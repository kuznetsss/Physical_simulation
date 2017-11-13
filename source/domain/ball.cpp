#include "domain/ball.h"

#include "utils/vector2f.h"
#include "utils/id.h"
#include "common/field_sizes.h"


namespace domain {

struct Ball::Impl
{
    Impl(const utils::Vector2f& initPosition):
        _id(std::hash<bool*>()(&_isFixed)),
        _position(initPosition),
        _speed(utils::Vector2f()),
        _isFixed(false)
    {}

    const utils::Id _id;
    utils::Vector2f _position;
    utils::Vector2f _speed;
    bool _isFixed;
};

Ball::Ball():
    _d(std::make_unique<Impl>(utils::Vector2f(std::rand() % (FIELD_WIDTH - 2 * RADIUS) + RADIUS,
                                              std::rand() % (FIELD_HEIGHT - 2 * RADIUS) + RADIUS)))
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
    _d->_speed += force * deltaT / MASS;
}

void Ball::makeStep(const float deltaT)
{
    if (_d->_isFixed) return;

    auto calculateNewPosition = [deltaT, this]() {
        return _d->_position + _d->_speed * deltaT;
    };

    auto newPosition = calculateNewPosition();
    bool speedChanged = false;
    if (newPosition.x() > FIELD_WIDTH - RADIUS || newPosition.x() <  RADIUS)
    {
        _d->_speed = utils::Vector2f(_d->_speed.x() * (-1), _d->_speed.y());
        speedChanged = true;
    }
    if (newPosition.y() > FIELD_HEIGHT - RADIUS || newPosition.y() <  RADIUS)
    {
        _d->_speed = utils::Vector2f(_d->_speed.x(), _d->_speed.y() * (-1));
        speedChanged = true;
    }

    // Если скорость изменилась, нужно пересчитать новую координату
    setPosition(speedChanged ? calculateNewPosition() : newPosition);
}

const utils::Id& Ball::id() const
{
    return _d->_id;
}

} // namespace domain
