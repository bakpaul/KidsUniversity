#include "robot.h"

robot::robot(std::string _filename)
{
    m_image.load(_filename.c_str());

}

robot::~robot()
{

}

void robot::draw(QPainter *_painter, QPaintEvent *_event, long long _elapsed)
{




}
