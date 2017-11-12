#include "presenter/main_presenter.h"

#include <QApplication>
#include <QMouseEvent>
#include <QDebug>

#include "domain/model.h"
#include "view/main_widow.h"
#include "view/render_area.h"
#include "presenter/i_presenter.h"

namespace presenter {

struct MainPresenter::Impl: public IPresenter
{
    Impl();

    void mousePressed(QMouseEvent* event) override final;
    void mouseReleased(QMouseEvent* event) override final;
    void mouseMoved(QMouseEvent* event) override final;
    const std::vector<view::Ball>& ballsToDraw() override final;

    domain::Model _model;
    // Вектор всегда содержит актуальное количество шаров, но не актуальные позиции
    std::vector<view::Ball> _balls;
    utils::Vector2f _buttonPressedPosition = utils::Vector2f();
    common::BallId _fixedBall = common::BallId::NULLID;
    const float _deletingEpsilon = 10.f;
};

MainPresenter::MainPresenter():
    _d(std::make_unique<Impl>())
{}

MainPresenter::~MainPresenter() = default;

int MainPresenter::init(int argc, char** argv)
{
    _d->_model.startSimulation();
    QApplication app(argc, argv);
    view::MainWindow mainWindow(_d.get());
    mainWindow.show();
    return app.exec();
}

MainPresenter::Impl::Impl():
    _model()
{
    for (const auto& ballInfo : _model.ballsInfo()) {
        _balls.emplace_back(ballInfo.id(), ballInfo.position());
    }
}

void MainPresenter::Impl::mousePressed(QMouseEvent* event)
{
    qDebug() << "Mouse pressed: " << event->localPos().x() - view::RenderArea::BORDER_SIZE << "\t" <<
                event->localPos().y() - view::RenderArea::BORDER_SIZE;
    if (event->button() != Qt::MouseButton::LeftButton) return;
    const auto eventPosition = utils::Vector2f(event->localPos().x() - view::RenderArea::BORDER_SIZE,
                                               event->localPos().y() - view::RenderArea::BORDER_SIZE);
    const auto ballId = _model.findBallByPosition(eventPosition);
    if (ballId.isNull()) return;
    _buttonPressedPosition = eventPosition;
    _model.setBallFixed(ballId, true);
    _fixedBall = ballId;
    qDebug() << "Mouse pressed _fixedBall: " << _fixedBall.toStdSizeT();
}

void MainPresenter::Impl::mouseReleased(QMouseEvent* event)
{
    qDebug() << "Mouse released: " << event->localPos().x() - view::RenderArea::BORDER_SIZE << "\t" <<
                event->localPos().y() - view::RenderArea::BORDER_SIZE;
    const auto eventPosition = utils::Vector2f(event->localPos().x() - view::RenderArea::BORDER_SIZE,
                                               event->localPos().y() - view::RenderArea::BORDER_SIZE);
    if (event->button() == Qt::MouseButton::RightButton) {
        if (_model.findBallByPosition(eventPosition).isNull()) {
            const auto newBallId = _model.addBall(eventPosition);
            _balls.emplace_back(newBallId, utils::Vector2f());
        }
    } else if (event->button() == Qt::MouseButton::LeftButton) {
        if (_fixedBall.isNull()) return;
        if ((eventPosition - _buttonPressedPosition).normSquare() > _deletingEpsilon) {
            _model.setBallFixed(_fixedBall, false);
        } else {
        std::remove_if(_balls.begin(), _balls.end(), [this](const auto& ball) { return ball.id() == this->_fixedBall;});
        _model.removeBall(_fixedBall);
        }
    }
    _fixedBall = common::BallId::NULLID;
}

void MainPresenter::Impl::mouseMoved(QMouseEvent* event)
{
    if (event->buttons().testFlag(Qt::MouseButton::LeftButton) && !_fixedBall.isNull()) {
        _model.moveBall(_fixedBall, utils::Vector2f(event->localPos().x() - view::RenderArea::BORDER_SIZE,
                                                    event->localPos().y() - view::RenderArea::BORDER_SIZE));
    }
}

const std::vector<view::Ball>& MainPresenter::Impl::ballsToDraw()
{
    for (auto& ball : _balls) {
        ball.setPosition(_model.ballPosition(ball.id()));
    }
    return _balls;
}

} // namespace presenter
