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
    std::vector<uchar> v = datIO::readDat();
    if (v.empty())
    {
        return;
    }

    ui->horizontalSlider_highlightR->setValue(v[0]);
    ui->horizontalSlider_highlightG->setValue(v[1]);
    ui->horizontalSlider_highlightB->setValue(v[2]);
    ui->horizontalSlider_normalR->setValue(v[3]);
    ui->horizontalSlider_normalG->setValue(v[4]);
    ui->horizontalSlider_normalB->setValue(v[5]);
    ui->horizontalSlider_labelR->setValue(v[6]);
    ui->horizontalSlider_labelG->setValue(v[7]);
    ui->horizontalSlider_labelB->setValue(v[8]);

    trayIcon = new TrayIcon(this);
    connect(trayIcon, &TrayIcon::sigShow, [this]{ this->show(); });
    connect(trayIcon, &TrayIcon::sigExit, [this]{ this->on_pushButton_close_clicked(); });
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

    MsgManager::instance()->registerSignal(
                QString("exit"),
                this,
                SIGNAL(sigExit()));
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

void DateTimeXXXToolBox::on_pushButton_save_clicked()
{
    std::vector<uchar> v;
    v.resize(9);
    v[0] = ui->horizontalSlider_highlightR->value();
    v[1] = ui->horizontalSlider_highlightG->value();
    v[2] = ui->horizontalSlider_highlightB->value();
    v[3] = ui->horizontalSlider_normalR->value();
    v[4] = ui->horizontalSlider_normalG->value();
    v[5] = ui->horizontalSlider_normalB->value();
    v[6] = ui->horizontalSlider_labelR->value();
    v[7] = ui->horizontalSlider_labelG->value();
    v[8] = ui->horizontalSlider_labelB->value();
    datIO::writeDat(v);
}

void DateTimeXXXToolBox::on_pushButton_close_clicked()
{
    emit sigExit();
    this->close();
}
