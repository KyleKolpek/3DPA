/* Adapted from code on http://www.opengl.org/wiki/ */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <stdgl.h>
#include <SDL.h>
#include "Config.h"
#include "Cube.h"
#include "Renderer.h"
#include "Viewport.h"


#define PROGRAM_NAME "3D Programmer Art"
 
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
 
    /* Create our window centered at 512x512 resolution */
    mainwindow = SDL_CreateWindow(PROGRAM_NAME,
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  512,
                                  512,
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
    glViewport(0, 0, 512, 512);

    // Setup scene
    Cube cube(1,1,1,1);
    Viewport vp(512, 512);
    Renderer r;
    r.addViewport(&vp);
    r.addModel(&cube);

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
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_UP:
                            vp.getCurrentCamera().moveEye(
                                glm::vec3(0.0, 0.05, 0.0));
                            vp.getCurrentCamera().moveAt(
                                glm::vec3(0.0, 0.05, 0.0));
                            break;
                        case SDLK_DOWN:
                            vp.getCurrentCamera().moveEye(
                                glm::vec3(0.0, -0.05, 0.0));
                            vp.getCurrentCamera().moveAt(
                                glm::vec3(0.0, -0.05, 0.0));
                            break;
                        case SDLK_LEFT:
                            vp.getCurrentCamera().moveEye(
                                glm::vec3(-0.05, 0.0, 0.0));
                            vp.getCurrentCamera().moveAt(
                                glm::vec3(-0.05, 0.0, 0.0));
                            break;
                        case SDLK_RIGHT:
                            vp.getCurrentCamera().moveEye(
                                glm::vec3(0.05, 0.0, 0.0));
                            vp.getCurrentCamera().moveAt(
                                glm::vec3(0.05, 0.0, 0.0));
                            break;
                    }
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
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

