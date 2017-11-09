#ifndef DOMAIN_BALL
#define DOMAIN_BALL

#include <memory>
#include <experimental/propagate_const>

#include "utils/vector2f.h"

namespace domain {

class Ball
{
public:
    Ball();
    Ball(const utils::Vector2f& position);
    ~Ball();

    void setPosition(const utils::Vector2f& newPosition);
    const utils::Vector2f& position() const;

    void setVelocity(const utils::Vector2f& newVelocity);
    const utils::Vector2f& velocity() const;

    void setFixed(bool fixed);
    bool isFixed() const;

    constexpr int radius();

    void applyForce(const utils::Vector2f& force);
    void makeStep();

private:
    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> _d;
};

} // namespace domain

#endif // DOMAIN_BALL
