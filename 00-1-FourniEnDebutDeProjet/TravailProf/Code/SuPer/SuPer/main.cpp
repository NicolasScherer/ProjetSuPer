#include <QtGui/QApplication>
#include "fident.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FIdent w;
    w.show();

    return a.exec();
}
