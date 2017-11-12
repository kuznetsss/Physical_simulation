#include "presenter/main_presenter.h"

#include <QApplication>

#include "domain/model.h"

namespace presenter {

struct MainPresenter::Impl
{
    domain::Model _model;
};

MainPresenter::MainPresenter():
    _d(std::make_unique<Impl>())
{}

MainPresenter::~MainPresenter() = default;

int MainPresenter::init(int argc, char** argv)
{
    _d->_model.startSimulation();
    QApplication app(argc, argv);
    return app.exec();
}

} // namespace presenter
