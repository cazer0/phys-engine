/*
 * SDLview.cpp
 *
 *  Created on: 12 juil. 2014
 *      Author: mickael
 */

#include "SDLView.h"
#include <SDL2/SDL.h>

#include <iostream>


SDLView::SDLView(unsigned int width, unsigned int height) {
	// SDL Init
	if(SDL_Init(SDL_INIT_VIDEO)==-1)
	{
		throw SDL_ERROR;
	}

	//Create Main window
	pMainWindow = SDL_CreateWindow("Main View",SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									width, height,
									SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(pMainWindow==0){
		throw SDL_ERROR;
	}

	//Create OpenGL context
	glContext = SDL_GL_CreateContext(pMainWindow);
	if(glContext==0){
		SDL_DestroyWindow(pMainWindow);
		SDL_Quit();
		throw SDL_ERROR;
	}

	// SDL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR);

	// Double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, OPENGL_DEPTH_SIZE);
}

SDLView::~SDLView() {
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(pMainWindow);
	SDL_Quit();
}


void SDLView::Print_sdl_err()
{
	std::cerr<< "SDL err"<< SDL_GetError()<< std::endl;
}

int SDLView::Launch_event_loop()
{
    SDL_Event event;

    std::cout << "Launching main event loop" << std::endl;
    while(true)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
            	return EXIT_SUCCESS;
                break;
            default:break;
        }
        //Refresh window
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(pMainWindow);
    }
    return EXIT_FAILURE;
}
