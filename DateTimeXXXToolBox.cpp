#include "DateTimeXXXToolBox.h"
#include "ui_DateTimeXXXToolBox.h"

DateTimeXXXToolBox::DateTimeXXXToolBox(QWidget *parent) :
    MovableWidget(parent),
    ui(new Ui::DateTimeXXXToolBox)
{
    ui->setupUi(this);

    init();
}

DateTimeXXXToolBox::~DateTimeXXXToolBox()
{
    delete ui;
}

bool DateTimeXXXToolBox::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this->parent())
    {
        if (event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if (keyEvent->modifiers() == Qt::ControlModifier &&
                keyEvent->key() == Qt::Key_T)
            {
                this->move(10, 10);
                this->setVisible(true);
            }
        }
    }

    return MovableWidget::eventFilter(watched, event);
}

void DateTimeXXXToolBox::init()
{
    this->parent()->installEventFilter(this);
}
