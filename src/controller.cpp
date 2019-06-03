#include "controller.h"


controller::controller(std::string _filename, std::shared_ptr<robot> _robot, std::shared_ptr<parcours> _parcours) : m_robot(_robot), m_parcours(_parcours)
{
    m_score = 0;
    m_scoreIcon.load(_filename.c_str());
    m_waitTime = 1400;
    //m_scoreIcon.load();
}

controller::~controller()
{

}

QString controller::instrunction2char(int _i)
{
    switch(_i)
    {
    case(0):
    {
        return QString(0x2192);
    }
    case(1):
    {
        return QString(0x2191);
    }
    case(2):
    {
        return QString(0x2190);
    }
    case(3):
    {
        return QString(0x2193);
    }
    case(4):
    {
        return QString(0x26A0);
    }
    default:
    {
        return QString(' ');
    }
    }
}

void controller::draw(QPainter *_painter, QPaintEvent *_event, long long _elapsed)
{
    QFont font;
    QPen pen(Qt::black);
    pen.setWidth(5);
    QBrush brush(Qt::transparent);
    double ratio_factor_ratio = fmin(1,(((double)_event->rect().width())/(_event->rect().height()))/RATIO_FACTOR);

    _painter->save();

    _painter->translate(_event->rect().width()-0.95*(1/3.0+1/9.0)*_event->rect().height()*ratio_factor_ratio, _event->rect().height()/2.0);

    font.setPixelSize(0.95*ratio_factor_ratio/6.0*_event->rect().height());
    _painter->setFont(font);
    _painter->setPen(pen);
    _painter->setBrush(brush);

    //Score rectangle
    _painter->translate(0,-0.95*(0.5)*_event->rect().height()*ratio_factor_ratio);
    _painter->drawRect(0,0,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio,0.95*(1/6.0)*_event->rect().height()*ratio_factor_ratio);

    //draw icon
    _painter->save();
    int imgSize = 1*0.95*(1/6.0)*_event->rect().height()*ratio_factor_ratio;
    QImage iconTemp = m_scoreIcon.scaled(imgSize*0.9,imgSize*0.9,Qt::KeepAspectRatio);
    _painter->translate(0.1*imgSize,0.05*imgSize);
    _painter->drawImage(QPoint(1,1)*0.1*0.95*(1/6.0)*_event->rect().height()*ratio_factor_ratio,iconTemp,QRect(0,0,imgSize,imgSize));
    _painter->restore();
    _painter->drawText(QRect(imgSize/2,0,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio-imgSize/2,0.95*(1/6.0)*_event->rect().height()*ratio_factor_ratio), Qt::AlignCenter, std::to_string(m_score).c_str());

    //Instructions rectangles
    font.setPixelSize(0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio);
    _painter->setFont(font);
    _painter->translate(0,0.95*(1.5/6)*_event->rect().height()*ratio_factor_ratio);
    _painter->drawRect(0,0,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio);

    if(m_instruction.size()==2)
        _painter->drawText(QRect(0,0,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio), Qt::AlignCenter, instrunction2char(m_instruction.front()));

    _painter->translate(0,0.95*(2.5/6)*_event->rect().height()*ratio_factor_ratio);
    _painter->drawRect(0,0,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio);

    if(m_instruction.size()>0)
        _painter->drawText(QRect(0,0,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio,0.95*(1/3.0)*_event->rect().height()*ratio_factor_ratio), Qt::AlignCenter,  instrunction2char(m_instruction.back()));

    _painter->restore();
    QPointF robotPos = m_parcours->m_origin+m_parcours->m_carreSize*QPointF(m_robot->m_position.x()+0.1,m_robot->m_position.y()+0.1);
    QImage imgTemp = m_robot->m_image.scaled(m_parcours->m_carreSize*0.8,m_parcours->m_carreSize*0.8,Qt::KeepAspectRatio);
    _painter->drawImage(robotPos,imgTemp,QRect(0,0,m_parcours->m_carreSize,m_parcours->m_carreSize));



}

void controller::initRobotPosition()
{
    QPoint pos(0,0);
    for(int i=0;i<m_parcours->m_map.size();i++)
    {
        for(int j=0;j<m_parcours->m_map[0].size();j++)
        {
            if(m_parcours->m_map[i][j]==2)
            {
                pos.setX(j);
                pos.setY(i);
            }
        }
    }
    m_robot->m_position = pos;
    camStruct upDate = getInformationFromCamera();
    applyInformationsFromCamera(upDate);
}

void controller::addInstructions(int _i)
{
    if(m_instruction.size()==2)
    {
        m_instruction.pop();
        m_instruction.push(_i);
    }
    else
    {
        m_instruction.push(_i);
    }
}

void controller::initInstructions()
{
    while(m_instruction.size())
    {
        m_instruction.pop();
    }
}

