#include "MovableWidget.h"

MovableWidget::MovableWidget(QWidget *parent) :
    QWidget(parent),
    m_bIsMovable(true)
{
    this->setWindowFlag(Qt::FramelessWindowHint);
}

void MovableWidget::SetMovable(bool isMovable)
{
    m_bIsMovable = isMovable;
}

void MovableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        m_bLeftPressed = true;
        m_pt = event->pos();
    }
}

void MovableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_bLeftPressed == true)
    {
        this->moveByDrag(event);
    }
}

void MovableWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
        m_bLeftPressed = false;
        this->moveByDrag(event);
    }
}

void MovableWidget::moveByDrag(QMouseEvent *event)
{
    if (m_bIsMovable == false)
    {
        return;
    }

    QPoint ptCur;
    if (this->parent() == NULL)
    {
        ptCur = event->screenPos().toPoint() - m_pt;
    }
    else
    {
        ptCur = QWidget::mapToParent(event->pos()) - m_pt;
    }

    this->move(ptCur);
}
