#ifndef DDA_H
#define DDA_H

void plot(float x, float y, float intensity);

// Function to draw a line using DDA algorithm
void drawLineDDA(float x0, float y0, float x1, float y1);

// Xiaolin Wu's line algorithm
void drawLineXiaolinWu(float x0, float y0, float x1, float y1);

// Bresenham's line algorithm along the X-Axis
void drawLineBresenham_X(float x0, float y0, float x1, float y1);

// Bresenham's line algorithm along the Y-Axis
void drawLineBresenham_Y(float x0, float y0, float x1, float y1);

// Bresenham's line algorithm along the Y-Axis
void drawLineBresenham(float x0, float y0, float x1, float y1);

#endif // DDA_H