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

SDLView::SDLView(unsigned int width, unsigned int height) {
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
    SDL_Event event;

    float vertices[]={
    		-0.7f,-0.7f,
    		0, 0.7f,
    		0.7f,-0.7f};
    float colors[]={
    		//R, G, B
    		0.5, 0.0, 0.0,
    		0.0, 0.5, 0.0,
    		0.0, 0.0, 0.5
    };

    //Shader init
    Shader myShader("Shaders/couleur2D.vert", "Shaders/couleur2D.frag");
    myShader.charger();

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
        //Clear window
        glClear(GL_COLOR_BUFFER_BIT);

        //TEST

        glUseProgram(myShader.getProgramID());
        {
        	//Vertices init
			glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE,0,vertices);
			glEnableVertexAttribArray(0);

			//Colors Init
			glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,0,colors);
			glEnableVertexAttribArray(1);

			//Draw
			glDrawArrays(GL_TRIANGLES,0,3);

			//De-init
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(0);
        }
        glUseProgram(0);

        //Refresh window
        SDL_GL_SwapWindow(m_pMainWindow);
    }
    return EXIT_FAILURE;
}
