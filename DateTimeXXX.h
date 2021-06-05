#ifndef DATETIMEXXX_H
#define DATETIMEXXX_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainterPath>
#include <QTimer>
#include <QDate>
#include <QTime>
#include <QDebug>

namespace Ui {
class DateTimeXXX;
}

class DateTimeXXX : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeXXX(QWidget *parent = 0);
    ~DateTimeXXX();

protected:
    void paintEvent(QPaintEvent *event);

private:
    Ui::DateTimeXXX *ui;

    QString m_map0to10[11] = {
        "零", "壹", "贰",
        "叁", "肆", "伍",
        "陆", "柒", "捌",
        "玖", "拾"
    };

    int m_month;
    int m_day;
    int m_hour;
    int m_minute;
    int m_second;

    QTimer m_timer;

    QPen m_penNormal;
    QPen m_penHighlight;

private:
    void init();
    QString itoStr(int i);

    void paintMonth(QPainter* painter);
    void paintDay(QPainter* painter);
    void paintHour(QPainter* painter);
    void paintMinute(QPainter* painter);
    void paintSecond(QPainter* painter);
};

#endif // DATETIMEXXX_H
