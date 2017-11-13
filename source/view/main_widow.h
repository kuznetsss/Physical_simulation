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

private:
    QLayout* initHorizontalLayout(QWidget* parent);
    QLayout* initTimePerStepLayout(QWidget* parent);
    QLayout* initControlLayout(QWidget* parent);

    QPushButton* _startStopButton;
    presenter::IPresenter* _iPresenter;

private slots:
    void timePerStepChanged(const QString& text);
    void startStopPressed(bool);
};

} // namespace view
#endif // VIEW_MAIN_WINDOW
