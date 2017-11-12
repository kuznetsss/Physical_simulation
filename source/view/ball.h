#ifndef VIEW_BALL
#define VIEW_BALL

#include <QColor>
#include "common/ball_info.h"

namespace view {

class Ball: public common::BallInfo
{
public:
    Ball(const common::BallId& id, const utils::Vector2f& position, const QColor& color = QColor(Qt::red)):
        common::BallInfo(id, position),
        _color(color)
    {}

    const QColor& color() const
    { return _color; }

private:
    const QColor _color;
};

}
#endif // VIEW_BALL
