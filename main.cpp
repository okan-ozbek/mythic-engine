#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"
#include "texture.h"
#include "camera.h"

const int DEFAULT_SCREEN_WIDTH = 1024;
const int DEFAULT_SCREEN_HEIGHT = 1024;

GLfloat vertices[] = {
	// Coordinates        // Colors              // Texture coordinates
	-0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,   0.0f, 0.0f, 
	-0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,   1.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,   0.83f, 0.70f, 0.44f,   0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,   0.83f, 0.70f, 0.44f,   1.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,   0.92f, 0.86f, 0.76f,   0.5f, 1.0f,
};

GLuint indices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	0, 3, 4
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


	Texture obamaTexture("obama_texture_512.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_UNSIGNED_BYTE);
	obamaTexture.TextureUnit(shaderProgram, "tex0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "cameraMatrix");


		obamaTexture.Bind();
		vao.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

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