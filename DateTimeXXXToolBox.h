#ifndef DATETIMEXXXTOOLBOX_H
#define DATETIMEXXXTOOLBOX_H

#include <QWidget>
#include <QKeyEvent>
#include "MovableWidget.h"

namespace Ui {
class DateTimeXXXToolBox;
}

class DateTimeXXXToolBox : public MovableWidget
{
    Q_OBJECT

public:
    explicit DateTimeXXXToolBox(QWidget *parent = 0);
    ~DateTimeXXXToolBox();

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::DateTimeXXXToolBox *ui;

private:
    void init();
};

#endif // DATETIMEXXXTOOLBOX_H
