#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "ToolBox.h"
#include "Canvas.h"
#include "DateTimeXXX.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    ToolBox* m_pToolBox;
    Canvas* m_pCanvas;
    DateTimeXXX* m_pDateTimeXXX;

private:
    void init();
    void createConnection();
};

#endif // WIDGET_H
