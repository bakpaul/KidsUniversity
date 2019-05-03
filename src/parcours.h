#include "baseObj2Draw.h"

class parcours : public baseObj2Draw
{
    parcours();
    virtual ~parcours();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
};
