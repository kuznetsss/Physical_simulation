#ifndef VIEW_RENDER_AREA
#define VIEW_RENDER_AREA

#include <QWidget>

namespace utils {

class Vector2f;

} //namespace utils

namespace presenter {

class IPresenter;

} // namespace presenter

namespace view {

class Ball;

class RenderArea: public QWidget
{
    Q_OBJECT
public:
    RenderArea(QWidget* parent, presenter::IPresenter* iPresenter);

    static constexpr int BORDER_SIZE = 5;
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

protected:
    void paintEvent(QPaintEvent*) override final;
    void timerEvent(QTimerEvent*) override final;

private:
    void drawBackground(QPainter* painter);
    void drawBall(QPainter* painter, const utils::Vector2f& ball);

    presenter::IPresenter* _iPresenter;
};

} // namespace view
#endif // VIEW_RENDER_AREA
