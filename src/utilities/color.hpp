#ifndef COLOR_H
#define COLOR_H

namespace Optikos
{
struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;

    constexpr Color() : r(0), g(0), b(0), a(255)
    {
    }

    constexpr Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255)
        : r(r), g(g), b(b), a(a)
    {
    }
};

struct Color3
{
    unsigned char r;
    unsigned char g;
    unsigned char b;

    constexpr Color3(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b)
    {
    }

    constexpr Color3(const Color& c) : r(c.r), g(c.g), b(c.b)
    {
    }
};

}  // namespace Optikos

#endif /* COLOR_H */