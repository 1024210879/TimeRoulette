#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    init();
    createConnection();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::init()
{
    m_pToolBox = ui->wgtToolBox;
    m_pCanvas = ui->wgtCanvas;

    m_pDateTimeXXX = new DateTimeXXX;
    m_pDateTimeXXX->show();
}

void Widget::createConnection()
{
    connect(m_pToolBox, SIGNAL(sigValueChanged(int)),
            m_pCanvas, SLOT(slotSpeedChanged(int)));

    connect(m_pToolBox, SIGNAL(sigPlay()),
            m_pCanvas, SLOT(slotPlay()));
}

