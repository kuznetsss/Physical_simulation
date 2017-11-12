#include "view/main_widow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "view/render_area.h"

namespace view {

MainWindow::MainWindow(presenter::IPresenter* iPresenter)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* horizontalLayout = new QHBoxLayout(mainLayout->widget());

    QLabel* label = new QLabel(horizontalLayout->widget());
    label->setText(QString(tr("Left mouse button click: remove ball.\nLeft mouse button drag: move ball.\n"
                           "Right mouse button click on free space: add new ball.")));
    horizontalLayout->addWidget(label);

    horizontalLayout->addStretch();

    QPushButton* exitButton = new QPushButton(tr("Exit"), horizontalLayout->widget());
    connect(exitButton, &QPushButton::clicked, this, &QDialog::close);
    horizontalLayout->addWidget(exitButton);

    mainLayout->addLayout(horizontalLayout);

    RenderArea* renderArea = new RenderArea(mainLayout->widget(), iPresenter);
    mainLayout->addWidget(renderArea);
    setLayout(mainLayout);
    setFixedSize(sizeHint());
    setWindowTitle(QString("Balls simulator"));
}

} // namespace view
