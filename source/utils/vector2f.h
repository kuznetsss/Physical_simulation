#ifndef UTILS_VECTOR2F
#define UTILS_VECTOR2F

namespace utils {

class Vector2f
{
public:
    Vector2f();
    Vector2f(float x, float y);

    Vector2f operator+(const Vector2f& right) const;
    void operator+=(const Vector2f& right);

    Vector2f operator-(const Vector2f& right) const;
    void operator-=(const Vector2f& right);

    Vector2f operator*(const float right) const;
    Vector2f operator/(const float right) const;

    float x() const;
    float& x();
    float y() const;
    float& y();
    float norm() const;
    float normSquare() const;

private:
    float _x = 0;
    float _y = 0;
};

} // namespace utils

#endif // UTILS_VECTOR2F
