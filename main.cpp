#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"

const int DEFAULT_SCREEN_WIDTH = 640;
const int DEFAULT_SCREEN_HEIGHT = 480;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,			1.0f, 0.0f, 0.0f, // 0 = bottom left
	0.5f, -0.5f, 0.0f,			0.0f, 1.0f, 0.0f, // 1 = bottom right
	0.0f, 0.5f, 0.0f,			0.0f, 0.0f, 1.0f, // 2 = top middle
	-0.25, 0.0f, 0.0f,			0.5f, 0.0f, 0.0f, // 3 = middle left
	0.25, 0.0f, 0.0f,			0.0f, 0.5f, 0.0f, // 4 = middle right
	0.0f, -0.5f, 0.0f,			0.0f, 0.5f, 0.0f // 5 = bottom middle
};

GLuint indices[] = {
	0, 3, 5,
	1, 4, 5,
	2, 3, 4
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

	vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	vao.Unbind();
	vbo.Unbind();
	ebo.Unbind();

	GLuint uniformId = glGetUniformLocation(shaderProgram.id, "scale");

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shaderProgram.Activate();
		glUniform1f(uniformId, 0.5f);
		vao.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}	

	vao.Delete();
	vbo.Delete();
	ebo.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();


	return 0;
}