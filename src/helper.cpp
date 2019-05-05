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
    std::shared_ptr<controller> tempCont(new controller(std::shared_ptr<robot>(static_cast<robot*>(tempRobot.get())),std::shared_ptr<parcours>(static_cast<parcours*>(tempParcours.get()))));
    m_controller = tempCont;
    std::shared_ptr<baseObj2Draw> tempCont2(tempCont.get());
    m_obj2Draw.push_back(tempParcours);
    m_obj2Draw.push_back(tempRobot);
    m_obj2Draw.push_back(tempCont2);

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

            std::string tempStr;
            while(file>>tempStr)
            {
                if(tempStr=="robot")
                    file>>returnObj.robotConfig;
                else if(tempStr=="parcours")
                    file>>returnObj.parcoursConfig;
                else if(tempStr=="period")
                    file >> returnObj.period;
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


void Helper::paint(QPainter *_painter, QPaintEvent *_event, long long _elapsed)
{
    _painter->fillRect(_event->rect(), background);

    for(unsigned i=0; i< m_obj2Draw.size(); i++)
    {
        m_obj2Draw[i]->draw(_painter, _event, _elapsed);
    }

}
