#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qDebug();

    Server server("127.0.0.254", "43210");
    MainWindow w1(&server);
    //MainWindow w2(&server);
    w1.show();
    //w2.show();
    
    return a.exec();
}
