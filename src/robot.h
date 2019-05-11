#pragma once

#include "baseObj2Draw.h"
#include <string>
#include <QPicture>
#include <QImage>

class robot : public baseObj2Draw
{
public:
    robot(std::string);
    virtual ~robot();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);


    QPoint m_position;
    QImage m_image;
};
