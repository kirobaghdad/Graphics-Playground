#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>

// Window dimensions
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Function to draw a line using DDA algorithm
void drawLineDDA(float x0, float y0, float x1, float y1)
{
	float dx = x1 - x0;
	float dy = y1 - y0;
	float steps = std::max(abs(dx), abs(dy)); // Number of steps to take

	float xIncrement = dx / steps;
	float yIncrement = dy / steps;

	float x = x0;
	float y = y0;

	glBegin(GL_POINTS); // Start drawing points
	for (int i = 0; i <= steps; i++)
	{
		glVertex2f(round(x), round(y)); // Draw the pixel at (x, y)
		x += xIncrement;
		y += yIncrement;
	}
	glEnd();
}

void plot(float x, float y, float intensity)
{
	glColor3f(intensity, intensity, intensity); // Set pixel intensity (grayscale)
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();
}

// Xiaolin Wu's line algorithm
void drawLineXiaolinWu(float x0, float y0, float x1, float y1)
{
	bool steep = abs(y1 - y0) > abs(x1 - x0); // Check if the line is steep

	// Swap coordinates if the line is steep
	if (steep)
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
	}

	// Ensure x0 < x1
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	float dx = x1 - x0;
	float dy = y1 - y0;
	float gradient = (dx == 0.0f) ? 1.0f : dy / dx;

	// Handle first endpoint
	float xend = round(x0);
	float yend = y0 + gradient * (xend - x0);
	float xgap = 1.0f - fmod(x0 + 0.5f, 1.0f);
	float xpxl1 = xend; // This will be used in the main loop
	float ypxl1 = floor(yend);

	if (steep)
	{
		plot(ypxl1, xpxl1, 1.0f - fmod(yend, 1.0f) * xgap);
		plot(ypxl1 + 1, xpxl1, fmod(yend, 1.0f) * xgap);
	}
	else
	{
		plot(xpxl1, ypxl1, 1.0f - fmod(yend, 1.0f) * xgap);
		plot(xpxl1, ypxl1 + 1, fmod(yend, 1.0f) * xgap);
	}

	float intery = yend + gradient; // First y-intersection for the main loop

	// Handle second endpoint
	xend = round(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = fmod(x1 + 0.5f, 1.0f);
	float xpxl2 = xend; // This will be used in the main loop
	float ypxl2 = floor(yend);

	if (steep)
	{
		plot(ypxl2, xpxl2, 1.0f - fmod(yend, 1.0f) * xgap);
		plot(ypxl2 + 1, xpxl2, fmod(yend, 1.0f) * xgap);
	}
	else
	{
		plot(xpxl2, ypxl2, 1.0f - fmod(yend, 1.0f) * xgap);
		plot(xpxl2, ypxl2 + 1, fmod(yend, 1.0f) * xgap);
	}

	// Main loop
	if (steep)
	{
		for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
		{
			plot(floor(intery), x, 1.0f - fmod(intery, 1.0f));
			plot(floor(intery) + 1, x, fmod(intery, 1.0f));
			intery += gradient;
		}
	}
	else
	{
		for (float x = xpxl1 + 1; x <= xpxl2 - 1; x++)
		{
			plot(x, floor(intery), 1.0f - fmod(intery, 1.0f));
			plot(x, floor(intery) + 1, fmod(intery, 1.0f));
			intery += gradient;
		}
	}
}

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
	while (!glfwWindowShouldClose(window1))
	{
		// Render to the first window
		glfwMakeContextCurrent(window1);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);	 // White color
		drawLineDDA(100, 100, 700, 500); // Draw a line using DDA
		glfwSwapBuffers(window1);

		// Render to the second window
		glfwMakeContextCurrent(window2);
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(1.0f, 1.0f, 1.0f);		   // White color
		drawLineXiaolinWu(100, 100, 700, 500); // Draw a line using Xiaolin Wu
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