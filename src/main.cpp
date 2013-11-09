/* Adapted from code on http://www.opengl.org/wiki/ */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdgl.h>
#include <SDL.h>
#include "Config.h"
#include "CubeManager.h"
#include "CubeGenerator.h"
#include "InputMapper.h"
#include "Renderer.h"
#include "Viewport.h"


#define PROGRAM_NAME "3D Programmer Art"
 
void cameraCallback(InputMap& inputs);

Viewport vp(1024, 1024);
InputMapper mapper;
CubeGenerator cg;

/* A simple function that prints a message, the error code returned by SDL,
 * and quits the application */
void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}
 
 
void checkSDLError(int line = -1)
{
#ifndef NDEBUG
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
                printf("SDL Error: %s\n", error);
                if (line != -1)
                        printf(" + line: %i\n", line);
                SDL_ClearError();
        }
#endif
}
 
 
/* Our program's entry point */
int main(int argc, char *argv[])
{
    SDL_Window *mainwindow;    /* Our window handle */
    SDL_GLContext maincontext; /* Our opengl context handle */
    SDL_Event event;           /* SDL Event container */
    GLuint vao;                /* Vertex Array Object */
    bool quit = false;
 
    if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
        sdldie("Unable to initialize SDL"); /* Or die on error */
 
    /* Request opengl 3.2 context.
     * SDL doesn't have the ability to choose which profile at this time of writing,
     * but it should default to the core profile */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    /*SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);*/
 
    /* Turn on double buffering with a 24bit Z buffer.
     * You may need to change this to 16 or 32 for your system */
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
 
    /* Hide the cursor when over the screen */
    //SDL_SetRelativeMouseMode(SDL_TRUE);

    /* Create our window centered at 512x512 resolution */
    mainwindow = SDL_CreateWindow(PROGRAM_NAME,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  1024,
                                  1024,
                                  SDL_WINDOW_OPENGL |
                                  SDL_WINDOW_SHOWN |
                                  SDL_WINDOW_RESIZABLE);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");
    checkSDLError(__LINE__);

    /* Create our opengl context and attach it to our window */
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);

    /* Initialize GLEW */
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    
    // Gen Vertex Array Object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    while(GLenum e = glGetError())
    {
        std::cerr << "GL Error: " << std::hex << e << std::endl;
    }

    // Disable Culling
    //glDisable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
 
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, 1024, 1024);

    // Setup scene
    CubeManager cm;
    Cube a, b, c;
    a.x = 0;
    a.y = 0;
    a.z = 0;
    a.red   = 1.0;
    a.green = 0.0;
    a.blue  = 0.0;
    b.x = 2;
    b.y = 2;
    b.z = -1;
    b.red   = 0.0;
    b.green = 1.0;
    b.blue  = 0.0;
    c.x = -2;
    c.y = 0;
    c.z = 1;
    c.red   = 0.0;
    c.green = 0.0;
    c.blue  = 1.0;

    cm.insert(a);
    cm.insert(b);
    cm.insert(c);

    cg.cubeManager = &cm;

    mapper.pushContext("maincontext");
    mapper.addCallback(cameraCallback, 0);

    Renderer r;
    r.addViewport(&vp);
    r.addModel(&cm);

    /* GAME LOOP */
    while(!quit)
    {
        /* Clear our buffer with a black background */
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Poll events */
        while(SDL_PollEvent(&event))
        {
            /* Handle events */
            switch(event.type)
            {
                case SDL_WINDOWEVENT:
                    switch(event.window.event)
                    {
                        case SDL_WINDOWEVENT_SIZE_CHANGED:
                            glViewport(0,
                                       0,
                                       event.window.data1,
                                       event.window.data2);
                            break;
                    }
                    break;
                case SDL_KEYUP:
                    {
                        Input::RawButton button =
                            Input::convertToRawButton(event);

                        mapper.processButtonInput(button,
                                                  event.key.state,
                                                  false);
                    }
                    break;
                case SDL_KEYDOWN:
                    {
                        Input::RawButton button =
                            Input::convertToRawButton(event);

                        mapper.processButtonInput(button,
                                                  event.key.state,
                                                  event.key.repeat);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                case SDL_MOUSEBUTTONUP:
                    {
                        Input::RawButton button = 
                            Input::convertToRawButton(event);

                        mapper.processButtonInput(button,
                                                  event.button.state,
                                                  false);
                    }
                    break;
                case SDL_MOUSEMOTION:
                    mapper.processAxisInput(Input::RAW_AXIS_MOUSE_X,
                                            static_cast<double>(
                                                event.motion.xrel));
                    mapper.processAxisInput(Input::RAW_AXIS_MOUSE_Y,
                                            static_cast<double>(
                                                event.motion.yrel));
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        
        // Process events based on inputs
        mapper.dispatch();
        mapper.reset();

        r.render();
        while(GLenum e = glGetError())
        {
            std::cerr << "GL Error: " << std::hex << e << std::endl;
        }
        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(mainwindow);
    }
 
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
 
    return 0;
}

void cameraCallback(InputMap& inputs)
{
    double x = inputs.ranges[Input::RANGE_ROTATE_CAMERA_X];
    double y = inputs.ranges[Input::RANGE_ROTATE_CAMERA_Y];

    if(inputs.states.find(Input::STATE_CAMERA_ROTATE) != inputs.states.end())
    {
        vp.getCurrentCamera().rotateY(-x);
        vp.getCurrentCamera().rotateX(y);
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.states.find(Input::STATE_CAMERA_MOVE_FORWARD) != inputs.states.end())
    {
        vp.getCurrentCamera().moveTowardsAt(0.25);
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.states.find(Input::STATE_CAMERA_MOVE_BACK) != inputs.states.end())
    {
        vp.getCurrentCamera().moveTowardsAt(-0.25);
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.states.find(Input::STATE_CAMERA_MOVE_LEFT) != inputs.states.end())
    {
        vp.getCurrentCamera().strafeRight(-0.25);
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.states.find(Input::STATE_CAMERA_MOVE_RIGHT) != inputs.states.end())
    {
        vp.getCurrentCamera().strafeRight(0.25);
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.states.find(Input::STATE_CAMERA_MOVE_UP) != inputs.states.end())
    {
        vp.getCurrentCamera().moveEye(glm::vec3(0.0, 0.25, 0.0));
        vp.getCurrentCamera().moveAt(glm::vec3(0.0, 0.25, 0.0));
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.states.find(Input::STATE_CAMERA_MOVE_DOWN) != inputs.states.end())
    {
        vp.getCurrentCamera().moveEye(glm::vec3(0.0, -0.25, 0.0));
        vp.getCurrentCamera().moveAt(glm::vec3(0.0, -0.25, 0.0));
        cg.moveTo(vp.getCurrentCamera().getAt());
    }
    if(inputs.actions.find(Input::ACTION_ADD_CUBE) != inputs.actions.end())
    {
        cg.addCube();
    }
}
