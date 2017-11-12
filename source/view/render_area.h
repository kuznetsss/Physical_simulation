#ifndef VIEW_RENDER_AREA
#define VIEW_RENDER_AREA

#include <QWidget>

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

   private slots:
     void timerTimeout();
protected:
    void paintEvent(QPaintEvent*) override final;

    void mousePressEvent(QMouseEvent* event) override final;
    void mouseReleaseEvent(QMouseEvent* event) override final;
    void mouseMoveEvent(QMouseEvent* event) override final;

private:
    void drawBackground(QPainter* painter);
    void drawBall(QPainter* painter, const view::Ball& ball);

    presenter::IPresenter* _iPresenter;
    QTimer* _timer;
};

} // namespace view
#endif // VIEW_RENDER_AREA
