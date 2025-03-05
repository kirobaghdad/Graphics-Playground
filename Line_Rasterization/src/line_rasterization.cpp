#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <line_rasterization.h>

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

void drawLineBresenham(float x0, float y0, float x1, float y1)
{
	// check the absolute slope
	float slope = abs((y1 - y0) / (x1 - x0));

	if (slope < 1)
		drawLineBresenham_X(x0, y0, x1, y1);
	else
		drawLineBresenham_Y(x0, y0, x1, y1);
}

void drawLineBresenham_Y(float x0, float y0, float x1, float y1)
{
	if (y0 > y1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int8_t change = std::signbit(dx) ? -1 : 1;

	dx *= change;

	int f = dy - 2 * dx;
	int x = x0;

	for (int y = y0; y <= y1; y++)
	{
		plot(x, y, 1);

		if (f < 0)
		{
			x += change;
			f += 2 * dy;
		}

		f += -2 * dx;
	}
}

void drawLineBresenham_X(float x0, float y0, float x1, float y1)
{
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	int8_t change = std::signbit(dy) ? -1 : 1;

	dy *= change;

	int f = dx - 2 * dy;
	int y = y0;

	for (int x = x0; x <= x1; x++)
	{
		plot(x, y, 1);

		if (f < 0)
		{
			y += change;
			f += 2 * dx;
		}

		f += -2 * dy;
	}
}
