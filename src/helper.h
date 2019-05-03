#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QSoundEffect>
#include "baseObj2Draw.h"

class Helper
{
public:
    Helper(int, char**);

public:
    void paint(QPainter *painter, QPaintEvent *event, long long elapsed);

private:
    std::vector<baseObj2Draw*> m_obj2Draw;
    QBrush background;
};

#endif
