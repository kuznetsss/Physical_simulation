#ifndef UTILS_BALL_ID
#define UTILS_BALL_ID

#include <cstddef>

namespace utils {

class Id
{
public:
    Id(const std::size_t id):
        _id(id)
    {}

    bool isNull() const
    { return _id == NULLID; }

    std::size_t toStdSizeT() const
    { return _id; }

    friend bool operator==(const Id& left, const Id& right);

    friend bool operator!=(const Id& left, const Id& right);

    static constexpr std::size_t NULLID = 0;

private:
    const std::size_t _id;
};

inline bool operator==(const Id& left, const Id& right)
{ return left._id == right._id; }

inline bool operator!=(const Id& left, const Id& right)
{ return left._id != right._id; }

} // namespace utils
#endif // UTILS_BALL_ID
