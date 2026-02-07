#ifndef COLOR_H
#define COLOR_H

namespace Optikos
{

struct Color
{
    float r;
    float g;
    float b;
    float a;

    constexpr Color(float r, float g, float b, float a = 255.0f)
        : r(r), g(g), b(b), a(a) {}
};

struct Color3
{
    float r;
    float g;
    float b;
    
    constexpr Color3(float r, float g, float b)
        : r(r), g(g), b(b) {}
    
    constexpr Color3(const Color& c)
        : r(c.r), g(c.g), b(c.b) {}
};

}  // namespace Optikos

#endif /* COLOR_H */