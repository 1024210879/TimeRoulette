#include "Canvas.h"
#include "ui_Canvas.h"

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    init();
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::paintEvent(QPaintEvent *event)
{
    static int counter = -1;
    counter = (counter+m_speed)%360;

    const int w = this->width();
    const int h = this->height();

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(w>>1, h>>1);
    painter.scale(std::min(w, h)/245.0, std::min(w, h)/245.0);

    QPen pen;
    pen.setWidth(0.5);
    painter.setPen(pen);

    QPainterPath pathNormal;
    pathNormal.moveTo(0, 80);
    pathNormal.lineTo(-10, 110);
    pathNormal.lineTo(10, 110);
    pathNormal.closeSubpath();

    QPainterPath pathFocus;
    pathFocus.moveTo(0, 90);
    pathFocus.lineTo(-10, 120);
    pathFocus.lineTo(10, 120);
    pathFocus.closeSubpath();

    for (int i = 0; i < 24; ++i)
    {
        painter.save();
        painter.setBrush(QBrush(randColor(100, 156)));
        painter.rotate(15*i);
        painter.drawPath((counter+7)/15 == i ? pathFocus : pathNormal);
        painter.restore();
    }

    for (int i = 0; i < 6; ++i)
    {
        painter.setBrush(QBrush(/*!(i%2) ? */randColor(50, 120)/* : QColor(200,200,200,200-i*20)*/));
        QPainterPath bigCircle, smallCircle;
        bigCircle.addEllipse(QPointF(0, 0), 15*i, 15*i);
        smallCircle.addEllipse(QPointF(0, 0), 15*(i-1), 15*(i-1));
        painter.drawPath(bigCircle-smallCircle);
    }

    QPainterPath pLine;
    pLine.moveTo(-5, 0);
    pLine.lineTo(0, -5);
    pLine.lineTo(5, 0);
    pLine.lineTo(0, 100);
    pLine.closeSubpath();

    painter.save();
    painter.rotate(counter);
    painter.setBrush(QBrush(QColor(200, 200, 200, 200)));
    painter.drawPath(pLine);
    painter.restore();
}

void Canvas::init()
{
    srand(time(0));
    m_speed = 1;
    m_timer.setInterval(1);
    connect(&m_timer, &QTimer::timeout, [this]{update();});
}

int Canvas::randInt(int low, int high)
{
    return rand() % high + low;
}

QColor Canvas::randColor(int low, int high)
{
    return QColor(randInt(low, high), randInt(low, high), randInt(low, high), randInt(low, high));
}

void Canvas::slotSpeedChanged(int value)
{
    m_speed = value;
}

void Canvas::slotPlay()
{
    static bool status = false;
    status = !status;
    if (status){ m_timer.start(); }
    else { m_timer.stop(); }
}
