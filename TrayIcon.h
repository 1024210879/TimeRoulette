#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>  //t托盘类
#include <QDesktopServices> //桌面事件类
#include <QAction>
#include <QMenu>

class TrayIcon : public QObject
{
    Q_OBJECT
public:
    explicit TrayIcon(QObject *parent = nullptr);

private:
    QMenu *menu;            //托盘菜单
    QSystemTrayIcon *tray;  //托盘图标添加成员
    QAction *acShow;        //托盘图标右键点击时弹出选项
    QAction *acExit;        //托盘图标右键点击时弹出选项

private:
    void init();

signals:
    void sigShow();
    void sigExit();
};

#endif // TRAYICON_H
