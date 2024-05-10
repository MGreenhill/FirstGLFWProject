#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource = "#version 330 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"	
		"}\0";

const char* fragmentShaderSourceOrange = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"uniform vec4 ourColor;\n"
		"void main()\n"
		"{\n"
		//"	ourColor = vec4(0.5, 0.0, 0.0, 1.0);\n"
		//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"	FragColor = ourColor;\n"
		"}\n\0";

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

	//build and compile Shaders
	//------------------------
	//Vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//Fragment Shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceOrange, NULL);
	glCompileShader(fragmentShader);
	//check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//Link shaders Orange
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	//check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	//Delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	//glDeleteShader(fragmentShaderYellow);


	//setup for vertex data, buffers, and configure vertex attributes
	float vertices[] = {
		 -0.4f,  0.2f, 0.0f,
		 -0.6f, -0.2f, 0.0f,
		 -0.2f, -0.2f, 0.0f
	};

	unsigned int indices[] = {  // start with 0
		0, 1, 3,
		1, 2, 3
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
	
	//Pass vertex data to the current vertex array
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//render loop
	//Keep window open untill told to close
	while (!glfwWindowShouldClose(window)) {
		//check for input
		processInput(window);

		//redering commands here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//Activate shader
		glUseProgram(shaderProgram);

		//update the uniform color
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

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