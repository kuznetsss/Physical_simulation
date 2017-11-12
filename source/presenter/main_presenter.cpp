#include "presenter/main_presenter.h"

#include <QApplication>

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

}

void MainPresenter::Impl::mouseReleased(QMouseEvent* event)
{

}

void MainPresenter::Impl::mouseMoved(QMouseEvent* event)
{

}

const std::vector<view::Ball>& MainPresenter::Impl::ballsToDraw()
{
    for (auto& ball : _balls) {
        ball.setPosition(_model.ballPosition(ball.id()));
    }
    return _balls;
}

} // namespace presenter
