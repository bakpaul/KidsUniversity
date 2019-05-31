
#ifndef WINDOW_H
#define WINDOW_H

#include "helper.h"

#include <QWidget>
#include <thread>
#include "solvers.h"

class Window : public QWidget
{
   // Q_OBJECT

public:
    Window(int, char**);

    void keyPressEvent(QKeyEvent *_event) override;

    Helper helper;
private:

    std::thread* m_SolverThread;
    simpleSolver tempSolver;
};

#endif
