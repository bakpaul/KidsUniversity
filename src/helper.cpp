#include "helper.h"
#include "stringException.h"
#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <iostream>
#include <math.h>

std::ostream& operator<<(std::ostream& _out,config& _config)
{
    _out<<"Periode : "<<_config.period<<std::endl;
    _out<<"Robot configuration file : "<<_config.robotConfig<<std::endl;
    _out<<"Parcours configuration file : "<<_config.parcoursConfig<<std::endl;
    if(_config.objConfig.size())
    {
        for(unsigned i = 0;i<_config.objConfig.size();i++)
        {
            _out<<i+1<<"th "<<"Obj configuration file : "<<_config.objConfig[i]<<std::endl;
        }
    }
    return _out;
}

Helper::Helper(int _a, char**_b )
{
    background = QBrush(QColor(255,255,255));
    config conf = configuration(_a,_b);
    std::cout<<conf;
    std::shared_ptr<baseObj2Draw> tempParcours(new parcours(conf.parcoursConfig));
    std::shared_ptr<baseObj2Draw> tempRobot(new robot(conf.robotConfig));
    m_obj2Draw.push_back(tempParcours);
    m_obj2Draw.push_back(tempRobot);

//    std::ofstream file;
//    file.open(_b[0]);

//    circleBrush = QBrush(gradient);
//    circlePen = QPen(Qt::black);
//    circlePen.setWidth(1);
//    m_linePen = QPen(Qt::black);
//    m_linePen.setWidth(7);
//    textPen = QPen(Qt::white);
//    textFont.setPixelSize(150);

//    m_period = 1000000/frequency;
//    m_elapsed = 0;
//    m_state = false;
//    m_length = completeTime*1000000;
}

config Helper::configuration(int _a,char** _b)
{
    config returnObj;
    if(_a>1)
    {
        std::ifstream file;
        std::string fileName(_b[1]);
        file.open(fileName);
        if(file.is_open())
        {
            file >> returnObj.period;
            std::string tempStr;
            while(file>>tempStr)
            {
                if(tempStr=="robot")
                    file>>returnObj.robotConfig;
                else if(tempStr=="parcours")
                    file>>returnObj.parcoursConfig;
                else
                {
                    file>>tempStr;
                    returnObj.objConfig.push_back(tempStr);
                }
            }
        }
        else
        {
            throw(stringException("Helper : Unable to open configuration file"));
        }
    }
    else
    {
        throw(stringException("Helper : No configuration file name was given"));
    }
    return returnObj;
}

void Helper::nextStep(parcours _parcours,robot _robot)
{

}

void Helper::paint(QPainter *_painter, QPaintEvent *_event, long long _elapsed)
{
    _painter->fillRect(_event->rect(), background);

    for(unsigned i=0; i< m_obj2Draw.size(); i++)
    {
        //m_obj2Draw[i]->draw(_painter, _event, _elapsed);
    }



//    static int acc = 0;
////    if(m_length>=_elapsed)
////    {
//        if (((m_elapsed)%(m_period/2))>(_elapsed)%(m_period/2))
//        {
//            m_state = !m_state;
//            acc++;
//        }
//        if(m_state)
//        {
//            background = QBrush(QColor(255,15,15));
//        }
//        else
//            background = QBrush(QColor(15,255,15));
    //        {
//        }
//        m_elapsed = _elapsed%m_period;
//        _painter->fillRect(_event->rect(), background);
//        _painter->translate(900, 500);

//        _painter->save();
//        _painter->setBrush(circleBrush);
//        _painter->setPen(circlePen);

//        _painter->translate(-200, -300);
//        qreal r = 2*M_PI*m_elapsed / m_period;
//        _painter->rotate(50*std::sin(r+M_PI/2)+90);
//        _painter->drawEllipse(QRectF(400, -100, 200, 200));
//        _painter->setPen(m_linePen);
//        _painter->drawLine(QLineF(QPointF(0,0),QPointF(400,0)));

//        _painter->restore();
//        _painter->translate(300, 0);
//        _painter->setPen(m_linePen);

////        painter->drawRoundedRect(QRectF(320, -380, 90, 700),10,10);
////        painter->setBrush(circleBrush);
////        double perc = ((double) _elapsed)/m_length;
////        painter->drawRoundedRect(QRectF(320, -380+700*(perc), 90, 700*(1-perc)),10,10);
//        _painter->fillRect(_event->rect(), background);
//        background = QBrush(QColor(105,115,110));
//        _painter->setPen(textPen);
//        _painter->setFont(textFont);
//        std::cout<<_event->rect().height()<<std::endl;

//        QString s_temp("s_time");
//        _painter->drawText(QRect(0, 0, 450, 200), Qt::AlignCenter, s_temp);

//    }
//    else
//    {
//        painter->fillRect(event->rect(), QBrush(QColor(255,255,255)));
//        painter->translate(0, 0);
//        textFont.setPixelSize(500);
//        painter->setPen(textPen);
//        painter->setFont(textFont);
//        painter->drawText(QRect(0, 0, 1800, 1000), Qt::AlignCenter, "STOP");
//    }
}
