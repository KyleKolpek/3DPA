/* Adapted from code on http://www.opengl.org/wiki/ */
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <SDL.h>
#include <Rocket/Core.h>
#include <Rocket/SDLCore.h>
#include <Rocket/Controls.h>
#include <Rocket/Debugger.h>
#include "stdgl.h"
#include "Config.h"
#include "CubeModeler.h"
#include "InputMapper.h"
#include "Renderer.h"
#include "Viewport.h"


#define PROGRAM_NAME "3D Programmer Art"
 
void cameraCallback(InputMap& inputs);

Viewport vp(1024, 1024);
InputMapper mapper;
ShaderManager sm("../assets/shaders/");

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
 
    /* Hide the cursor when over the screen. This seems to be bugged. */
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
    // Die if creation failed 
    if (!mainwindow)
    {
        sdldie("Unable to create window");
    }
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
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
 
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, 1024, 1024);

    // Setup scene
    CubeModeler cm(sm);

    Renderer r;
    r.addViewport(&vp);
    r.addModel(&cm);
    
    ////////////////////////////////////////////////////////////////////////////
    // Set up Rocket
    ////////////////////////////////////////////////////////////////////////////
    SDLRenderInterface rocketRenderer;
    rocketRenderer.SetShaderManager(&sm);
    Rocket::Core::SetRenderInterface(&rocketRenderer);
    rocketRenderer.SetViewport(1024, 1024);

    SDLSystemInterface rocketSystem;
    Rocket::Core::SetSystemInterface(&rocketSystem);

    Rocket::Core::Initialise();
    Rocket::Core::Context* rocketContext =
        Rocket::Core::CreateContext("default",
                                    Rocket::Core::Vector2i(1024, 1024));
    if(rocketContext == NULL)
    {
        std::cerr << "Error creating Rocket context." << std::endl;
        Rocket::Core::Shutdown();
        return 1;
    }

    SDLInputInterface rocketInput(rocketContext);

    // Set up the debugger
    //Rocket::Debugger::Initialise(rocketContext);
    //Rocket::Debugger::SetVisible(true);

    // Set up the controls
    Rocket::Controls::Initialise();

    Rocket::Core::FontDatabase::LoadFontFace(
        Rocket::Core::String("../assets/fonts/Delicious-Roman.otf"));
    Rocket::Core::FontDatabase::LoadFontFace(
        Rocket::Core::String("../assets/fonts/Delicious-Italic.otf"));
    Rocket::Core::FontDatabase::LoadFontFace(
        Rocket::Core::String("../assets/fonts/Delicious-Bold.otf"));
    Rocket::Core::FontDatabase::LoadFontFace(
        Rocket::Core::String("../assets/fonts/Delicious-BoldItalic.otf"));

    Rocket::Core::ElementDocument *document =
        rocketContext->LoadDocument("../assets/Rocket/menu.rml");
    if(document != NULL)
    {
        document->Show();
        document->RemoveReference();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Set up input
    ////////////////////////////////////////////////////////////////////////////
    mapper.pushContext("maincontext");
    mapper.addCallback(&vp.getCurrentCamera(), 0);
    mapper.addCallback(&cm, 0);

    ////////////////////////////////////////////////////////////////////////////
    // GAME LOOP
    ////////////////////////////////////////////////////////////////////////////
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
                            rocketRenderer.SetViewport(event.window.data1,
                                                       event.window.data2);
                            rocketContext->SetDimensions(
                                Rocket::Core::Vector2i(event.window.data1,
                                                       event.window.data2));
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
                case SDL_TEXTINPUT:
                    mapper.processTextInput(event.text.text);
                    break;
                case SDL_QUIT:
                    quit = true;
                    break;
            }
            // Pass events to rocket
            rocketInput.handleRocketInput(event);
        }
        
        // Process events based on inputs
        mapper.dispatch();
        mapper.reset();

        cm.setActiveCubePos(vp.getCurrentCamera().getAt());
        r.render();

        // Rocket Updates
        rocketContext->Update();
        rocketContext->Render();

        while(GLenum e = glGetError())
        {
            std::cerr << "GL Error: " << std::hex << e << std::endl;
        }
        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(mainwindow);
    }
 
    /* Delete random stuff */

    /* Shut down rocket */
    // Example of how to unload documents
    document->GetContext()->UnloadDocument(document);
    rocketContext->RemoveReference();
    Rocket::Core::Shutdown();

    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();

    return 0;
}
