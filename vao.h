#ifndef VAO_CLASS_H
#define VAO_CLASS_H

#include<glad/glad.h>
#include "vbo.h"

class VAO
{
	public:
		GLuint id;
		VAO();

		void LinkVBO(VBO vbo, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
};

#endif 
