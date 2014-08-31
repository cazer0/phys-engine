/*
 * SDLview.cpp
 *
 *  Created on: 12 juil. 2014
 *      Author: mickael
 */

#include "SDLView.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "Shader.h"

#include "Cube.h"

SDLView::SDLView(unsigned int width, unsigned int height) : m_input()
{
	// SDL Init
	if(SDL_Init(SDL_INIT_VIDEO)==-1)
	{
		throw SDL_ERROR;
	}

	//Create Main window
	m_pMainWindow = SDL_CreateWindow("Main View",SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									width, height,
									SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if(m_pMainWindow==0){
		throw SDL_ERROR;
	}

	//Create OpenGL context
	m_glContext = SDL_GL_CreateContext(m_pMainWindow);
	if(m_glContext==0){
		SDL_DestroyWindow(m_pMainWindow);
		SDL_Quit();
		throw SDL_ERROR;
	}

	// SDL version
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, OPENGL_MAJOR);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, OPENGL_MINOR);

	// Double buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, OPENGL_DEPTH_SIZE);

	glEnable(GL_DEPTH_TEST);

	// Matrix creation
	m_Projection = glm::perspective(70.0, (const double)width/height,1.0,100.0);
	m_ModelView = glm::mat4(1.0);
}

SDLView::~SDLView() {
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_pMainWindow);
	SDL_Quit();
}


void SDLView::Print_sdl_err()
{
	std::cerr<< "SDL err"<< SDL_GetError()<< std::endl;
}

int SDLView::Launch_event_loop()
{
    uint32_t begin_time(0);
    uint32_t elapsed_time(0);
    uint32_t framerate_ms(1000/50);

    //Shader init
    Shader myShader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
    myShader.charger();

    // Objects init
    Cube myCube(2.0, "Shaders/couleur3D.vert", "Shaders/couleur3D.frag");

    float angleX(0.0);
    float angleY(0.0);

    std::cout << "Launching main event loop" << std::endl;
    while(!m_input.terminate())
    {
    	begin_time = SDL_GetTicks();

    	//Input management
    	m_input.updateEvents();

    	if(m_input.isKeyPressed(SDL_SCANCODE_LEFT))
    	    angleX-=4.0f;

    	if(m_input.isKeyPressed(SDL_SCANCODE_RIGHT))
    	    angleX+=4.0f;

    	if(m_input.isKeyPressed(SDL_SCANCODE_UP))
    	    angleY+=4.0f;

    	if(m_input.isKeyPressed(SDL_SCANCODE_DOWN))
    	    angleY-=4.0f;

    	if(angleX >360.0f) angleX -=360.0f;
    	if(angleY >360.0f) angleY -=360.0f;
    	// Clear window
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Matrix reset
        m_ModelView = glm::mat4(1.0);
        m_ModelView = glm::lookAt(glm::vec3(0,6,6),glm::vec3(0,0,0),glm::vec3(0,0,1));

        m_ModelView = glm::rotate(m_ModelView, angleX, glm::vec3(0,0,1));
        m_ModelView = glm::rotate(m_ModelView, angleY, glm::vec3(1,0,0));

        // Begin display
        myCube.Afficher(m_Projection, m_ModelView);

        //Refresh window
        SDL_GL_SwapWindow(m_pMainWindow);

        elapsed_time = SDL_GetTicks() - begin_time;
        if( elapsed_time < framerate_ms)
        	SDL_Delay(framerate_ms - elapsed_time);
    }
    return EXIT_FAILURE;
}
