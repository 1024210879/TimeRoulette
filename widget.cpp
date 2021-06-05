#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
    createConnection();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    static unsigned int counter = 0;
    counter = (counter+1)%360;

    const int w = this->width();
    const int h = this->height();

    QPainter painter(this);
    painter.setPen(QPen(QColor(200, 200, 200)));
    painter.setBrush(QBrush(QColor(200, 200, 200)));
    painter.drawRect(QRect(QPoint(0, 0), QPoint(w, h)));

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

    painter.save();
    for (int i = 0; i < 24; ++i)
    {
        painter.setBrush(QBrush(randColor(100, 156)));
        painter.rotate(15);
        painter.drawPath((counter-5)/15 == i ? pathFocus : pathNormal);
    }
    painter.restore();

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

int Widget::randInt(int low, int high)
{
    return rand() % high + low;
}

QColor Widget::randColor(int low, int high)
{
    return QColor(randInt(low, high), randInt(low, high), randInt(low, high), randInt(low, high));
}

void Widget::init()
{
    srand(time(0));
    m_timer.setInterval(33);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(slotTimeout()));
    m_timer.start();

    m_pToolBox = new ToolBox(this);
    m_pToolBox->move(10, 10);
    m_pToolBox->show();
}

void Widget::createConnection()
{
    connect(m_pToolBox, &ToolBox::sigValueChanged, [this](int value){
        m_timer.stop();
        m_timer.setInterval(value);
        m_timer.start();
    });
}

void Widget::slotTimeout()
{
        this->update();
}
