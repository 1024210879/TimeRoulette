#include "ToolBox.h"
#include "ui_ToolBox.h"

ToolBox::ToolBox(QWidget *parent) :
    MovableWidget(parent),
    ui(new Ui::ToolBox)
{
    ui->setupUi(this);

    init();
}

ToolBox::~ToolBox()
{
    delete ui;
}

void ToolBox::on_horizontalSlider_timerInterval_valueChanged(int value)
{
    ui->label_timerInterval->setText("speed: " + QString::number(1000.0/value, 'f', 2));
    emit sigValueChanged(value);
}

void ToolBox::init()
{
    ui->horizontalSlider_timerInterval->setMinimum(1);
    ui->horizontalSlider_timerInterval->setMaximum(33);
    ui->horizontalSlider_timerInterval->setValue(33);
}
