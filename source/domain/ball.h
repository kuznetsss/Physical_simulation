#ifndef DOMAIN_BALL
#define DOMAIN_BALL

#include "utils/common_utils.h"
#include "domain/ball_id.h"

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

    void setVelocity(const utils::Vector2f& newVelocity);
    const utils::Vector2f& velocity() const;

    void setFixed(bool fixed);
    bool isFixed() const;

    constexpr float radius();
    constexpr float mass();

    void applyForce(const utils::Vector2f& force, float deltaT);
    void makeStep(float deltaT);

    BallId id() const;

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

using BallPtr = std::shared_ptr<Ball>;

} // namespace domain
#endif // DOMAIN_BALL
