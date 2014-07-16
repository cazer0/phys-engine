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
	pMainWindow = SDL_CreateWindow("Main View",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
									width, height,
									SDL_WINDOW_SHOWN);
	if(pMainWindow==NULL){
		throw SDL_ERROR;
	}

	//Create Main Renderer
	pMainRenderer = SDL_CreateRenderer(pMainWindow,-1, SDL_RENDERER_ACCELERATED);
	if(pMainRenderer==NULL){
		throw SDL_ERROR;
	}
}

SDLView::~SDLView() {
	SDL_DestroyRenderer(pMainRenderer);
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
    }
    return EXIT_FAILURE;
}
