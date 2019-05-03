#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>

class baseObj2Draw
{
public:
    baseObj2Draw(){}
    virtual ~baseObj2Draw(){}
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed)=0;
};
