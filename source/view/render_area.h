#ifndef VIEW_RENDER_AREA
#define VIEW_RENDER_AREA

#include <QWidget>

namespace view {

class RenderArea: public QWidget
{
    Q_OBJECT
public:
    RenderArea(QWidget* parent);
    void paintEvent(QPaintEvent*);

    static constexpr int BORDER_SIZE = 5;
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

private:
    void drawBackground(QPainter* painter);
};

} // namespace view
#endif // VIEW_RENDER_AREA
