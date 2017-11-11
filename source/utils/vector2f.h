#ifndef UTILS_VECTOR2F
#define UTILS_VECTOR2F

namespace utils {

class Vector2f
{
public:
    Vector2f();
    Vector2f(float x, float y);

    friend Vector2f operator+(const Vector2f& left, const Vector2f& right);
    friend void operator+=(Vector2f& left, const Vector2f& right);

    friend Vector2f operator-(const Vector2f& left, const Vector2f& right);
    friend void operator-=(Vector2f& left, const Vector2f& right);

    friend Vector2f operator*(const Vector2f& left, const float right);
    friend Vector2f operator/(const Vector2f& left, const float right);

    friend bool operator==(const Vector2f& left, const Vector2f& right);
    friend bool operator!=(const Vector2f& left, const Vector2f& right);

    float x() const;
    float& x();
    float y() const;
    float& y();
    float norm() const;
    float normSquare() const;
    Vector2f normalized() const;

private:
    float _x = 0;
    float _y = 0;
};

} // namespace utils

#endif // UTILS_VECTOR2F
