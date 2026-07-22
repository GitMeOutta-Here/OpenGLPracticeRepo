#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include <filesystem>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const GLuint SCR_WIDTH = 800;
const GLuint SCR_HEIGHT = 800;


int main() {

	// Initialize GLFW
	glfwInit();

	// Tells GLFW what version of OpenGL I am using
	// Using OpenGL 4.4 for this project
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	// Tells GLFW that I am using the core profile
	// core profile has only modern functions within OpenGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



	// Create GLFW window object of 800x800 pixels named "OpenGL Window", 
	// fullscreen = null, shareResources = null (no other window to share resources)
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Window", nullptr, nullptr);

	// Check if window object created successfully
	// if not, terminate GLFW, and return -1
	if (!window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window object into the current context
	// (make the window interactable)
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	// Load glad so it configures OpenGL
	gladLoadGL();

	Shader ourShader("shaders/shader.vert", "shaders/shader.frag");


	// Vertices data for the triangle
	GLfloat vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};


	//Specify the viewport of openGL from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Attribute Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	// Bind VBO as active buffer in OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Put vertices data into VBO data buffer
	// Static usage pattern indicates the buffer will be written once, but read many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	// Swaps the current and back buffer to show the new color
	glfwSwapBuffers(window);

	// Keeps window open until user clicks exit, 
	// or some other function tells window to close
	while (!glfwWindowShouldClose(window)) {

		processInput(window);
		// render
		// ------
		glClearColor(0.17f, 0.17f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// render the triangle
		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Destroy the GLFW window object
	glfwDestroyWindow(window);
	// Terminate GLFW
	glfwTerminate();

	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}