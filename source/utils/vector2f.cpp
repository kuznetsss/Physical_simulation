#include "utils/vector2f.h"

#include<math.h>

namespace utils {

Vector2f::Vector2f() = default;

Vector2f::Vector2f(float x, float y):
    _x(x),
    _y(y)
{}

Vector2f Vector2f::operator+(const Vector2f& right) const
{
    return Vector2f(_x + right.x(), _y + right.y());
}

void Vector2f::operator+=(const Vector2f& right)
{
    _x += right.x();
    _y += right.y();
}

Vector2f Vector2f::operator-(const Vector2f& right) const
{
    return Vector2f(_x - right.x(), _y - right.y());
}

void Vector2f::operator-=(const Vector2f& right)
{
    _x -= right.x();
    _y -= right.y();
}

Vector2f Vector2f::operator*(const float right) const
{
   return Vector2f(_x * right, _y * right);
}

Vector2f Vector2f::operator/(const float right) const
{
    return Vector2f(_x / right, _y / right);
}

float Vector2f::x() const
{
    return _x;
}

float& Vector2f::x()
{
    return _x;
}

float Vector2f::y() const
{
    return _y;
}

float& Vector2f::y()
{
    return _y;
}

float Vector2f::norm() const
{
    return std::sqrt(normSquare());
}

float Vector2f::normSquare() const
{
    return _x*_x + _y*_y;
}

} // namespace utils
