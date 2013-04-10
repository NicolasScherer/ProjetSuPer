#ifndef IHM_H
#define IHM_H

#include <QMainWindow>

#include "lecteur.h"
#include "dynamique.h"
#include "bdd.h"

//structure pour un Badge
typedef struct s_Badge {
    QString num_badge;
    QString num_pers;
    int dateMiseEnService;
    int dateChangePile;
    bool estActif;
} T_Badge;

typedef struct s_personne {
    QString nom, pnom;
    QString societe;
    QString dateDeb, dateFin;
    QString email;
    int noPers; // no unique de la personne
    QString ident;
    QString pass;
    QString exploit;
} T_Pers;

// structure pour le positionnement X, Y du label badge
typedef struct {
    int x,y;
} T_Point;

// configuration de SuPER
typedef struct {
    int tempoM,// ms tempo pour le timer mouvement
    tempoR,// ms tempo pour le timer de réception
    tempoA,// affichage général IHM
    maxVal;// Nbre de valeur pour faire la moyenne de sensibilité
} T_Config;

/////////////////////////////////

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

    //Ihm dynamique (initialisation + visualisation lecteur)
    void ajoutOnglet(int num_vue, QString legende, QString image);
    void ajoutLecteur(int numLecteur, int num_vue, int x, int y);
    void suppLecteur(int numLecteur, int num_vue);

    /*---Config de Super---*/
    int tempoM,// ms tempo pour le timer mouvement
    tempoR,// ms tempo pour le timer de réception
    tempoA;// affichage général IHM



    //pointeur sur la classe Dynamique (sauvegarde de l'affichage dynamique)
    Dynamique *pDynamique;
    //pointeur sur la classe BDD
    Bdd *pBdd;


signals:
    void signalNewLecteur(Lecteur *pLecteur);         //doit disparaitre à l'intégration

public slots:
    //lié à la connexion/déconnexion des lecteurs
    void lecteurActif(Lecteur *pLecteur);
    void lecteurInactif(Lecteur *pLecteur);
    void lecteurInconnu();

    //traitement de la trame
    bool traitementTrame(QString trame);

private slots:
    //bouton sur l'ihm pour quitter
    void on_btQuitter_clicked();
};

#endif // IHM_H
