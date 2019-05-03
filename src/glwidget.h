#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <chrono>
#include <ctime>

class Helper;

class GLWidget : public QOpenGLWidget
{
    //Q_OBJECT

public:
    GLWidget(Helper *helper, QWidget *parent);

public slots:
    void animate();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Helper *helper;

    std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;

    long long m_elapsed;

};

#endif
