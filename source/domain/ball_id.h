#ifndef DOMAIN_BALL_ID
#define DOMAIN_BALL_ID

#include <cstddef>

namespace domain {

class BallId
{
public:
    BallId(const std::size_t id):
        _id(id)
    {}

    bool isNull() const
    { return _id == NULLID; }

    std::size_t toStdSizeT() const
    { return _id; }

    friend bool operator==(const BallId& left, const BallId& right);

    friend bool operator!=(const BallId& left, const BallId& right);

    static constexpr std::size_t NULLID = 0;

private:
    const std::size_t _id;
};

inline bool operator==(const BallId& left, const BallId& right)
{ return left._id == right._id; }

inline bool operator!=(const BallId& left, const BallId& right)
{ return left._id != right._id; }
} // namespace domain

#endif // DOMAIN_BALL_ID
