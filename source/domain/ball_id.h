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

    std::size_t toStdSizeT() const
    { return _id; }

    friend bool operator==(const BallId& left, const BallId& right);

    bool operator!=(const BallId& right) const
    { return _id != right.toStdSizeT(); }

    static constexpr std::size_t NULLID = 0;

private:
    const std::size_t _id;
};

inline bool operator==(const BallId& left, const BallId& right)
{ return left.toStdSizeT() == right.toStdSizeT(); }

} // namespace domain

#endif // DOMAIN_BALL_ID
