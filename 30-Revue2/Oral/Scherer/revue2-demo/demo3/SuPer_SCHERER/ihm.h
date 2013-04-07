#ifndef IHM_H
#define IHM_H

#include <QMainWindow>

#include "lecteur.h"
#include "dynamique.h"
#include "bdd.h"

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

    //Ihm dynamique (initialisation)
    void ajoutOnglet(int num_vue, QString legende, QString image);
    void ajoutLecteur(int numLecteur, int num_vue, int x, int y);
    void suppLecteur(int numLecteur, int num_vue);

    //pointeur sur la classe Dynamique (sauvegarde de l'affichage dynamique)
    Dynamique *pDynamique;
    //pointeur sur la classe BDD
    Bdd *pBdd;

signals:
    void signalNewLecteur(Lecteur *pLecteur);         //doit disparaitre à l'intégration

public slots:
    //lié à la connexion/déconnexion des lecteurs
    void lecteurActif(Lecteur *pLecteur);
    void lecteurActif3(Lecteur *pLecteur);
    void lecteurInactif(Lecteur *pLecteur);
    void lecteurInconnu();


private slots:
    //bouton sur l'ihm pour quitter
    void on_btQuitter_clicked();
};

#endif // IHM_H
