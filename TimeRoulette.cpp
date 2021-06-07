#include "TimeRoulette.h"
#include "ui_TimeRoulette.h"

TimeRoulette::TimeRoulette(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TimeRoulette)
{
    ui->setupUi(this);
    init();
    registerMsg();
}

TimeRoulette::~TimeRoulette()
{
    m_pToolBox->deleteLater();
    delete ui;
}

void TimeRoulette::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    getDateTimeInfo();

    const int w = this->width();
    const int h = this->height();

    painter.translate(w >> 1, h >> 1);
    painter.scale(std::min(w, h)/m_scale, std::min(w, h)/m_scale);

    paintMonth(&painter);
    paintDay(&painter);
    paintHour(&painter);
    paintMinute(&painter);
    paintSecond(&painter);

    paintCurDateTimeBackground(&painter);
    paintCurDateTime(&painter);
    paintLabel(&painter);

    paintPointerHour(&painter);
    paintPointerMinute(&painter);
    paintPointerSecond(&painter);
    paintCenterCircle(&painter);
}

void TimeRoulette::init()
{
    m_scale = 630;

    const int spacing = 50;
    m_dateTimeInfo.xMonth      = 70;
    m_dateTimeInfo.xDay        = 70+1*spacing;
    m_dateTimeInfo.xHour       = 70+2*spacing;
    m_dateTimeInfo.xMinue      = 70+3*spacing;
    m_dateTimeInfo.xSecond     = 70+4*spacing;

    QList<QScreen *> list_screen =  QGuiApplication::screens();
    QRect rect = list_screen.at(0)->geometry();
    const int sw = rect.width();
    const int sh = rect.height();
    this->setFixedSize(sw, sh);

    std::vector<uchar> v = datIO::readDat();
    if (!v.empty())
    {
        m_penHighlight.setColor(QColor(v[0], v[1], v[2]));
        m_penNormal.setColor(QColor(v[3], v[4], v[5]));
        m_penLabel.setColor(QColor(v[6], v[7], v[8]));
    }
    else
    {
        m_penHighlight.setColor(QColor(220, 234, 246));
        m_penNormal.setColor(QColor(118, 149, 150));
        m_penLabel.setColor(QColor(150, 10, 10));
    }
    m_penHighlight.setWidthF(0.5);
    m_penNormal.setWidthF(0.5);
    m_penLabel.setWidthF(0.5);

    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout, [this]{
        this->update();
    });
    m_timer.start();

    m_pToolBox = new TimeRouletteToolBox;
}

void TimeRoulette::registerMsg()
{
    MsgManager::instance()->registerSlot(
                QString("changeNormalColor"),
                this,
                SLOT(slotChangeColor(QString,QString,int)));

    MsgManager::instance()->registerSlot(
                QString("exit"),
                this,
                SLOT(slotExit()));
}

QString TimeRoulette::itoStr(int i)
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

void TimeRoulette::getDateTimeInfo()
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

void TimeRoulette::paintMonth(QPainter* painter)
{
    const double angle = 360.0/12.0;
    for (int i = 1; i <= 12; ++i)
    {
        painter->save();
        painter->rotate(i*angle - m_dateTimeInfo.month*angle);
        if (m_dateTimeInfo.month == i)
        {
            painter->restore();
            continue;
        }
        painter->setPen(m_penNormal);
        painter->rotate(-m_dateTimeInfo.day*1.0/m_dateTimeInfo.daysInMonth*angle);
        painter->drawText(m_dateTimeInfo.xMonth, 0, i != 12 ? itoStr(i) : QString("拾贰"));
        painter->restore();
    }
}

void TimeRoulette::paintDay(QPainter* painter)
{
    const double angle = 360.0/m_dateTimeInfo.daysInMonth;
    for (int i = 1; i <= m_dateTimeInfo.daysInMonth; ++i)
    {
        painter->save();
        painter->rotate(i*angle - m_dateTimeInfo.day*angle);
        if (m_dateTimeInfo.day == i)
        {
            painter->restore();
            continue;
        }
        painter->setPen(m_penNormal);
        painter->rotate(-m_dateTimeInfo.hour/24.0*angle);
        painter->drawText(m_dateTimeInfo.xDay, 0, itoStr(i));
        painter->restore();
    }
}

void TimeRoulette::paintHour(QPainter* painter)
{
    const double angle = 360.0/24.0;
    for (int i = 0; i < 24; ++i)
    {
        painter->save();
        painter->rotate(i*angle - m_dateTimeInfo.hour*angle);
        if (m_dateTimeInfo.hour == i)
        {
            painter->restore();
            continue;
        }
        painter->setPen(m_penNormal);
        painter->rotate(-m_dateTimeInfo.minute/60.0*angle);
        painter->drawText(m_dateTimeInfo.xHour, 0, itoStr(i));
        painter->restore();
    }
}

void TimeRoulette::paintMinute(QPainter* painter)
{
    const double angle = 360.0/60.0;
    for (int i = 0; i < 60; ++i)
    {
        painter->save();
        painter->rotate(i*angle - m_dateTimeInfo.minute*angle);
        if (m_dateTimeInfo.minute == i)
        {
            painter->restore();
            continue;
        }
        painter->setPen(m_penNormal);
        painter->rotate(-m_dateTimeInfo.second/60.0*angle);
        painter->drawText(m_dateTimeInfo.xMinue, 0, itoStr(i));
        painter->restore();
    }
}

