#include "glwidget.h"
#include "window.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>

Window::Window(int _a, char** _c) : helper(_a,_c)
{
    setWindowTitle(tr("Kid's university"));

    GLWidget *openGL = new GLWidget(&helper, this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(openGL, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
    timer->start(1);
}
