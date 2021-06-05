#include "ToolBox.h"
#include "ui_ToolBox.h"

ToolBox::ToolBox(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBox)
{
    ui->setupUi(this);

    init();
    createConnection();
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
    ui->horizontalSlider_timerInterval->setValue(1);

    ui->pushButton_play->setProperty("status", QVariant(false));
}

void ToolBox::createConnection()
{
    connect(ui->pushButton_play, &QPushButton::clicked, [this]{
        bool status = ui->pushButton_play->property("status").toBool();
        status = !status;
        ui->pushButton_play->setProperty("status", QVariant(status));
        if (status) { ui->pushButton_play->setText("stop"); }
        else { ui->pushButton_play->setText("start"); }
        emit sigPlay();
    });
}
