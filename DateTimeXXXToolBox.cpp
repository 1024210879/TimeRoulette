#include "DateTimeXXXToolBox.h"
#include "ui_DateTimeXXXToolBox.h"

DateTimeXXXToolBox::DateTimeXXXToolBox(QWidget *parent) :
    MovableWidget(parent),
    ui(new Ui::DateTimeXXXToolBox)
{
    ui->setupUi(this);

    init();
    registerMsg();
}

DateTimeXXXToolBox::~DateTimeXXXToolBox()
{
    delete ui;
}

void DateTimeXXXToolBox::init()
{

}

void DateTimeXXXToolBox::registerMsg()
{
    MsgManager::instance()->registerSignal(
                QString("changeNormalColor"),
                this,
                SIGNAL(sigChangeColor(QString,QString,int)));

    MsgManager::instance()->registerSignal(
                QString("changeSpacing"),
                this,
                SIGNAL(sigChangeSpacing(int)));
}

void DateTimeXXXToolBox::on_pushButton_hide_clicked()
{
    this->setVisible(false);
}

void DateTimeXXXToolBox::on_horizontalSlider_normalR_valueChanged(int value)
{
    emit sigChangeColor(QString("normal"), QString("R"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_normalG_valueChanged(int value)
{
    emit sigChangeColor(QString("normal"), QString("G"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_normalB_valueChanged(int value)
{
    emit sigChangeColor(QString("normal"), QString("B"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_highlightR_valueChanged(int value)
{
    emit sigChangeColor(QString("highlight"), QString("R"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_highlightG_valueChanged(int value)
{
    emit sigChangeColor(QString("highlight"), QString("G"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_highlightB_valueChanged(int value)
{
    emit sigChangeColor(QString("highlight"), QString("B"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_labelR_valueChanged(int value)
{
    emit sigChangeColor(QString("label"), QString("R"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_labelG_valueChanged(int value)
{
    emit sigChangeColor(QString("label"), QString("G"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_labelB_valueChanged(int value)
{
    emit sigChangeColor(QString("label"), QString("B"), value);
}

void DateTimeXXXToolBox::on_horizontalSlider_spacing_valueChanged(int value)
{
    emit sigChangeSpacing(value);
}
