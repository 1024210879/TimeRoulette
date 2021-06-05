#include "DateTimeXXX.h"
#include "ui_DateTimeXXX.h"

DateTimeXXX::DateTimeXXX(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DateTimeXXX)
{
    ui->setupUi(this);
    init();
    registerMsg();
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
    paintLabel(&painter);
}

void DateTimeXXX::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        this->close();
    }
    else if (event->key() == Qt::Key_T && event->modifiers() == Qt::ControlModifier)
    {
        m_pToolBox->move(10, 10);
        m_pToolBox->show();
    }
}

void DateTimeXXX::init()
{
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->showFullScreen();

    getDateTimeInfo();

    m_penHighlight.setColor(QColor(220, 234, 246));
    m_penNormal.setColor(QColor(118, 149, 150));
    m_penLabel.setColor(QColor(150, 10, 10));
    m_fontNormal.setBold(false);
    m_fontNormal.setWeight(1);
    m_fontHighlight.setBold(true);
    m_fontHighlight.setWeight(2);

    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, [this]{
        getDateTimeInfo();
        this->repaint();
    });
    m_timer.start();

    m_pToolBox = new DateTimeXXXToolBox(this);
}

void DateTimeXXX::registerMsg()
{
    MsgManager::instance()->registerSlot(
                QString("changeNormalColor"),
                this,
                SLOT(slotChangeColor(QString,QString,int)));

    MsgManager::instance()->registerSlot(
                QString("changeSpacing"),
                this,
                SLOT(slotChangeSpacing(int)));
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

void DateTimeXXX::getDateTimeInfo()
{
    QDate curDate = QDate::currentDate();
    QTime curTime = QTime::currentTime();

    m_dateTimeInfo.month       = curDate.month();
    m_dateTimeInfo.day         = curDate.day();
    m_dateTimeInfo.daysInMonth = curDate.daysInMonth();
    m_dateTimeInfo.hour        = curTime.hour();
    m_dateTimeInfo.minute      = curTime.minute();
    m_dateTimeInfo.second      = curTime.second();

    m_spacing = 50;
    m_dateTimeInfo.xMonth      = 70;
    m_dateTimeInfo.xDay        = 70+1*m_spacing;
    m_dateTimeInfo.xHour       = 70+2*m_spacing;
    m_dateTimeInfo.xMinue      = 70+3*m_spacing;
    m_dateTimeInfo.xSecond     = 70+4*m_spacing;
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
        painter->drawText(m_dateTimeInfo.xMonth, 0, i != 12 ? itoStr(i) : QString("拾贰"));
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
        painter->drawText(m_dateTimeInfo.xDay, 0, itoStr(i));
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
        painter->drawText(m_dateTimeInfo.xHour, 0, itoStr(i));
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
        painter->drawText(m_dateTimeInfo.xMinue, 0, itoStr(i));
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
        painter->drawText(m_dateTimeInfo.xSecond, 0, itoStr(i));
        painter->restore();
    }
}

void DateTimeXXX::paintLabel(QPainter *painter)
{
    painter->setPen(m_penLabel);
    painter->drawText(m_dateTimeInfo.xMonth  + 25, 0, QString("月"));
    painter->drawText(m_dateTimeInfo.xDay    + 25, 0, QString("日"));
    painter->drawText(m_dateTimeInfo.xHour   + 25, 0, QString("时"));
    painter->drawText(m_dateTimeInfo.xMinue  + 25, 0, QString("分"));
    painter->drawText(m_dateTimeInfo.xSecond + 25, 0, QString("秒"));
}

void DateTimeXXX::slotChangeColor(QString topic, QString channel, int value)
{
    QColor color;
    if (topic == "normal")
    {
        color = m_penNormal.color();
        if (channel == "R"){
            color.setRed(value);
        }else if (channel == "G"){
            color.setGreen(value);
        }else if (channel == "B"){
            color.setBlue(value);
        }
        m_penNormal.setColor(color);
    }
    else if (topic == "highlight")
    {
        color = m_penHighlight.color();
        if (channel == "R"){
            color.setRed(value);
        }else if (channel == "G"){
            color.setGreen(value);
        }else if (channel == "B"){
            color.setBlue(value);
        }
        m_penHighlight.setColor(color);
    }
    else if (topic == "label")
    {
        color = m_penLabel.color();
        if (channel == "R"){
            color.setRed(value);
        }else if (channel == "G"){
            color.setGreen(value);
        }else if (channel == "B"){
            color.setBlue(value);
        }
        m_penLabel.setColor(color);
    }
}

void DateTimeXXX::slotChangeSpacing(int value)
{
    m_spacing = value;
}
