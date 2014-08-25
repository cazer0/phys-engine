/*
 * Cube.h
 *
 *  Created on: 25 août 2014
 *      Author: mickael
 */

#ifndef CUBE_H_
#define CUBE_H_

#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Cube {
public:
	Cube(float taille, std::string const vertexShader, std::string fragmentShader);
	virtual ~Cube();

	void Afficher(glm::mat4 &projection, glm::mat4 &modelview);

private:
	Shader m_Shader;
	float m_vertices[108];
	float m_colors[108];
};

#endif /* CUBE_H_ */
