#include "domain/ball.h"

#include "utils/constants.h"
#include "utils/vector2f.h"

namespace domain {
struct Ball::Impl
{
    Impl(const utils::Vector2f& initPosition):
        _position(initPosition),
        _velocity(utils::Vector2f()),
        _id(std::hash<bool*>()(&_isFixed)),
        _isFixed(false)
    {}

    utils::Vector2f _position;
    utils::Vector2f _velocity;
    const BallId _id;
    bool _isFixed;
    static constexpr float _radius = 5.f;
    static constexpr float _mass = 1.f;
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
    _d->_position = newPosition;
}

const utils::Vector2f& Ball::position() const
{
   return _d->_position;
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

constexpr float Ball::radius()
{
    return Impl::_radius;
}

constexpr float Ball::mass()
{
    return Impl::_mass;
}

void Ball::applyForce(const utils::Vector2f& force, const float deltaT)
{
    _d->_velocity += force * deltaT / mass();
}

void Ball::makeStep(const float deltaT)
{
    if (!_d->_isFixed) _d->_position += _d->_velocity * deltaT;
}

BallId Ball::id() const
{
    return _d->_id;
}



} // namespace domain
