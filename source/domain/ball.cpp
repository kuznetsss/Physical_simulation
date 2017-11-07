#include "domain/ball.h"

#include "utils/constants.h"

namespace domain {
struct Ball::Impl
{
    Impl(const utils::Vector2i& initPosition):
        isFixed(false),
        position(initPosition),
        velocity(utils::Vector2i())
    {}

    bool isFixed;
    utils::Vector2i position;
    utils::Vector2i velocity;
    static constexpr int radius = 5;
};

Ball::Ball():
    _d(std::make_unique<Impl>(utils::Vector2i(FIELD_RIGHT_WALL + std::rand() % FIELD_LEFT_WALL,
                                              FIELD_DOWN_WALL + std::rand() % FIELD_UP_WALL)))
{}

Ball::Ball(const utils::Vector2i& position):
    _d(std::make_unique<Impl>(position))
{}

Ball::~Ball() = default;

void Ball::setPosition(const utils::Vector2i& newPosition)
{
    _d->position = newPosition;
}

const utils::Vector2i& Ball::position() const
{
   return _d->position;
}

void Ball::setVelocity(const utils::Vector2i& newVelocity)
{
    _d->velocity = newVelocity;
}

const utils::Vector2i& Ball::velocity() const
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

} // namespace domain
