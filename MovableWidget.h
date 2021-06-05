#ifndef MOVABLEWIDGET_H
#define MOVABLEWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class MovableWidget : public QWidget
{
    Q_OBJECT


public:
    explicit MovableWidget(QWidget *parent = nullptr);

    void SetMovable(bool isMovable);


protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


private:
    bool    m_bLeftPressed;
    QPoint  m_pt;


private:
    void moveByDrag(QMouseEvent *event);

    bool m_bIsMovable;
};

#endif // MOVABLEWIDGET_H
