#include "domain/ball.h"

#include "utils/vector2f.h"
#include "common/ball_info.h"
#include "common/field_sizes.h"


namespace domain {

struct Ball::Impl: public common::BallInfo
{
    Impl(const utils::Vector2f& initPosition):
        common::BallInfo(std::hash<bool*>()(&_isFixed), initPosition),
        _speed(utils::Vector2f()),
        _isFixed(false)
    {}

    utils::Vector2f _speed;
    bool _isFixed;
};

Ball::Ball():
    _d(std::make_unique<Impl>(utils::Vector2f(std::rand() % (FIELD_WIDTH - 2 * _d->RADIUS) + _d->RADIUS,
                                              std::rand() % (FIELD_HEIGHT - 2 * _d->RADIUS) + _d->RADIUS)))
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

void Ball::setSpeed(const utils::Vector2f& newSpeed)
{
    _d->_speed = newSpeed;
}

const utils::Vector2f& Ball::speed() const
{
   return _d->_speed;
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
    _d->_speed += force * deltaT / _d->MASS;
}

void Ball::makeStep(const float deltaT)
{
    if (_d->_isFixed) return;

    auto calculateNewPosition = [deltaT, this]() {
        return _d->position() + _d->_speed * deltaT;
    };

    auto newPosition = calculateNewPosition();
    bool speedChanged = false;
    if (newPosition.x() > FIELD_WIDTH - _d->RADIUS || newPosition.x() <  _d->RADIUS)
    {
        _d->_speed = utils::Vector2f(_d->_speed.x() * (-1), _d->_speed.y());
        speedChanged = true;
    }
    if (newPosition.y() > FIELD_HEIGHT - _d->RADIUS || newPosition.y() <  _d->RADIUS)
    {
        _d->_speed = utils::Vector2f(_d->_speed.x(), _d->_speed.y() * (-1));
        speedChanged = true;
    }

    // Если скорость изменилась, нужно пересчитать новую координату
     _d->setPosition(speedChanged ? calculateNewPosition() : newPosition);
}

const common::BallId& Ball::id() const
{
    return _d->id();
}

} // namespace domain
