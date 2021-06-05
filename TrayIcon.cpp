#include "TrayIcon.h"

TrayIcon::TrayIcon(QObject *parent) : QObject(parent)
{
    init();
}

void TrayIcon::init()
{
    tray = new QSystemTrayIcon(this);
    tray->setToolTip("时间轮盘");
    tray->setIcon(QIcon(QPixmap(":/images/1.png")));
    tray->show();

    acShow = new QAction("打开", this);
    connect(acShow, SIGNAL(triggered()), this, SIGNAL(sigShow()));
    acExit = new QAction("退出", this);
    connect(acExit, SIGNAL(triggered()), this, SIGNAL(sigExit()));

    menu = new QMenu;
    menu->addAction(acShow);
    menu->addAction(acExit);
    tray->setContextMenu(menu);
}
