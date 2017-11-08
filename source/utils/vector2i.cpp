#include "utils/vector2i.h"

#include<math.h>

namespace utils {

Vector2i::Vector2i() = default;

Vector2i::Vector2i(int x, int y):
    _x(x),
    _y(y)
{}

Vector2i Vector2i::operator+(const Vector2i& right) const
{
    return Vector2i(_x + right.x(), _y + right.y());
}

void Vector2i::operator+=(const Vector2i& right)
{
    _x += right.x();
    _y += right.y();
}

Vector2i Vector2i::operator-(const Vector2i& right) const
{
    return Vector2i(_x + right.x(), _y + right.y());
}

void Vector2i::operator-=(const Vector2i& right)
{
    _x -= right.x();
    _y -= right.y();
}

Vector2i Vector2i::operator*(const int right) const
{
   return Vector2i(_x * right, _y * right);
}

Vector2i Vector2i::operator/(const int right) const
{
    return Vector2i(_x / right, _y / right);
}

int Vector2i::x() const
{
    return _x;
}

int& Vector2i::x()
{
    return _x;
}

int Vector2i::y() const
{
    return _y;
}

int& Vector2i::y()
{
    return _y;
}

float Vector2i::norm() const
{
    return std::sqrt(normSquare());
}

float Vector2i::normSquare() const
{
    return static_cast<float>(_x*_x + _y*_y);
}

} // namespace utils
