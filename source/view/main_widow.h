#ifndef VIEW_MAIN_WINDOW
#define VIEW_MAIN_WINDOW

#include <QDialog>

namespace presenter {

class IPresenter;

} // namespace presenter

namespace view {

class MainWindow: public QDialog
{
    Q_OBJECT
public:
    MainWindow(presenter::IPresenter* iPresenter);
};

} // namespace view
#endif // VIEW_MAIN_WINDOW
