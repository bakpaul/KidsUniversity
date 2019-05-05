#ifndef HELPER_H
#define HELPER_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QWidget>
#include <QSoundEffect>
#include <fstream>
#include <memory>
#include "baseObj2Draw.h"
#include <string>
#include "parcours.h"
#include "robot.h"
#include "controller.h"

typedef struct config
{
    std::string robotConfig;
    std::string parcoursConfig;
    std::vector<std::string> objConfig;
    double period;
} config;

class Helper
{
public:
    Helper(int, char**);

    void paint(QPainter *painter, QPaintEvent *event, long long elapsed);
    config configuration(int,char**);

    std::shared_ptr<controller> m_controller;
private:
    std::vector<std::shared_ptr<baseObj2Draw>> m_obj2Draw;
    QBrush background;

};

#endif
