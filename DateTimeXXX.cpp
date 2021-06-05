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
    painter.scale(std::min(w, h)/600.0, std::min(w, h)/600.0);

    paintMonth(&painter);
    paintDay(&painter);
    paintHour(&painter);
    paintMinute(&painter);
    paintSecond(&painter);
}

void DateTimeXXX::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }
}

void DateTimeXXX::init()
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->showFullScreen();

    getDateTime();

    m_penHighlight.setColor(QColor(220, 234, 246));
    m_penNormal.setColor(QColor(118, 149, 150));
    m_fontNormal.setBold(false);
    m_fontNormal.setWeight(1);
    m_fontHighlight.setBold(true);
    m_fontHighlight.setWeight(2);

    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, [this]{
        getDateTime();
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
    return str;
}

void DateTimeXXX::getDateTime()
{
    QDate curDate = QDate::currentDate();
    QTime curTime = QTime::currentTime();

    m_dateTimeInfo.month       = curDate.month();
    m_dateTimeInfo.day         = curDate.day();
    m_dateTimeInfo.daysInMonth = curDate.daysInMonth();
    m_dateTimeInfo.hour        = curTime.hour();
    m_dateTimeInfo.minute      = curTime.minute();
    m_dateTimeInfo.second      = curTime.second();
}

void DateTimeXXX::paintMonth(QPainter* painter)
{
    for (int i = 1; i <= 12; ++i)
    {
        painter->save();
        painter->rotate(i*30 - m_dateTimeInfo.month*30);
        if (m_dateTimeInfo.month == i)
        {
            painter->setPen(m_penHighlight);
            painter->setFont(m_fontNormal);
        }
        else painter->setPen(m_penNormal);
        painter->drawText(80, 0, i != 12 ? itoStr(i) : QString("拾贰"));
        painter->restore();
    }
}

void DateTimeXXX::paintDay(QPainter* painter)
{
    const double angle = 360.0/m_dateTimeInfo.daysInMonth;
    for (int i = 1; i <= m_dateTimeInfo.daysInMonth; ++i)
    {
        painter->save();
        painter->rotate(i*angle - m_dateTimeInfo.day*angle);
        if (m_dateTimeInfo.day == i)
        {
            painter->setPen(m_penHighlight);
            painter->setFont(m_fontNormal);
        }
        else painter->setPen(m_penNormal);
        painter->drawText(120, 0, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintHour(QPainter* painter)
{
    for (int i = 0; i < 24; ++i)
    {
        painter->save();
        painter->rotate(i*15 - m_dateTimeInfo.hour*15);
        if (m_dateTimeInfo.hour == i)
        {
            painter->setPen(m_penHighlight);
            painter->setFont(m_fontNormal);
        }
        else painter->setPen(m_penNormal);
        painter->drawText(160, 0, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintMinute(QPainter* painter)
{
    for (int i = 0; i < 60; ++i)
    {
        painter->save();
        painter->rotate(i*6 - m_dateTimeInfo.minute*6);
        if (m_dateTimeInfo.minute == i)
        {
            painter->setPen(m_penHighlight);
            painter->setFont(m_fontNormal);
        }
        else painter->setPen(m_penNormal);
        painter->drawText(200, 0, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintSecond(QPainter* painter)
{
    for (int i = 0; i < 60; ++i)
    {
        painter->save();
        painter->rotate(i*6 - m_dateTimeInfo.second*6);
        if (m_dateTimeInfo.second == i)
        {
            painter->setPen(m_penHighlight);
            painter->setFont(m_fontNormal);
        }
        else painter->setPen(m_penNormal);
        painter->drawText(240, 0, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintLabel(QPainter *painter)
{

}
