#ifndef DOMAIN_BALL
#define DOMAIN_BALL

#include <memory>
#include <experimental/propagate_const>

#include "utils/vector2f.h"
#include "utils/non_copyable.h"

namespace domain {

class Ball: public utils::NonCopyable
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

    constexpr float radius();
    constexpr float mass();

    void applyForce(const utils::Vector2f& force, float deltaT);
    void makeStep(float deltaT);

private:
    struct Impl;
    std::experimental::propagate_const<std::unique_ptr<Impl>> _d;
};

} // namespace domain

#endif // DOMAIN_BALL
