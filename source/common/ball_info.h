#ifndef COMMON_BALL_INFO
#define COMMON_BALL_INFO

#include "common/ball_id.h"
#include "utils/vector2f.h"

namespace common {

class BallInfo
{
public:
    BallInfo(const BallId& id, const utils::Vector2f& position):
        _id(id),
        _position(position)
    {}

    void setPosition(const utils::Vector2f& newPosition)
    { _position = newPosition; }

    const BallId& id() const
    { return _id; }

    const utils::Vector2f& position() const
    { return _position; }

    static constexpr int RADIUS = 50;
    static constexpr int MASS = 1;

private:
    common::BallId _id;
    utils::Vector2f _position;
};

} // namespace common
#endif // COMMON_BALL_INFO
