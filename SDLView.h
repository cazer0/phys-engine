/*
 * SDLview.h
 *
 *  Created on: 12 juil. 2014
 *      Author: mickael
 */

#ifndef SDLVIEW_H_
#define SDLVIEW_H_

#include <SDL2/SDL.h>

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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
	SDL_Window*		m_pMainWindow;
	SDL_GLContext	m_glContext;
	SDL_Event		m_Event;

	glm::mat4		m_Projection;
	glm::mat4		m_ModelView;
};

#endif /* SDLVIEW_H_ */
