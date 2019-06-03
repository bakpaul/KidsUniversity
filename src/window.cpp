#include "glwidget.h"
#include "window.h"
#include "controller.h"

#include <QGridLayout>
#include <QLabel>
#include <QTimer>
#include <QKeyEvent>


void automThread(Window*,std::shared_ptr<solver>);

Window::Window(int _a, char** _c) : helper(_a,_c)
{
    setWindowTitle(tr("Kid's university"));

    GLWidget *openGL = new GLWidget(&helper, this);
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(openGL, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
    timer->start(100);

    std::string autom = "a";
    //simpleSolver _solver;
    m_tempSolver = std::shared_ptr<solver>(new simpleSolver());
    if(!strcmp(_c[_a-1],autom.c_str()))
    {
        m_SolverThread = new std::thread(automThread,this,m_tempSolver);
        m_SolverThread->detach();
    }
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
        case(Qt::Key_R) :
        {
            helper.reinit();
            break;
        }
        case(Qt::Key_Space) :
        {
            helper.m_controller->initInstructions();
            break;
        }
        case(Qt::Key_Control) :
        {
            helper.m_controller->toggleVisibility();
            break;
        }
        case(Qt::Key_Plus) :
        {
            helper.m_controller->decrWaitTime();
            break;
        }
        case(Qt::Key_Minus) :
        {
            helper.m_controller->incrWaitTime();
            break;
        }
        default:
        {
            break;
        }
    }

}
