#include "texture.h"

Texture::Texture(const char* image, GLenum textureType, GLenum slot, GLenum format, GLenum pixelType) {
	type = textureType; 

	int imageWidth;
	int imageHeight;
	int channelsInFile;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(image, &imageWidth, &imageHeight, &channelsInFile, 0);

	glGenTextures(1, &id);
	glActiveTexture(slot);
	glBindTexture(textureType, id);

	glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_NEAREST);
	glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_NEAREST);

	glTexImage2D(textureType, 0, format, imageWidth, imageHeight, 0, format, pixelType, bytes);
	glGenerateMipmap(textureType);

	stbi_image_free(bytes);
	glBindTexture(textureType, 0);
}

void Texture::TextureUnit(Shader shader, const char* uniform, GLuint unit) {
	GLuint tex0Uniform = glGetUniformLocation(shader.id, uniform);
	shader.Activate();
	glUniform1i(tex0Uniform, unit);
}

void Texture::Bind() {
	glBindTexture(type, id);
}

void Texture::Unbind() {
	glBindTexture(type, 0);
}

void Texture::Delete() {
	glDeleteTextures(1, &id);
}
