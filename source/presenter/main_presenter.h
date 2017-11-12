#ifndef PRESENTER_MAIN_PRESENTER
#define PRESENTER_MAIN_PRESENTER

#include "utils/common_utils.h"

namespace presenter {

class MainPresenter
{
public:
    MainPresenter();
    ~MainPresenter();

    int init(int argc, char** argv);

private:
    struct Impl;
    utils::ImplPtr<Impl> _d;
};

} // namespace presenter

#endif // PRESENTER_MAIN_PRESENTER
