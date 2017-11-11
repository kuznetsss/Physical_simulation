#include "utils/vector2f.h"

#include<math.h>

namespace utils {

Vector2f::Vector2f() = default;

Vector2f::Vector2f(float x, float y):
    _x(x),
    _y(y)
{}

Vector2f operator+(const Vector2f& left, const Vector2f& right)
{
    return Vector2f(left._x + right._x, left._y + right._y);
}

void operator+=(Vector2f& left, const Vector2f& right)
{
    left._x += right._x;
    left._y += right._y;
}

Vector2f operator-(const Vector2f& left, const Vector2f& right)
{
    return Vector2f(left._x - right._x, left._y - right._y);
}

void operator-=(Vector2f& left, const Vector2f& right)
{
    left._x -= right._x;
    left._y -= right._y;
}

Vector2f operator*(const Vector2f& left, const float right)
{
   return Vector2f(left._x * right, left._y * right);
}

Vector2f operator/(const Vector2f& left, const float right)
{
    return Vector2f(left._x / right, left._y / right);
}

bool operator==(const Vector2f& left, const Vector2f& right)
{
    // TODO вынести константу
    const float eps = 0.0001f;
    return std::fabs(left._x - right._x) < eps && std::fabs(left._y - right._y) < eps;
}

bool operator!=(const Vector2f& left, const Vector2f& right)
{
    // TODO вынести константу
    const float eps = 0.0001f;
    return std::fabs(left._x - right._x) > eps || std::fabs(left._y - right._y) > eps;
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

Vector2f Vector2f::normalized() const
{
    const auto n = norm();
    return Vector2f(_x / n, _y / n);
}

} // namespace utils
