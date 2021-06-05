#include "widget.h"
#include "DateTimeXXX.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DateTimeXXX w;
    w.show();

    return a.exec();
}
