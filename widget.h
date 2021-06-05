#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPainterPath>

#include <time.h>

#include "ToolBox.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Widget *ui;
    QTimer m_timer;
    ToolBox* m_pToolBox;

private:
    int randInt(int low, int high);
    QColor randColor(int low, int high);
    void init();
    void createConnection();

private slots:
    void slotTimeout();
};

#endif // WIDGET_H
