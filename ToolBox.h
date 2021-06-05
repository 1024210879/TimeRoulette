#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QWidget>

#include "MovableWidget.h"

namespace Ui {
class ToolBox;
}

class ToolBox : public MovableWidget
{
    Q_OBJECT

public:
    explicit ToolBox(QWidget *parent = 0);
    ~ToolBox();

private slots:
    void on_horizontalSlider_timerInterval_valueChanged(int value);

private:
    Ui::ToolBox *ui;

private:
    void init();

signals:
    void sigValueChanged(int);
};

#endif // TOOLBOX_H