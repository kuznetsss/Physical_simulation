#include "domain/ball.h"

#include "utils/constants.h"

namespace domain {
struct Ball::Impl
{
    Impl(const utils::Vector2f& initPosition):
        isFixed(false),
        position(initPosition),
        velocity(utils::Vector2f())
    {}

    bool isFixed;
    utils::Vector2f position;
    utils::Vector2f velocity;
    static constexpr float radius = 5.f;
    static constexpr float mass = 1.f;
};

Ball::Ball():
    _d(std::make_unique<Impl>(utils::Vector2f(FIELD_RIGHT_WALL + std::rand() % FIELD_LEFT_WALL,
                                              FIELD_DOWN_WALL + std::rand() % FIELD_UP_WALL)))
{}

Ball::Ball(const utils::Vector2f& position):
    _d(std::make_unique<Impl>(position))
{}

Ball::~Ball() = default;

void Ball::setPosition(const utils::Vector2f& newPosition)
{
    _d->position = newPosition;
}

const utils::Vector2f& Ball::position() const
{
   return _d->position;
}

void Ball::setVelocity(const utils::Vector2f& newVelocity)
{
    _d->velocity = newVelocity;
}

const utils::Vector2f& Ball::velocity() const
{
   return _d->velocity;
}

void Ball::setFixed(const bool fixed)
{
    _d->isFixed = fixed;
}

bool Ball::isFixed() const
{
    return _d->isFixed;
}

constexpr float Ball::radius()
{
    return Impl::radius;
}

constexpr float Ball::mass()
{
   return Impl::mass;
}

void Ball::applyForce(const utils::Vector2f& force, const float deltaT)
{
    _d->velocity += force * deltaT / mass();
}

void Ball::makeStep(const float deltaT)
{
    if (!_d->isFixed) _d->position += _d->velocity * deltaT;
}



} // namespace domain
