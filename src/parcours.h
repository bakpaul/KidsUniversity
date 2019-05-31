#pragma once

#include "baseObj2Draw.h"
#include <string>
#include <fstream>
#include <QPainter>
#include <QPaintEvent>

typedef std::vector<std::vector<int>> parcoursMap;

class parcours : public baseObj2Draw
{
public:
    parcours(std::string);
    virtual ~parcours();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
    virtual void reinit();
    void configuration(std::string);

    parcoursMap m_map;
    parcoursMap m_mapMask;
    std::vector<QBrush> m_brush;
    std::vector<QPen> m_pen;
    QFont m_font;
    QPointF m_offsetFromCenter;
    QPointF m_origin;
    double m_scale;
    int m_carreSize;
    int m_height;
    int m_width;
};
