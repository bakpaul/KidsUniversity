#include "robot.h"

robot::robot(std::string)
{

}

robot::~robot()
{

}

void robot::draw(QPainter *painter, QPaintEvent *event, long long elapsed)
{
    std::cout<<"Hey I am a robot and the time elapsed is : "<<elapsed<<std::endl<<std::endl;
}
