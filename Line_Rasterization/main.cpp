#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <chrono>

#include <line_rasterization.h>

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Callback for window resize
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

int main()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// Create the first window
	GLFWwindow *window1 = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "DDA Line Drawing", NULL, NULL);
	if (!window1)
	{
		std::cerr << "Failed to create GLFW window 1" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window1);
	glfwSetFramebufferSizeCallback(window1, framebuffer_size_callback);

	// Load OpenGL functions for the first window using glad
	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD for window 1" << std::endl;
		return -1;
	}

	// Set up the viewport for the first window
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCR_WIDTH, 0, SCR_HEIGHT, -1, 1); // 2D orthographic projection
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Create the second window
	GLFWwindow *window2 = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "XiaolinWu Line Drawing", NULL, NULL);
	if (!window2)
	{
		std::cerr << "Failed to create GLFW window 2" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window2);
	glfwSetFramebufferSizeCallback(window2, framebuffer_size_callback);

	// Load OpenGL functions for the second window using glad
	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD for window 2" << std::endl;
		return -1;
	}

	// Set up the viewport for the second window
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, SCR_WIDTH, 0, SCR_HEIGHT, -1, 1); // 2D orthographic projection
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Main rendering loop
	while (!(glfwWindowShouldClose(window1) || glfwWindowShouldClose(window2)))
	{
		// Render to the first window
		glfwMakeContextCurrent(window1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);		   // White color
		drawLineBresenham(100, 100, 200, 550); // Draw a line using Bresenham's Algo.
		glfwSwapBuffers(window1);

		// Render to the second window
		glfwMakeContextCurrent(window2);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);		   // White color
		drawLineXiaolinWu(100, 100, 200, 550); // Draw a line using Bresenham's Algo.
		glfwSwapBuffers(window2);

		// Poll events for both windows
		glfwPollEvents();
	}

	// Clean up and exit
	glfwDestroyWindow(window1);
	glfwDestroyWindow(window2);
	glfwTerminate();
	return 0;
}