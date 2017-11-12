#include <ctime>
#include "presenter/main_presenter.h"

int main(int argc, char** argv)
{
    std::srand(std::time(nullptr));
    presenter::MainPresenter mainPresenter;
    return mainPresenter.init(argc, argv);
}
