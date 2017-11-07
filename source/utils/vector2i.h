#ifndef UTILS_VECTOR2I
#define UTILS_VECTOR2I

namespace utils {

class Vector2i
{
public:
    Vector2i();
    Vector2i(int x, int y);

    int x() const;
    int& x();
    int y() const;
    int& y();
    float norm() const;
    float normSquare() const;

private:
    int _x = 0;
    int _y = 0;
};

} // namespace utils

#endif // UTILS_VECTOR2I
