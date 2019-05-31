#ifndef SOLVERS_H
#define SOLVERS_H

#include <QPoint>
#include <QtEvents>
#include <QKeyEvent>
#include "controller.h"


typedef std::queue<QKeyEvent> instructions;

instructions getInstructionFromType(int type,int direction);

class solver
{
public:
    solver(){m_lastPosition = QPoint(-1,-1);};
    virtual instructions calculProchainesInstructions(camStruct camInformations,  std::shared_ptr<controller> _controller) = 0;
protected:
    QPoint m_lastPosition;
};

class simpleSolver : public solver
{
public:
    simpleSolver(){}
    virtual instructions calculProchainesInstructions(camStruct _camInformations, std::shared_ptr<controller> _controller) override;
    std::vector<int> lookingOrder(QPoint _directions);

};
#endif // SOLVERS_H
