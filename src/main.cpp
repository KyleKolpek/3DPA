/* Adapted from code on http://www.opengl.org/wiki/ */
#include <stdio.h>
#include <stdlib.h>
#include <stdgl.h>
#include <SDL.h>
#include "ShaderManager.h"
#include "Config.h"

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
    ShaderManager sm(SHADER_DIR);
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
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
 
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
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
 
    /* This makes our buffer swap syncronized with the monitor's vertical refresh */
    SDL_GL_SetSwapInterval(1);

    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* GAME LOOP */
    while(!quit)
    {
        /* Clear our buffer with a black background */

        /* Poll events */
        while(SDL_PollEvent(&event))
        {
            /* Handle events */
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    glClearColor(1.0, 0.0, 0.0, 0.0);
                    break;
                case SDL_MOUSEBUTTONUP:
                    glClearColor(0.0, 0.0, 0.0, 0.0);
                    break;
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
                case SDL_QUIT:
                    quit = true;
                    break;
            }
        }
        glClear ( GL_COLOR_BUFFER_BIT );

        /* Swap our back buffer to the front */
        SDL_GL_SwapWindow(mainwindow);
    }
 
    /* Delete our opengl context, destroy our window, and shutdown SDL */
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
 
    return 0;
}

