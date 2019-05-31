#include "glwidget.h"
#include "helper.h"

#include <QPainter>
#include <QTimer>

GLWidget::GLWidget(Helper *_helper, QWidget *_parent)
    : QOpenGLWidget(_parent), helper(_helper)
{
    setMinimumSize(200,150);
    setMaximumSize(2000,2000);
    m_begin = std::chrono::high_resolution_clock::now();

    setAutoFillBackground(false);
}

void GLWidget::animate()
{
    m_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-m_begin).count();
    update();
}

void GLWidget::paintEvent(QPaintEvent *_event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    helper->precompute(m_elapsed);
    helper->paint(&painter, _event, m_elapsed);
    painter.end();
}
