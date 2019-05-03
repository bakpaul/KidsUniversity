#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QSoundEffect>

class Helper
{
public:
    Helper(double frequency,double);

public:
    void paint(QPainter *painter, QPaintEvent *event, long long elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont textFont;
    QPen circlePen;
    QPen textPen;
    QPen m_linePen;
    QSoundEffect tic;
    QSoundEffect tac;
    long m_period;
    bool m_state;
    long m_elapsed;
    long long m_length;

};

#endif
