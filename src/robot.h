#pragma once

#include "baseObj2Draw.h"
#include <string>
#include <QPicture>
#include <QPixmap>

class robot : public baseObj2Draw
{
public:
    robot(std::string);
    virtual ~robot();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
};
