#include "domain/ball.h"

#include "utils/constants.h"
#include "utils/vector2f.h"
#include "common/ball_info.h"

namespace domain {
struct Ball::Impl: public common::BallInfo
{
    Impl(const utils::Vector2f& initPosition):
        common::BallInfo(std::hash<bool*>()(&_isFixed), initPosition),
        _velocity(utils::Vector2f()),
        _isFixed(false)
    {}

    utils::Vector2f _velocity;
    bool _isFixed;
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
    _d->setPosition(newPosition);
}

const utils::Vector2f& Ball::position() const
{
   return _d->position();
}

void Ball::setVelocity(const utils::Vector2f& newVelocity)
{
    _d->_velocity = newVelocity;
}

const utils::Vector2f& Ball::velocity() const
{
   return _d->_velocity;
}

void Ball::setFixed(const bool fixed)
{
    _d->_isFixed = fixed;
}

bool Ball::isFixed() const
{
    return _d->_isFixed;
}

void Ball::applyForce(const utils::Vector2f& force, const float deltaT)
{
    _d->_velocity += force * deltaT / _d->mass();
}

void Ball::makeStep(const float deltaT)
{
    // TODO добавить отскок на границе
    if (!_d->_isFixed) _d->setPosition(_d->position() + _d->_velocity * deltaT);
}

const common::BallId& Ball::id() const
{
    return _d->id();
}



} // namespace domain
