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
    std::string controllerConfig;
    std::vector<std::string> objConfig;
} config;

class Helper
{
public:
    Helper(int, char**);

    void precompute(long long elapsed);
    void paint(QPainter *painter, QPaintEvent *event, long long elapsed);
    config configuration(int,char**);
    void reinit();

    std::shared_ptr<controller> m_controller;
private:
    std::vector<std::shared_ptr<baseObj2Draw>> m_obj2Draw;
    QBrush background;

};

#endif
