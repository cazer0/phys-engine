/*
 * SDLview.h
 *
 *  Created on: 12 juil. 2014
 *      Author: mickael
 */

#ifndef SDLVIEW_H_
#define SDLVIEW_H_

#include <SDL2/SDL.h>
// Windows
#ifdef WIN32
#include <GL/glew.h>

#else
//Linux
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>

#endif

//OpenGL version
static const int OPENGL_MAJOR=3;
static const int OPENGL_MINOR=1;

//OpenGL double buffer
static const int OPENGL_DEPTH_SIZE=32;
static const int SDL_ERROR=1;


class SDLView {
public:
	SDLView(unsigned int width=800, unsigned int height=600);
	virtual ~SDLView();
	int Launch_event_loop();

	static void Print_sdl_err();

private:
	SDL_Window		*pMainWindow;
	SDL_GLContext	glContext;
};

#endif /* SDLVIEW_H_ */
