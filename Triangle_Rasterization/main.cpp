#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <chrono>
#include <triangle_rasterization.h>

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
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle Rasterization", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGL(glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD for window 2" << std::endl;
		return -1;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	std::vector<float> framebuffer(width * height * 3, 0.0f);

	Vec2 a = {400, 100};
	Vec2 b = {700, 100};
	Vec2 c = {400, 500};

	RasterizeTriangle(a, b, c, framebuffer, width, height);

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, framebuffer.data());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}