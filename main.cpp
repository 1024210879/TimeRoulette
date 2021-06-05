#include "DateTimeXXX.h"
#include <windows.h>
#include <QApplication>

bool enumUserWindowsCB(HWND hwnd, LPARAM lParam)
{
    long wflags = GetWindowLong(hwnd, GWL_STYLE);
    if (!(wflags & WS_VISIBLE)) {
        return TRUE;
    };

    HWND sndWnd;
    if (!(sndWnd=FindWindowEx(hwnd, NULL, L"SHELLDLL_DefView", NULL))) {
        return TRUE;
    }
    HWND targetWnd;
    if (!(targetWnd=FindWindowEx(sndWnd, NULL, L"SysListView32", L"FolderView"))) {
        return TRUE;
    }

    HWND* resultHwnd = (HWND*)lParam;
    *resultHwnd = targetWnd;
    return FALSE;
}

HWND findDesktopIconWnd()
{
    HWND resultHwnd = NULL;
    EnumWindows((WNDENUMPROC)enumUserWindowsCB, (LPARAM)&resultHwnd);
    return resultHwnd;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DateTimeXXX w;
    w.setAttribute(Qt::WA_TransparentForMouseEvents, true);
    w.setWindowFlag(Qt::FramelessWindowHint);
    w.setAttribute(Qt::WA_TranslucentBackground, true);


    HWND desktopHwnd = findDesktopIconWnd();
    // 设置桌面为父窗口
    if (desktopHwnd) {
        SetParent((HWND)w.winId(), desktopHwnd);
    }
    w.show();

    return a.exec();
}
