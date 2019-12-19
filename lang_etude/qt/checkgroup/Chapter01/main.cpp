#include "MainWindow.h"
#include "SubWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    SubWindow sw("Sub");
    sw.show();

    return a.exec();
}
