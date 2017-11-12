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

    float radius() const
    { return _radius; }

    float mass() const
    { return _mass; }

private:
    const common::BallId _id;
    utils::Vector2f _position;
    static constexpr float _radius = 50.f;
    static constexpr float _mass = 1.f;
};

} // namespace common
#endif // COMMON_BALL_INFO
