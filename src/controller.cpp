#include "controller.h"


controller::controller(std::shared_ptr<robot> _robot, std::shared_ptr<parcours> _parcours) : m_robot(_robot), m_parcours(_parcours)
{
    m_score = 0;
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
//    std::cout<<"Hi ! "<<std::endl;
    QFont font;
    QPen pen(Qt::black);
    pen.setWidth(5);
    QBrush brush(Qt::transparent);

    _painter->translate(_event->rect().width()/2.0+m_parcours->m_carreSize*(m_parcours->m_width/2.0 + m_parcours->m_offsetFromCenter.x()+1), _event->rect().height()/2.0-m_parcours->m_carreSize*m_parcours->m_offsetFromCenter.y());
    font.setPixelSize((m_parcours->m_carreSize*m_parcours->m_height)/6.0);
    _painter->setFont(font);
    _painter->save();
    _painter->setPen(pen);
    _painter->setBrush(brush);
    _painter->translate(0,-(m_parcours->m_carreSize*m_parcours->m_height)/2);
    _painter->drawRect(0,0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0,(m_parcours->m_carreSize*m_parcours->m_height)/6.0);
    _painter->drawText(QRect(0,0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0,(m_parcours->m_carreSize*m_parcours->m_height)/6.0), Qt::AlignCenter, std::to_string(m_score).c_str());

    font.setPixelSize((m_parcours->m_carreSize*m_parcours->m_height)/3.0);
    _painter->setFont(font);
    _painter->translate(0,(m_parcours->m_carreSize*m_parcours->m_height)*1.5/6.0);
    _painter->drawRect(0,0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0);
    if(m_instruction.size()==2)
        _painter->drawText(QRect(0,0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0), Qt::AlignCenter, instrunction2char(m_instruction.front()));

    _painter->translate(0,(m_parcours->m_carreSize*m_parcours->m_height)*2.5/6.0);
    _painter->drawRect(0,0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0);
    if(m_instruction.size()>0)
        _painter->drawText(QRect(0,0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0,(m_parcours->m_carreSize*m_parcours->m_height)/3.0), Qt::AlignCenter,  instrunction2char(m_instruction.back()));


    _painter->restore();

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

void controller::executeInstructions()
{
    if(m_instruction.size())
        m_score ++;
    while(m_instruction.size() >0)
        m_instruction.pop();
}
