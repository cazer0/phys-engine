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
    SDL_Event event;

    float vertices[]={
    		0.0f,	0.0f,	-1.0f,
    		0.5f,	0.0f, 	-1.0f,
    		0.0f,	0.5f, 	-1.0f};
    float colors[]={
    		//R, G, B
    		1.0f, 0.0, 0.0,
    		0.0, 1.0f, 0.0,
    		0.0, 0.0, 1.0f
    };

    //Shader init
    Shader myShader("Shaders/couleur3D.vert", "Shaders/couleur3D.frag");
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
        // Clear window
        glClear(GL_COLOR_BUFFER_BIT);

        // Matrix reset
        m_ModelView = glm::mat4(1.0);
        m_ModelView = glm::lookAt(glm::vec3(1,1,1),glm::vec3(0,0,0),glm::vec3(0,1,0));

        // Begin display
        glUseProgram(myShader.getProgramID());
        {
        	//Vertices init
			glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,0,vertices);
			glEnableVertexAttribArray(0);

			//Colors Init
			glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,0,colors);
			glEnableVertexAttribArray(1);

			//Matrix transformation
			m_ModelView = glm::translate(m_ModelView,glm::vec3(0.4f,0.0f,0.0f));
			m_ModelView = glm::rotate(m_ModelView,60.0f, glm::vec3(0.0f,0.0f,1.0f));
			m_ModelView = glm::scale(m_ModelView, glm::vec3(2,2,1));

			//Send matrix to the shaders
			glUniformMatrix4fv(glGetUniformLocation(myShader.getProgramID(),"modelview"),
								1,
								GL_FALSE,
								glm::value_ptr(m_ModelView));

			glUniformMatrix4fv(glGetUniformLocation(myShader.getProgramID(),"projection"),
											1,
											GL_FALSE,
											glm::value_ptr(m_Projection));
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
