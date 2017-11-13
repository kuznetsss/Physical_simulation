#include "view/render_area.h"

#include <QPainter>

#include "presenter/i_presenter.h"
// TODO тут не должно быть domain
#include "domain/ball.h"

namespace view {

RenderArea::RenderArea(QWidget* parent, presenter::IPresenter* iPresenter):
    QWidget(parent),
    _iPresenter(iPresenter)
{
    setFixedHeight(2*BORDER_SIZE + HEIGHT);
    setFixedWidth(2*BORDER_SIZE + WIDTH);
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
    startTimer(40);
}

void RenderArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    drawBackground(&painter);
    for (const auto& position : _iPresenter->ballsToDraw()) {
        drawBall(&painter, position);
    }
}

void RenderArea::timerEvent(QTimerEvent*)
{
    repaint();
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
    _iPresenter->mousePressed(event);
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
    _iPresenter->mouseMoved(event);
}

void RenderArea::mouseReleaseEvent(QMouseEvent* event)
{
    _iPresenter->mouseReleased(event);
}

void RenderArea::drawBackground(QPainter* painter)
{
    painter->save();
    painter->setPen(QPen(Qt::black, BORDER_SIZE));
    painter->setBrush(Qt::gray);
    const auto rect = QRect(BORDER_SIZE, BORDER_SIZE, WIDTH, HEIGHT);
    painter->drawRect(rect);
    painter->restore();
}

void RenderArea::drawBall(QPainter* painter, const utils::Vector2f& position)
{
    painter->save();
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::red);
    painter->drawEllipse(BORDER_SIZE + static_cast<int>(position.x()) - domain::Ball::RADIUS,
                         BORDER_SIZE + static_cast<int>(position.y())- domain::Ball::RADIUS,
                         2 * domain::Ball::RADIUS, 2 * domain::Ball::RADIUS);
    painter->restore();
}

} // namespace view
