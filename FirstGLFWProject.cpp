#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);


int main() {
	//glfw: Initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif


	//glfw: Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);  //glfw: set windows as thread focus
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//set viewport dimensions

	//glad: Load OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	Shader ourShader("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs");

	//setup for vertex data, buffers, and configure vertex attributes
	float vertices[] = {
		 //positions         //colors
		 -0.4f,  0.2f, 0.0f,  1.0f, 0.0f, 0.0f,  //bottom right
		 -0.6f, -0.2f, 0.0f,  0.0f, 1.0f, 0.0f,  //bottom left
		 -0.2f, -0.2f, 0.0f,  0.0f, 0.0f, 1.0f   //top
	};

	//Create vertex buffer object and assign to GPU memory as static
	unsigned int VBO1, VAO1;
	glGenVertexArrays(1, &VAO1);
	glGenBuffers(1, &VBO1);

	//Set current vertex array in use
	glBindVertexArray(VAO1);

	//Set current buffer data to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	//Pass vertex Position to the current VAO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Pass vertex color to current VAO
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	//render loop
	//Keep window open untill told to close
	while (!glfwWindowShouldClose(window)) {
		//check for input
		processInput(window);

		//redering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate shader
		ourShader.use();

		//Draw first triangle
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//Clear current array in use
		glBindVertexArray(0);

		//check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//Clear and remove all windows
	glfwTerminate();
	return 0;
}

//resize window to match user resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	//Window should close when ESC pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}