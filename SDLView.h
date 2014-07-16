/*
 * SDLview.h
 *
 *  Created on: 12 juil. 2014
 *      Author: mickael
 */

#ifndef SDLVIEW_H_
#define SDLVIEW_H_

#include <SDL2/SDL.h>

static const int SDL_ERROR=1;


class SDLView {
public:
	SDLView(unsigned int width=800, unsigned int height=600);
	virtual ~SDLView();
	int Launch_event_loop();

	static void Print_sdl_err();

private:
	SDL_Window *pMainWindow;
	SDL_Renderer *pMainRenderer;
};

#endif /* SDLVIEW_H_ */
