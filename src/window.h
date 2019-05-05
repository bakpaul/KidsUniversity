
#ifndef WINDOW_H
#define WINDOW_H

#include "helper.h"

#include <QWidget>

class Window : public QWidget
{
   // Q_OBJECT

public:
    Window(int, char**);

    void keyPressEvent(QKeyEvent *_event) override;

private:
    Helper helper;
};

#endif
