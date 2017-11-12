#ifndef PRESENTER_I_PRESENTER
#define PRESENTER_I_PRESENTER

#include <vector>
#include "view/ball.h"

class QMouseEvent;

namespace presenter {

class IPresenter
{
public:
    virtual ~IPresenter() = default;
    virtual void mousePressed(QMouseEvent* event) = 0;
    virtual void mouseReleased(QMouseEvent* event) = 0;
    virtual void mouseMoved(QMouseEvent* event) = 0;
    virtual const std::vector<view::Ball>& ballsToDraw() = 0;
};

} // namespace presenter
#endif // PRESENTER_I_PRESENTER
