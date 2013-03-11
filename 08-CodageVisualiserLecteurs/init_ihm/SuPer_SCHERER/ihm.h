#ifndef IHM_H
#define IHM_H

#include <QMainWindow>
#include <QtSql>
#include "lecteur.h"

namespace Ui {
class Ihm;
}

class Ihm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Ihm(QWidget *parent = 0);
    ~Ihm();

private:
    Ui::Ihm *ui;

    //onglet dynamique
    void ajoutOnglet(int num_vue, QString legende, QString image);
    int getVueMax();    //lié à BDD

    //BDD
    QSqlQuery * query;
    QSqlDatabase  database;

public slots:
    void lecteurActif(Lecteur *pLecteur);


signals:
    void signalNewLecteur(Lecteur *pLecteur);         //doit disparaitre à l'intégration
};

#endif // IHM_H
