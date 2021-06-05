#include "DateTimeXXX.h"
#include "ui_DateTimeXXX.h"

DateTimeXXX::DateTimeXXX(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTimeXXX)
{
    ui->setupUi(this);
    init();
}

DateTimeXXX::~DateTimeXXX()
{
    delete ui;
}

void DateTimeXXX::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    const int w = this->width();
    const int h = this->height();
    painter.setPen(QColor(0, 0, 0));
    painter.setBrush(QColor(0, 0, 0));
    painter.drawRect(QRect(0, 0, w, h));

    painter.setPen(QColor(130, 130, 130, 230));
    painter.translate(w >> 1, h >> 1);
    painter.scale(std::min(w, h)/700.0, std::min(w, h)/700.0);

    paintMonth(&painter);
    paintDay(&painter);
    paintHour(&painter);
    paintMinute(&painter);
    paintSecond(&painter);
}

void DateTimeXXX::init()
{
    m_month     = 0;
    m_day       = 0;
    m_hour      = 0;
    m_minute    = 0;
    m_second    = 0;

    m_penHighlight.setColor(QColor(118, 149, 150));
    m_penHighlight.setWidth(20);
    m_penNormal.setColor(QColor(220, 234, 246));
    m_penNormal.setWidth(1);

    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, [this]{
        QDate curDate = QDate::currentDate();
        QTime curTime = QTime::currentTime();

        m_month  = curDate.month();
        m_day    = curDate.day();
        m_hour   = curTime.hour();
        m_minute = curTime.minute();
        m_second = curTime.second();

        update();
    });
    m_timer.start();
}

QString DateTimeXXX::itoStr(int i)
{
    QString str = "";
    if (i < 10)
    {
        str.push_front(m_map0to10[i%10]);
    }
    else if (i < 100)
    {
        str.push_front(m_map0to10[i%10]);
        str.push_front(m_map0to10[i/10]);
    }
    else if (i < 1000)
    {
        str.push_front(m_map0to10[i%10]);
        str.push_front(m_map0to10[i/10]);
        str.push_front(m_map0to10[i/100]);
    }
    return str;
}

void DateTimeXXX::paintMonth(QPainter* painter)
{
    const QPointF topLeft(-80, -80);
    const QPointF bottomRight(80, 80);
    QRectF rectf(topLeft, bottomRight);

    for (int i = 0; i < 12; ++i)
    {
        painter->save();
        painter->rotate(i*30 - m_month*30);
        if (m_month == i) painter->setPen(m_penHighlight);
        else painter->setPen(m_penNormal);
        painter->drawText(rectf, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintDay(QPainter* painter)
{
    const QPointF topLeft(-120, -120);
    const QPointF bottomRight(120, 120);
    QRectF rectf(topLeft, bottomRight);

    for (int i = 0; i < 30; ++i)
    {
        painter->save();
        painter->rotate(i*12 - m_day*12);
        if (m_day == i) painter->setPen(m_penHighlight);
        else painter->setPen(m_penNormal);
        painter->drawText(rectf, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintHour(QPainter* painter)
{
    const QPointF topLeft(-160, -160);
    const QPointF bottomRight(160, 160);
    QRectF rectf(topLeft, bottomRight);

    for (int i = 0; i < 24; ++i)
    {
        painter->save();
        painter->rotate(i*15 - m_hour*15);
        if (m_hour == i) painter->setPen(m_penHighlight);
        else painter->setPen(m_penNormal);
        painter->drawText(rectf, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintMinute(QPainter* painter)
{
    const QPointF topLeft(-200, -200);
    const QPointF bottomRight(200, 200);
    QRectF rectf(topLeft, bottomRight);

    for (int i = 0; i < 60; ++i)
    {
        painter->save();
        painter->rotate(i*6 - m_minute*6);
        if (m_minute == i) painter->setPen(m_penHighlight);
        else painter->setPen(m_penNormal);
        painter->drawText(rectf, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintSecond(QPainter* painter)
{
    const QPointF topLeft(-240, -240);
    const QPointF bottomRight(240, 240);
    QRectF rectf(topLeft, bottomRight);

    for (int i = 0; i < 60; ++i)
    {
        painter->save();
        painter->rotate(i*6 - m_second*6);
        if (m_second == i) painter->setPen(m_penHighlight);
        else painter->setPen(m_penNormal);
        painter->drawText(rectf, itoStr(i));
        painter->restore();
    }
}
