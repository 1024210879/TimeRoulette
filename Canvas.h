#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPainterPath>

#include <time.h>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::Canvas *ui;
    QTimer m_timer;
    unsigned int m_speed;

private:
    void init();
    int randInt(int low, int high);
    QColor randColor(int low, int high);

private slots:
    void slotSpeedChanged(int value);
    void slotPlay();
};

#endif // CANVAS_H
