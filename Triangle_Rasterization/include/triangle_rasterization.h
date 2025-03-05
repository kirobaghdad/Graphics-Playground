#ifndef TRIANGLE_RASTERIZATION_H
#define TRIANGLE_RASTERIZATION_H

#include <vector>

// Your code here

struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};

Vec3 ComputeBarycentricCoords(const Vec2 &p, const Vec2 &a, const Vec2 &b, const Vec2 &c);

void RasterizeTriangle(const Vec2 &a, const Vec2 &b, const Vec2 &c, std::vector<float> &framebuffer, int width, int height);

#endif // TRIANGLE_RASTERIZATION_H