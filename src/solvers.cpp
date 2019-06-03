#include "solvers.h"

instructions getInstructionFromType(std::pair<int,int> _type, int _direction)
{
    instructions returnObj;
    switch(_direction)
    {
    case(0):
        returnObj.push(QKeyEvent(QEvent::KeyPress,Qt::Key_Right,Qt::NoModifier));
        break;
    case(1):
        returnObj.push(QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier));
        break;
    case(2):
        returnObj.push(QKeyEvent(QEvent::KeyPress,Qt::Key_Left,Qt::NoModifier));
        break;
    case(3):
        returnObj.push(QKeyEvent(QEvent::KeyPress,Qt::Key_Down,Qt::NoModifier));
        break;
    default:
        break;
    }
    if((_type.second == 4)&&(_type.first==1))
        returnObj.push(QKeyEvent(QEvent::KeyPress,Qt::Key_Exclam,Qt::NoModifier));

    return returnObj;
}

/******************************************************************************
 * Simple solver
 *****************************************************************************/

instructions simpleSolver::calculProchainesInstructions(camStruct _camInformations, std::shared_ptr<controller> _controller)
{
    std::vector<int> order;
    instructions emptyInst;
    if(m_lastPosition.x()==-1)
    {
        order = lookingOrder(QPoint(0,0));
    }
    else
    {
        order = lookingOrder(_controller->getRobotPosition().first - m_lastPosition);
    }
    m_lastPosition = _controller->getRobotPosition().first;
    if( _controller->getRobotPosition().second == 2)
    {
        emptyInst.push(QKeyEvent(QEvent::KeyPress,Qt::Key_Up,Qt::NoModifier));
        return emptyInst;
    }
    for(int i = 0; i<order.size();i++)
    {
        switch(order[i])
        {
        case(0):
            if((_camInformations.right.second!=1)||(_camInformations.right.first>1))
            {
                return getInstructionFromType(_camInformations.right,order[i]);
            }
            break;
        case(1):
            if((_camInformations.up.second!=1)||(_camInformations.up.first>1))
            {
                return getInstructionFromType(_camInformations.up,order[i]);
            }
            break;
        case(2):
            if((_camInformations.left.second!=1)||(_camInformations.left.first>1))
            {
                return getInstructionFromType(_camInformations.left,order[i]);
            }
            break;
        case(3):

            if((_camInformations.down.second!=1)||(_camInformations.down.first>1))
            {
                return getInstructionFromType(_camInformations.down,order[i]);
            }
            break;
        default:
            break;
        }
    }
    return emptyInst;
}



std::vector<int> simpleSolver::lookingOrder(QPoint _directions)
{
    std::vector<int> returnObj;
    if(_directions.y() <= -1)
    {
        returnObj.push_back(0);
        returnObj.push_back(1);
        returnObj.push_back(2);
        returnObj.push_back(3);
    }
    else if(_directions.y() >= 1)
    {
        returnObj.push_back(2);
        returnObj.push_back(3);
        returnObj.push_back(0);
        returnObj.push_back(1);
    }
    else if(_directions.x() >= 1)
    {
        returnObj.push_back(3);
        returnObj.push_back(0);
        returnObj.push_back(1);
        returnObj.push_back(2);
    }
    else if(_directions.x() <= -1)
    {
        returnObj.push_back(1);
        returnObj.push_back(2);
        returnObj.push_back(3);
        returnObj.push_back(0);
    }
    else
    {
        returnObj.push_back(0);
        returnObj.push_back(1);
        returnObj.push_back(2);
        returnObj.push_back(3);
    }
    return returnObj;
}

/******************************************************************************
 * Graph solver
 *****************************************************************************/

instructions graphSolver::calculProchainesInstructions(camStruct _camInformations, std::shared_ptr<controller> _controller)
{

    instructions returnObj;
    return returnObj;
}

