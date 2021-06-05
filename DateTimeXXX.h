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
#include <QScreen>
//#include <QDebug>

#include "DateTimeXXXToolBox.h"
#include "MsgManager.h"
#include "datIO.h"

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
//    void keyPressEvent(QKeyEvent *event);

private:
    Ui::DateTimeXXX *ui;
    DateTimeXXXToolBox* m_pToolBox;

private:
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

        int xMonth;
        int xDay;
        int xHour;
        int xMinue;
        int xSecond;
    }DateTimeInfo;

    QTimer m_timer;
    DateTimeInfo m_dateTimeInfo;
    int m_spacing;

    QPen m_penNormal;
    QPen m_penHighlight;
    QPen m_penLabel;
    QFont m_fontNormal;
    QFont m_fontHighlight;

private:
    void init();
    void registerMsg();
    QString itoStr(int i);
    void getDateTimeInfo();

    void paintMonth(QPainter* painter);
    void paintDay(QPainter* painter);
    void paintHour(QPainter* painter);
    void paintMinute(QPainter* painter);
    void paintSecond(QPainter* painter);
    void paintLabel(QPainter* painter);

private slots:
    void slotChangeColor(QString topic, QString channel, int value);
    void slotChangeSpacing(int value);
    void slotExit();
};

#endif // DATETIMEXXX_H
