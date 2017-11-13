#include "view/main_widow.h"
#include <QDebug>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QRegExpValidator>

#include "presenter/i_presenter.h"
#include "view/render_area.h"

namespace view {

MainWindow::MainWindow(presenter::IPresenter* iPresenter):
    _startStopButton(nullptr),
    _iPresenter(iPresenter)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(initHorizontalLayout(mainLayout->widget()));

    RenderArea* renderArea = new RenderArea(mainLayout->widget(), iPresenter);
    mainLayout->addWidget(renderArea);
    setLayout(mainLayout);
    setFixedSize(sizeHint());
    setWindowTitle(QString("Balls simulator"));
}

QLayout* MainWindow::initHorizontalLayout(QWidget* parent)
{
    QHBoxLayout* horizontalLayout = new QHBoxLayout(parent);

    QLabel* label = new QLabel(horizontalLayout->widget());
    label->setText(tr("Left mouse button click: remove ball.\n"
                      "Left mouse button drag: move ball.\n"
                      "Right mouse button click on free space: add new ball.\n"
                      "\"Time/step\" is the size of simulation step.\n"));
    horizontalLayout->addWidget(label);

    horizontalLayout->addStretch();

    horizontalLayout->addLayout(initControlLayout(horizontalLayout->widget()));

    return horizontalLayout;
}

QLayout* MainWindow::initTimePerStepLayout(QWidget* parent)
{
    QHBoxLayout* timePerStepLayout = new QHBoxLayout(parent);

    QLabel* label = new QLabel(tr("Time/step: "), timePerStepLayout->widget());
    timePerStepLayout->addWidget(label);

    QLineEdit* textBox = new QLineEdit(QString("0.0001"), timePerStepLayout->widget());
    connect(textBox, &QLineEdit::textChanged, this, &MainWindow::timePerStepChanged);
    textBox->setAlignment(Qt::Alignment(Qt::AlignmentFlag::AlignRight));
    const QRegExp regExp("([0][.][0-9]{0,5})|([1][.][0]{0,5})");
    textBox->setValidator(new QRegExpValidator(regExp, timePerStepLayout->widget()));
    timePerStepLayout->addWidget(textBox);

    return timePerStepLayout;
}

QLayout* MainWindow::initControlLayout(QWidget* parent)
{
   QVBoxLayout* controlLayout = new QVBoxLayout(parent);

   _startStopButton = new QPushButton(tr("Stop"), controlLayout->widget());
   QObject::connect(_startStopButton, &QPushButton::clicked, this, &MainWindow::startStopPressed);
   controlLayout->addWidget(_startStopButton);

   controlLayout->addLayout(initTimePerStepLayout(controlLayout->widget()));

   QPushButton* exitButton = new QPushButton(tr("Exit"), controlLayout->widget());
   connect(exitButton, &QPushButton::clicked, this, &QDialog::close);
   controlLayout->addWidget(exitButton);

   return controlLayout;
}

void MainWindow::timePerStepChanged(const QString& text)
{
    _iPresenter->deltaTChanged(text.toFloat());
}

void MainWindow::startStopPressed(bool)
{
    _startStopButton->setText(_startStopButton->text() == "Stop" ? tr("Start") : tr("Stop"));
    _iPresenter->startStopPressed();
}

} // namespace view
