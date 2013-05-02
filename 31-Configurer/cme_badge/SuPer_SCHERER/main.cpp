#include <QApplication>
#include <QLabel>
#include "ihm.h"
#include "configurer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ihm w;
    w.show();
    Configurer y;
    y.show();
    
    return a.exec();
}


