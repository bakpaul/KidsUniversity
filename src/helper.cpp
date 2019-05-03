#include "helper.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <iostream>
#include <math.h>

Helper::Helper(double frequency,double completeTime)
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::black);
    gradient.setColorAt(1.0, Qt::black);

    background = QBrush(QColor(255,15,15));
    circleBrush = QBrush(gradient);
    circlePen = QPen(Qt::black);
    circlePen.setWidth(1);
    m_linePen = QPen(Qt::black);
    m_linePen.setWidth(7);
    textPen = QPen(Qt::black);
    textFont.setPixelSize(150);

    m_period = 1000000/frequency;
    m_elapsed = 0;
    m_state = false;
    m_length = completeTime*1000000;
}

void Helper::paint(QPainter *painter, QPaintEvent *event, long long _elapsed)
{
    static int acc = 0;
//    if(m_length>=_elapsed)
//    {
        if (((m_elapsed)%(m_period/2))>(_elapsed)%(m_period/2))
        {
            m_state = !m_state;
            acc++;
        }
        if(m_state)
        {
            background = QBrush(QColor(255,15,15));
        }
        else
        {
            background = QBrush(QColor(15,255,15));
        }
        m_elapsed = _elapsed%m_period;
        painter->fillRect(event->rect(), background);
        painter->translate(900, 500);

        painter->save();
        painter->setBrush(circleBrush);
        painter->setPen(circlePen);

        painter->translate(-200, -300);
        qreal r = 2*M_PI*m_elapsed / m_period;
        painter->rotate(50*std::sin(r+M_PI/2)+90);
        painter->drawEllipse(QRectF(400, -100, 200, 200));
        painter->setPen(m_linePen);
        painter->drawLine(QLineF(QPointF(0,0),QPointF(400,0)));

        painter->restore();
        painter->translate(300, 0);
        painter->setPen(m_linePen);

//        painter->drawRoundedRect(QRectF(320, -380, 90, 700),10,10);
//        painter->setBrush(circleBrush);
//        double perc = ((double) _elapsed)/m_length;
//        painter->drawRoundedRect(QRectF(320, -380+700*(perc), 90, 700*(1-perc)),10,10);

        painter->setPen(textPen);
        painter->setFont(textFont);
        char s_time[10];
        sprintf(s_time,"%d\0",acc) ;
        QString s_temp(s_time);
        painter->drawText(QRect(180, -75, 450, 200), Qt::AlignCenter, s_temp);
//        painter->restore();
//    }
//    else
//    {
//        painter->fillRect(event->rect(), QBrush(QColor(255,255,255)));
//        painter->translate(0, 0);
//        textFont.setPixelSize(500);
//        painter->setPen(textPen);
//        painter->setFont(textFont);
//        painter->drawText(QRect(0, 0, 1800, 1000), Qt::AlignCenter, "STOP");
//    }
}
