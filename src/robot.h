#include "baseObj2Draw.h"

class robot : public baseObj2Draw
{
    robot();
    virtual ~robot();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
};
