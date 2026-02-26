#ifndef VECTOR_H
#define VECTOR_H

namespace Optikos
{
struct Vec2
{
    Vec2(float x = 0.0f, float y = 0.0f) : x(x), y(y)
    {
    }

    bool operator==(const Vec2& other) const
    {
        return (x == other.x && y == other.y);
    }

    bool operator!=(const Vec2& other) const
    {
        return !(*this == other);
    }
    
    Vec2 operator+(const Vec2& other) const
    {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2& operator+=(const Vec2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 operator-(const Vec2& other) const
    {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2& operator-=(const Vec2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2 operator*(const Vec2& other) const
    {
        return Vec2(x * other.x, y * other.y);
    }

    Vec2& operator*=(const Vec2& other)
    {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vec2 operator/(const Vec2& other) const
    {
        return Vec2(x / other.x, y / other.y);
    }

    Vec2& operator/=(const Vec2& other)
    {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec2)
    {
        os << vec2.x << " " << vec2.y;
        return os;
    }

    float x;
    float y;
};

}  // namespace Optikos

#endif /* VECTOR_H */