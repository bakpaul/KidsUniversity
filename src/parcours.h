#pragma once

#include "baseObj2Draw.h"
#include <string>

class parcours : public baseObj2Draw
{
public:
    parcours(std::string);
    virtual ~parcours();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
};
