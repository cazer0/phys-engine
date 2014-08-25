/*
 * Cube.cpp
 *
 *  Created on: 25 août 2014
 *      Author: mickael
 */

#include "Cube.h"

Cube::Cube(float taille, std::string const vertexShader, std::string fragmentShader)
:m_Shader(vertexShader,fragmentShader)
{

	// Shader
	m_Shader.charger();

	taille /=2;
    float vertices[]={
    		//BACK
    		-taille, -taille, taille, taille, -taille, taille, taille, -taille,-taille,
    		-taille, -taille, taille,	-taille, -taille,-taille, taille, -taille,-taille,

    		//RIGHT
    		-taille, -taille, taille, -taille, -taille,-taille,	-taille,taille,-taille,
    		-taille, -taille, taille, -taille,taille,taille,	-taille,taille,-taille,

    		//BOTTOM
    		taille, -taille,-taille, -taille, -taille,-taille,	-taille,taille,-taille,
    		taille, -taille,-taille, taille,taille,-taille,	-taille,taille,-taille,

    		//LEFT
    		taille, -taille, taille, taille, -taille,-taille,	taille,taille,-taille,
    		taille, -taille, taille, taille,taille,taille,	taille,taille,-taille,

    		//FRONT
    		taille,taille,taille, -taille,taille,taille,	-taille,taille,-taille,
    		taille,taille,taille, taille,taille,-taille,	-taille,taille,-taille,

    		//TOP
    		taille, -taille, taille, -taille, -taille, taille,	-taille,taille,taille,
    		taille, -taille, taille, taille,taille,taille,	-taille,taille,taille
    };

    float colors[]={
       		//R, G, B
       		0.1f, 0.1f, 0.1f,		0.1f, 0.1f, 0.1f,		0.1f, 0.1f, 0.1f,
       		0.1f, 0.1f, 0.1f,		0.1f, 0.1f, 0.1f,		0.1f, 0.1f, 0.1f,

       		0.25f,0.25f,0.25f,		0.25f,0.25f,0.25f,		0.25f,0.25f,0.25f,
       		0.25f,0.25f,0.25f,		0.25f,0.25f,0.25f,		0.25f,0.25f,0.25f,

       		0.40f,0.40f,0.40f,		0.40f,0.40f,0.40f,		0.40f,0.40f,0.40f,
       		0.40f,0.40f,0.40f,		0.40f,0.40f,0.40f,		0.40f,0.40f,0.40f,

       		0.55f,0.55f,0.55f,		0.55f,0.55f,0.55f,		0.55f,0.55f,0.55f,
       		0.55f,0.55f,0.55f,		0.55f,0.55f,0.55f,		0.55f,0.55f,0.55f,

       		0.70f,0.70f,0.70f,		0.70f,0.70f,0.70f,		0.70f,0.70f,0.70f,
       		0.70f,0.70f,0.70f,		0.70f,0.70f,0.70f,		0.70f,0.70f,0.70f,

       		0.85f,0.85f,0.85f,		0.85f,0.85f,0.85f,		0.85f,0.85f,0.85f,
       		0.85f,0.85f,0.85f,		0.85f,0.85f,0.85f,		0.85f,0.85f,0.85f
       };

    for(int i=0; i<108 ; ++i)
    {
    	m_vertices[i] = vertices[i];
    	m_colors[i] = colors[i];
    }
}

Cube::~Cube() {

}

void Cube::Afficher(glm::mat4 &projection, glm::mat4 &modelview) {

	glUseProgram(m_Shader.getProgramID());
	{
		//Vertices init
		glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,0,m_vertices);
		glEnableVertexAttribArray(0);

		//Colors Init
		glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE,0,m_colors);
		glEnableVertexAttribArray(1);

		//Send matrix to the shaders
		glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(),"modelview"),
							1,
							GL_FALSE,
							glm::value_ptr(modelview));

		glUniformMatrix4fv(glGetUniformLocation(m_Shader.getProgramID(),"projection"),
										1,
										GL_FALSE,
										glm::value_ptr(projection));
		//Draw
		glDrawArrays(GL_TRIANGLES,0,6*6);

		//De-init
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
	}
	glUseProgram(0);
}
