#ifndef CONFIGURER_H
#define CONFIGURER_H

#include <QMainWindow>
#include "bdd.h"

namespace Ui {
class Configurer;
}

class Configurer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Configurer(QWidget *parent = 0);
    ~Configurer();
    
private slots:
    void on_btAffLog_clicked();

    void on_btSuppLog_clicked();

private:
    Ui::Configurer *ui;

    //pointeur sur la classe BDD
    Bdd *pBdd;
};

#endif // CONFIGURER_H
