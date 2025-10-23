#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "shader.h"

class Texture
{
	public: 
		GLuint id;
		GLenum type;

		Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType);

		void TextureUnit(Shader& shader, const char* uniform, GLuint unit);
		void Bind();
		void Unbind();
		void Delete();
};

#endif
