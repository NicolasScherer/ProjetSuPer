#include <QApplication>
#include "configurer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Configurer w;
    w.show();
    
    return a.exec();
}
