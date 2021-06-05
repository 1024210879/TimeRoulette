#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>

namespace Ui {
class Canvas;
}

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

private:
    Ui::Canvas *ui;
};

#endif // CANVAS_H
