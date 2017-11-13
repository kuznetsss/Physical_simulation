#include "presenter/main_presenter.h"

#include <QApplication>
#include <QMouseEvent>

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
    std::vector<BallDrawingInfo> ballsToDraw() override final;

    static utils::Vector2f convertToModelCordinates(const QPointF& position);

    domain::Model _model;
    utils::Id _fixedBall;
    utils::Vector2f _mouseButtonPressPosition;
    static constexpr float MINIMUM_MOVE_PATH = 5.;
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
    _model(),
    _fixedBall(utils::Id::NULLID)
{}

void MainPresenter::Impl::mousePressed(QMouseEvent* event)
{
    if (event->button() != Qt::MouseButton::LeftButton) return;
    const auto eventPosition = Impl::convertToModelCordinates(event->localPos());
    const auto id = _model.findBallByPosition(eventPosition);
    if (id.isNull()) return;
    _model.setBallFixed(id, true);
    _fixedBall = id;
    _mouseButtonPressPosition = eventPosition;
}

void MainPresenter::Impl::mouseMoved(QMouseEvent* event)
{
    if (_fixedBall.isNull() || !event->buttons().testFlag(Qt::MouseButton::LeftButton)) return;
    const auto eventPosition =  Impl::convertToModelCordinates(event->localPos());
    _model.moveBall(_fixedBall, eventPosition);
}

void MainPresenter::Impl::mouseReleased(QMouseEvent* event)
{
    const auto eventPosition =  Impl::convertToModelCordinates(event->localPos());
    if (event->button() == Qt::MouseButton::RightButton) {
        _model.addBall(eventPosition);
        return;
    }
    if (_fixedBall.isNull()) return;
    if (event->button() == Qt::MouseButton::LeftButton &&
            (eventPosition - _mouseButtonPressPosition).normSquare() < Impl::MINIMUM_MOVE_PATH) {
        _model.removeBall(_fixedBall);
    } else {
        _model.setBallFixed(_fixedBall, false);
    }
    _fixedBall = utils::Id::NULLID;
}

std::vector<BallDrawingInfo> MainPresenter::Impl::ballsToDraw()
{
    std::vector<BallDrawingInfo> result;
    for (const auto& position : _model.ballsPositions()) {
        result.emplace_back(position);
    }
    return result;
}

utils::Vector2f MainPresenter::Impl::convertToModelCordinates(const QPointF &position)
{
    return utils::Vector2f(position.x() - view::RenderArea::BORDER_SIZE, position.y() - view::RenderArea::BORDER_SIZE);
}

} // namespace presenter
