#include "view/render_area.h"

#include <QPainter>
#include <QTimer>

#include "presenter/i_presenter.h"

namespace view {

RenderArea::RenderArea(QWidget* parent, presenter::IPresenter* iPresenter):
    QWidget(parent),
    _iPresenter(iPresenter),
    _timer(new QTimer(this))
{
    setFixedHeight(2*BORDER_SIZE + HEIGHT);
    setFixedWidth(2*BORDER_SIZE + WIDTH);
    setSizePolicy(QSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed));
    connect(_timer, &QTimer::timeout, this, &RenderArea::timerTimeout);
    _timer->start(40);

}

void RenderArea::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    drawBackground(&painter);
    for (const auto& ball : _iPresenter->ballsToDraw()) {
        drawBall(&painter, ball);
    }
}

void RenderArea::timerTimeout()
{
    repaint();
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
    _iPresenter->mousePressed(event);
}

void RenderArea::mouseReleaseEvent(QMouseEvent* event)
{
    _iPresenter->mouseReleased(event);
}

void RenderArea::mouseMoveEvent(QMouseEvent* event)
{
    _iPresenter->mouseMoved(event);
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

void RenderArea::drawBall(QPainter* painter, const view::Ball& ball)
{
    painter->save();
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(ball.color());
    painter->drawEllipse(BORDER_SIZE + static_cast<int>(ball.position().x()) - ball.RADIUS / 2,
                         BORDER_SIZE + static_cast<int>(ball.position().y()) - ball.RADIUS / 2,
                         ball.RADIUS, ball.RADIUS);
    painter->restore();
}

} // namespace view
