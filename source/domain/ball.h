#ifndef DOMAIN_BALL
#define DOMAIN_BALL

#include "utils/common_utils.h"

namespace common {

class BallId;

} // namespace common

namespace utils {

class Vector2f;

} //namespace utils

namespace domain {

class Ball: public utils::NonCopyable
{
public:
    Ball();
    explicit Ball(const utils::Vector2f& position);
    ~Ball();

    void setPosition(const utils::Vector2f& newPosition);
    const utils::Vector2f& position() const;

    void setSpeed(const utils::Vector2f& newSpeed);
    const utils::Vector2f& speed() const;

    void setFixed(bool fixed);
    bool isFixed() const;

    void applyForce(const utils::Vector2f& force, float deltaT);
    void makeStep(float deltaT);

    const common::BallId& id() const;

    static constexpr int RADIUS = 25;
    static constexpr int MASS = 1;

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

using BallPtr = std::shared_ptr<Ball>;

} // namespace domain
#endif // DOMAIN_BALL
