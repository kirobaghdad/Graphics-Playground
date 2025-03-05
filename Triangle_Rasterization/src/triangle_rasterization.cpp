#include <bits/stdc++.h>
#include <triangle_rasterization.h>

Vec3 ComputeBarycentricCoords(const Vec2 &p, const Vec2 &a, const Vec2 &b, const Vec2 &c)
{
    Vec2 v0 = {b.x - a.x, b.y - a.y};
    Vec2 v1 = {c.x - a.x, c.y - a.y};
    Vec2 v2 = {p.x - a.x, p.y - a.y};

    float d00 = v0.x * v0.x + v0.y * v0.y;
    float d01 = v0.x * v1.x + v0.y * v1.y;
    float d11 = v1.x * v1.x + v1.y * v1.y;
    float d20 = v2.x * v0.x + v2.y * v0.y;
    float d21 = v2.x * v1.x + v2.y * v1.y;

    float denom = d00 * d11 - d01 * d01;
    float v = (d11 * d20 - d01 * d21) / denom;
    float w = (d00 * d21 - d01 * d20) / denom;
    float u = 1.0f - v - w;

    return {u, v, w};
}

void RasterizeTriangle(const Vec2 &a, const Vec2 &b, const Vec2 &c, std::vector<float> &framebuffer, int width, int height)
{
    int minX = std::max(0, (int)std::min({a.x, b.x, c.x}));
    int maxX = std::min(width - 1, (int)std::max({a.x, b.x, c.x}));
    int minY = std::max(0, (int)std::min({a.y, b.y, c.y}));
    int maxY = std::min(height - 1, (int)std::max({a.y, b.y, c.y}));

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            Vec2 p = {(float)x, (float)y};
            Vec3 bary = ComputeBarycentricCoords(p, a, b, c);

            if (bary.x >= 0 && bary.y >= 0 && bary.z >= 0)
            {
                int index = (y * width + x) * 3;
                framebuffer[index] = 1.0f;     // Red
                framebuffer[index + 1] = 1.0f; // Green
                framebuffer[index + 2] = 1.0f; // Blue
            }
        }
    }
}
