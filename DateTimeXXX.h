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
#include <QFont>
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
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DateTimeXXX *ui;

    QString m_map0to10[11] = {
        "零", "壹", "贰",
        "叁", "肆", "伍",
        "陆", "柒", "捌",
        "玖", "拾"
    };

    typedef struct {
        int month;
        int day;
        int daysInMonth;
        int hour;
        int minute;
        int second;
    }DateTimeInfo;

    QTimer m_timer;
    DateTimeInfo m_dateTimeInfo;

    QPen m_penNormal;
    QPen m_penHighlight;
    QFont m_fontNormal;
    QFont m_fontHighlight;

private:
    void init();
    QString itoStr(int i);
    void getDateTime();

    void paintMonth(QPainter* painter);
    void paintDay(QPainter* painter);
    void paintHour(QPainter* painter);
    void paintMinute(QPainter* painter);
    void paintSecond(QPainter* painter);
    void paintLabel(QPainter* painter);
};

#endif // DATETIMEXXX_H
