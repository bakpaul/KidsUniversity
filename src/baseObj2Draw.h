#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <memory>
#include <QPainter>

#define RATIO_FACTOR 1.58

typedef struct
{
    std::pair<int,int> up;
    std::pair<int,int> down;
    std::pair<int,int> left;
    std::pair<int,int> right;
} camStruct;

class baseObj2Draw
{
public:
    baseObj2Draw(){}
    virtual ~baseObj2Draw(){}
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed)=0;
};