void controller::executeInstructions()
{
    bool pending = false;
    bool Warn = false;
    int lastInstr=4;
    int instr=4;
    while(m_instruction.size())
    {
        instr = m_instruction.front();
        m_instruction.pop();
        if(instr<4)
        {
            int VFI = getValueFromInstruction(instr);
            switch(VFI)
            {
            case 0:
                setNewPositionFromInstruction(instr);
                break;
            case 1:
                m_score++;
                break;
            case 2:
                setNewPositionFromInstruction(instr);
                break;
            case 3:
                setNewPositionFromInstruction(instr);
                break;
            case 4:
                if(m_instruction.size())
                    pending = true;
                else
                {
                    if(Warn)
                    {
                        setNewPositionFromInstruction(instr);
                    }
                    else
                    {
                        m_score++;
                    }
                }
                break;
            default:
                break;
            }
        }
        else
        {
            if(m_instruction.size())
            {
                Warn = true;
            }
            else if(pending)
            {
                pending = false;
                setNewPositionFromInstruction(lastInstr);
                setNewPositionFromInstruction(lastInstr);
            }
            else if(!pending)
            {
                Warn = true;
            }
        }
        if(m_instruction.size())
            lastInstr = instr;
    }
    if(pending)
        m_score++;
    if(Warn) //See if it works
    {
        if(lastInstr==4)
        {
            if(!getValueFromInstruction(instr))
                setNewPositionFromInstruction(instr);
            else
                m_score++;
        }
        else
        {
            if(!getValueFromInstruction(lastInstr))
                setNewPositionFromInstruction(lastInstr);
            else
                m_score++;
        }
    }

    //    TODO
    camStruct upDate = getInformationFromCamera();
    applyInformationsFromCamera(upDate);

}

void controller::applyInformationsFromCamera(camStruct upDate)
{
    m_parcours->m_mapMask[m_robot->m_position.y()][m_robot->m_position.x()+upDate.right.first] = 1;
    m_parcours->m_mapMask[m_robot->m_position.y()-upDate.up.first][m_robot->m_position.x()] = 1;
    m_parcours->m_mapMask[m_robot->m_position.y()][m_robot->m_position.x()-upDate.left.first] = 1;
    m_parcours->m_mapMask[m_robot->m_position.y()+upDate.down.first][m_robot->m_position.x()] = 1;
}

int controller::getValueFromInstruction(int _instr)
{
    int returnObj = 0;
    switch (_instr) {
    case 0 :
        if(m_parcours->m_map[0].size()==m_robot->m_position.x()+1)
            returnObj = -1;
        else
            returnObj = m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()+1];
        break;
    case 1 :
        if(-1==m_robot->m_position.y()-1)
            returnObj = -1;
        else
            returnObj = m_parcours->m_map[m_robot->m_position.y()-1][m_robot->m_position.x()];
        break;
    case 2 :
        if(-1==m_robot->m_position.x()-1)
            returnObj = -1;
        else
            returnObj = m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()-1];
        break;
    case 3 :
        if(m_parcours->m_map.size()==m_robot->m_position.y()+1)
            returnObj = -1;
        else
            returnObj = m_parcours->m_map[m_robot->m_position.y()+1][m_robot->m_position.x()];
        break;
    default:
        break;
    }
    return returnObj;
}

void controller::setNewPositionFromInstruction(int _instr)
{
    switch (_instr) {
    case 0 :
        m_robot->m_position.setX( m_robot->m_position.x()+1);
        break;
    case 1 :
        m_robot->m_position.setY( m_robot->m_position.y()-1);
        break;
    case 2 :
        m_robot->m_position.setX( m_robot->m_position.x()-1);
        break;
    case 3 :
        m_robot->m_position.setY( m_robot->m_position.y()+1);
        break;
    default:
        break;
    }
}

void controller::reinit()
{
    m_score = 0;
    while(m_instruction.size())
        m_instruction.pop();
    initRobotPosition();
}

camStruct controller::getInformationFromCamera() //TODO
{
    camStruct returnObj;
    for(unsigned j =0;j<4;j++)
    {
        int i = 0;
        switch (j) {
        case 0 :
            while(!(m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()+i]))
            {
                m_parcours->m_mapMask[m_robot->m_position.y()][m_robot->m_position.x()+i] = 1;
                i++;
            }
            returnObj.right = std::pair<int,int>(i,m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()+i]);
            break;
        case 1 :
            while((!(m_parcours->m_map[m_robot->m_position.y()-i][m_robot->m_position.x()]))||(m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()+i] == 2))
            {
                m_parcours->m_mapMask[m_robot->m_position.y()-i][m_robot->m_position.x()] = 1;
                i++;
            }
            returnObj.up = std::pair<int,int>(i,m_parcours->m_map[m_robot->m_position.y()-i][m_robot->m_position.x()]);
            break;
        case 2 :
            while(!(m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()-i]))
            {
                m_parcours->m_mapMask[m_robot->m_position.y()][m_robot->m_position.x()-i] = 1;
                i++;
            }
            returnObj.left = std::pair<int,int>(i,m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()-i]);
            break;
        case 3 :
            while(!(m_parcours->m_map[m_robot->m_position.y()+i][m_robot->m_position.x()]))
            {
                m_parcours->m_mapMask[m_robot->m_position.y()+i][m_robot->m_position.x()] = 1;
                i++;
            }
            returnObj.down = std::pair<int,int>(i,m_parcours->m_map[m_robot->m_position.y()+i][m_robot->m_position.x()]);
            break;
        default:
            break;
        }
    }
    return returnObj;

}

std::pair<QPoint,int> controller::getRobotPosition()
{
    std::pair<QPoint,int> returnObj(m_robot->m_position,m_parcours->m_map[m_robot->m_position.y()][m_robot->m_position.x()]);
    return returnObj;
}


void controller::toggleVisibility()
{
    m_parcours->m_reveal = !(m_parcours->m_reveal);
}
