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
#include <QImage>

#define getInformationFromCamera construireCarteObstacle


class controller : public baseObj2Draw
{
public:
    controller(std::string,std::shared_ptr<robot>, std::shared_ptr<parcours>);
    virtual ~controller();
    virtual void draw(QPainter *painter, QPaintEvent *event, long long elapsed);
    void initRobotPosition();
    void addInstructions(int _instruc);
    void executeInstructions();
    void findNextInstructions();
    int getValueFromInstruction(int _instr);
    void setNewPositionFromInstruction(int _instr);
    void applyInformationsFromCamera(camStruct upDate);
    void initInstructions();
    void toggleVisibility();
    void incrWaitTime(){m_waitTime*=4.0/3.0;};
    void decrWaitTime(){m_waitTime*=3.0/4.0;};
    double getWaitTime(){return m_waitTime;};
    std::pair<QPoint,int> getRobotPosition();
    camStruct construireCarteObstacle();
    QString instrunction2char(int _i);

    virtual void reinit();

    private:
    std::shared_ptr<robot> m_robot;
    std::shared_ptr<parcours> m_parcours;
    int m_score;
    double m_waitTime;
    std::queue<int> m_instruction;
    QImage m_scoreIcon;
};
