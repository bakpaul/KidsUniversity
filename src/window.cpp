#include "glwidget.h"
#include "window.h"
#include "controller.h"

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
    timer->start(20);
}


void Window::keyPressEvent(QKeyEvent *_event)
{
    switch(_event->key())
    {
        case(Qt::Key_Right) :
        {
            helper.m_controller->addInstructions(0);
            break;
        }
        case(Qt::Key_Up) :
        {
            helper.m_controller->addInstructions(1);
            break;
        }
        case(Qt::Key_Left) :
        {
            helper.m_controller->addInstructions(2);
            break;
        }
        case(Qt::Key_Down) :
        {
            helper.m_controller->addInstructions(3);
            break;
        }
        case(Qt::Key_Exclam) :
        {
            helper.m_controller->addInstructions(4);
            break;
        }
        case(Qt::Key_Return) :
        {
            helper.m_controller->executeInstructions();
            break;
        }
        default:
        {
            break;
        }
    }

}
