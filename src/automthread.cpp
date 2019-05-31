#include "automthread.h"
#include <thread>


void automThread(Window* _parent, std::shared_ptr<solver> _solver)
{
    while(_parent->helper.m_controller->getRobotPosition().second != 3)
    {
        std::this_thread::sleep_for(std::chrono::duration<int,std::milli>(1000));
        camStruct informationCamera = _parent->helper.m_controller->getInformationFromCamera();
        instructions prochainesInstructions = _solver->calculProchainesInstructions(informationCamera,_parent->helper.m_controller);
        envoisInstructions(prochainesInstructions,_parent);
        std::this_thread::sleep_for(std::chrono::duration<int,std::milli>(500));
        executeInstructions(_parent);
    }
}


void envoisInstructions(instructions _instructions,Window* _parent)
{
    while(_instructions.size())
    {
        _parent->keyPressEvent(&(_instructions.front()));
        _instructions.pop();
    }
}

void executeInstructions(Window* _parent)
{
    QKeyEvent executeInstructionsEvent(QEvent::KeyPress,Qt::Key_Return,Qt::NoModifier);
    _parent->keyPressEvent(&(executeInstructionsEvent));
}



