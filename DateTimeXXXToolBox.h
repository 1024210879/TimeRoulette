#ifndef DATETIMEXXXTOOLBOX_H
#define DATETIMEXXXTOOLBOX_H

#include <QWidget>
#include <QKeyEvent>

#include "TrayIcon.h"
#include "MovableWidget.h"
#include "MsgManager.h"
#include "datIO.h"

namespace Ui {
class DateTimeXXXToolBox;
}

class DateTimeXXXToolBox : public MovableWidget
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

    void on_horizontalSlider_spacing_valueChanged(int value);

    void on_pushButton_save_clicked();

    void on_pushButton_close_clicked();

private:
    Ui::DateTimeXXXToolBox *ui;
    TrayIcon* trayIcon;

private:
    void init();
    void registerMsg();

signals:
    void sigChangeColor(QString, QString, int);
    void sigChangeSpacing(int);
    void sigExit();
};

#endif // DATETIMEXXXTOOLBOX_H
