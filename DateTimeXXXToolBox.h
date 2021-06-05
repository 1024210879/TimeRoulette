#ifndef DATETIMEXXXTOOLBOX_H
#define DATETIMEXXXTOOLBOX_H

#include <QWidget>
#include <QKeyEvent>
#include "MovableWidget.h"
#include "MsgManager.h"

namespace Ui {
class DateTimeXXXToolBox;
}

class DateTimeXXXToolBox : public QWidget
{
    Q_OBJECT

public:
    explicit DateTimeXXXToolBox(QWidget *parent = 0);
    ~DateTimeXXXToolBox();

private slots:
    void on_pushButton_hide_clicked();

    void on_horizontalSlider_normalR_valueChanged(int value);

    void on_horizontalSlider_normalG_valueChanged(int value);

    void on_horizontalSlider_normalB_valueChanged(int value);

    void on_horizontalSlider_highlightR_valueChanged(int value);

    void on_horizontalSlider_highlightG_valueChanged(int value);

    void on_horizontalSlider_highlightB_valueChanged(int value);

    void on_horizontalSlider_labelR_valueChanged(int value);

    void on_horizontalSlider_labelG_valueChanged(int value);

    void on_horizontalSlider_labelB_valueChanged(int value);

private:
    Ui::DateTimeXXXToolBox *ui;

private:
    void init();
    void registerMsg();
    void createConnection();

signals:
    void sigChangeColor(QString, QString, int);
};

#endif // DATETIMEXXXTOOLBOX_H