#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"
#include "texture.h"

const int DEFAULT_SCREEN_WIDTH = 1024;
const int DEFAULT_SCREEN_HEIGHT = 1024;

GLfloat vertices[] = {
	// Coordinates      // Colors         // Texture coordinates
	-0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Top left corner
	 0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Top right corner
	 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // Bottom right corner
	-0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f  // Bottom left corner
};

GLuint indices[] = {
	0, 1, 2,
	0, 3, 2
};

void setWindowHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

GLFWwindow* createWindow()
{
	return glfwCreateWindow(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "Mythic Engine", NULL, NULL);
}

int main()
{
	glfwInit();
	setWindowHints();

	GLFWwindow* window = createWindow();
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();

	glViewport(0, 0, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);

	Shader shaderProgram("default.vert", "default.frag");

	VAO vao;
	vao.Bind();

	VBO vbo(vertices, sizeof(vertices));
	EBO ebo(indices, sizeof(indices));

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	GLuint uniformId = glGetUniformLocation(shaderProgram.id, "scale");

	Texture obamaTexture("obama_texture_512.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	obamaTexture.TextureUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();
		glUniform1f(uniformId, 0.5f);
		obamaTexture.Bind();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}	

	
	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	obamaTexture.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}