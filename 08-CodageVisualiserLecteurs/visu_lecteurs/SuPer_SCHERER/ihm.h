#ifndef IHM_H
#define IHM_H

#include <QMainWindow>
#include <QtSql>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QtGui>

#include "lecteur.h"
#include "dynamique.h"

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
    Lecteur *pLecteur;

    //onglet dynamique
    void ajoutOnglet(int num_vue, QString legende, QString image);
    int getVueMax();    //lié à BDD

    int getNumLieu();
    void ajoutLecteur(int numLecteur, int num_vue, int x, int y);
    void suppLecteur(int numLecteur, int num_vue);

    //pointeur sur la classe Dynamique (sauvegarde de l'affichage dynamique)
    Dynamique *pDynamique;
    //pointeur sur la classe onglet
    //Onglet *pOnglet;
    QWidget *onglet;

    //BDD
    QSqlQuery * query;
    QSqlDatabase  database;
signals:
    void signalNewLecteur(Lecteur *pLecteur);         //doit disparaitre à l'intégration

public slots:
   void lecteurActif(Lecteur *pLecteur);
   void lecteurInactif(Lecteur *pLecteur);



private slots:
   void on_btQuitter_clicked();
};

#endif // IHM_H