void TimeRoulette::paintSecond(QPainter* painter)
{
    for (int i = 0; i < 60; ++i)
    {
        painter->save();
        painter->rotate(i*6 - m_dateTimeInfo.second*6);
        if (m_dateTimeInfo.second == i)
        {
            painter->restore();
            continue;
        }
        painter->setPen(m_penNormal);
        painter->drawText(m_dateTimeInfo.xSecond, 0, itoStr(i));
        painter->restore();
    }
}

void TimeRoulette::paintCurDateTimeBackground(QPainter *painter)
{
    painter->save();

    QPen pen(QColor(30, 30, 30));
    QBrush brush(QColor(128, 128, 128, 230));
    painter->setPen(pen);
    painter->setBrush(brush);

    painter->drawRoundedRect(m_dateTimeInfo.xMonth  - 5, -15, 45, 20, 5, 5);
    painter->drawRoundedRect(m_dateTimeInfo.xDay    - 5, -15, 45, 20, 5, 5);
    painter->drawRoundedRect(m_dateTimeInfo.xHour   - 5, -15, 45, 20, 5, 5);
    painter->drawRoundedRect(m_dateTimeInfo.xMinue  - 5, -15, 45, 20, 5, 5);
    painter->drawRoundedRect(m_dateTimeInfo.xSecond - 5, -15, 45, 20, 5, 5);

    painter->restore();
}

void TimeRoulette::paintCurDateTime(QPainter *painter)
{
    // month
    painter->setPen(m_penHighlight);
    painter->drawText(m_dateTimeInfo.xMonth, 0, m_dateTimeInfo.month != 12 ? itoStr(m_dateTimeInfo.month) : QString("拾贰"));

    // day
    painter->setPen(m_penHighlight);
    painter->drawText(m_dateTimeInfo.xDay, 0, itoStr(m_dateTimeInfo.day));

    // hour
    painter->setPen(m_penHighlight);
    painter->drawText(m_dateTimeInfo.xHour, 0, itoStr(m_dateTimeInfo.hour));

    // minute
    painter->setPen(m_penHighlight);
    painter->drawText(m_dateTimeInfo.xMinue, 0, itoStr(m_dateTimeInfo.minute));

    // second
    painter->setPen(m_penHighlight);
    painter->drawText(m_dateTimeInfo.xSecond, 0, itoStr(m_dateTimeInfo.second));
}

void TimeRoulette::paintLabel(QPainter *painter)
{
    painter->setPen(m_penLabel);
    painter->drawText(m_dateTimeInfo.xMonth  + 25, 0, QString("月"));
    painter->drawText(m_dateTimeInfo.xDay    + 25, 0, QString("日"));
    painter->drawText(m_dateTimeInfo.xHour   + 25, 0, QString("时"));
    painter->drawText(m_dateTimeInfo.xMinue  + 25, 0, QString("分"));
    painter->drawText(m_dateTimeInfo.xSecond + 25, 0, QString("秒"));
}

void TimeRoulette::paintPointerHour(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(-15, 0);
    path.lineTo(0, 10);
    path.lineTo(15, 0);
    path.lineTo(0, -m_dateTimeInfo.xHour);
    path.closeSubpath();

    painter->save();
    painter->rotate((m_dateTimeInfo.hour%12)*30 + m_dateTimeInfo.minute/60.0*30);
    painter->setPen(QPen(QColor(200, 200, 200, 150)));
    painter->setBrush(QColor(200, 200, 200, 128));
    painter->drawPath(path);
    painter->restore();
}

void TimeRoulette::paintPointerMinute(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(-10, 0);
    path.lineTo(0, 20);
    path.lineTo(10, 0);
    path.lineTo(0, -m_dateTimeInfo.xMinue);
    path.closeSubpath();

    painter->save();
    painter->rotate(m_dateTimeInfo.minute*6 + m_dateTimeInfo.second/60.0*6);
    painter->setPen(QPen(QColor(200, 200, 200, 150)));
    painter->setBrush(QColor(200, 200, 200, 128));
    painter->drawPath(path);
    painter->restore();
}

void TimeRoulette::paintPointerSecond(QPainter *painter)
{
    QPainterPath path;
    path.moveTo(-7, 0);
    path.lineTo(0, 30);
    path.lineTo(7, 0);
    path.lineTo(0, -m_dateTimeInfo.xSecond);
    path.closeSubpath();

    painter->save();
    painter->rotate(m_dateTimeInfo.second*6);
    painter->setPen(QPen(QColor(200, 200, 200, 150)));
    painter->setBrush(QColor(200, 200, 200, 128));
    painter->drawPath(path);
    painter->restore();
}

void TimeRoulette::paintCenterCircle(QPainter *painter)
{
    QPainterPath path;
    path.addEllipse(QPointF(0, 0), 3, 3);

    painter->save();
    painter->setPen(QPen(QColor(30, 30, 30, 10)));
    painter->setBrush(QBrush(QColor(128, 128, 128, 30)));
    painter->drawPath(path);
    painter->restore();
}

void TimeRoulette::slotChangeColor(QString topic, QString channel, int value)
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

    this->repaint();
}

void TimeRoulette::slotExit()
{
    this->close();
}
