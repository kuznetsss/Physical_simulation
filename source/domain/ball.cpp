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
    static constexpr int radius = 5;
    static constexpr int mass = 1;
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

constexpr int Ball::radius()
{
    return _d->radius;
}

void Ball::applyForce(const utils::Vector2f& force)
{
    _d->velocity += force / _d->mass;
}

void Ball::makeStep()
{
    _d->position += _d->velocity;
}



} // namespace domain
