#ifndef PRESENTER_I_PRESENTER
#define PRESENTER_I_PRESENTER

#include <vector>
#include "utils/vector2f.h"
#include "domain/ball.h"

class QMouseEvent;

namespace presenter {

struct BallDrawingInfo
{
    BallDrawingInfo(const utils::Vector2f& pos):
        position(pos)
    {}

    utils::Vector2f position;
    static constexpr int RADIUS = static_cast<int>(domain::Ball::RADIUS);
};

class IPresenter
{
public:
    virtual ~IPresenter() = default;
    virtual void mousePressed(QMouseEvent* event) = 0;
    virtual void mouseReleased(QMouseEvent* event) = 0;
    virtual void mouseMoved(QMouseEvent* event) = 0;
    virtual std::vector<BallDrawingInfo> ballsToDraw() const = 0;

    virtual void deltaTChanged(const float newValue) = 0;
    virtual float deltaT() const = 0;
    virtual void startStopPressed() = 0;
};


} // namespace presenter
#endif // PRESENTER_I_PRESENTER
