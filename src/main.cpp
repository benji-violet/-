#include "mainwindow.h"
#include "map.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow window;
    Map map;

    window.show();
    return a.exec();
}
