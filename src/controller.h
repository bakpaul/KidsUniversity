#pragma once

#include "baseObj2Draw.h"
#include "robot.h"
#include "parcours.h"
#include <string>
#include <memory>
#include <queue>
#include <QFont>
#include <QPen>
#include <QBrush>


class controller : public baseObj2Draw
{
public:
    controller(std::shared_ptr<robot>, std::shared_ptr<parcours>);
    virtual ~controller();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
    void addInstructions(int _instruc);
    void executeInstructions();
    void findNextInstructions();
    QString instrunction2char(int _i);

private:
    std::shared_ptr<robot> m_robot;
    std::shared_ptr<parcours> m_parcours;
    int m_score;
    std::queue<int> m_instruction;
};
