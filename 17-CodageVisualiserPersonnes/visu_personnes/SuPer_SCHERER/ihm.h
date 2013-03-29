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

// Permet le mise en correspondance d'un QLabel de position avec un badge.
// création dynamique des logo affiché représentant les personnes badgées.
typedef struct s_listeLabel {
    QLabel *l;     // référence du label d'affichage
    QTimer *wdm;   // timer de watchdog de mouvement
   // QTimer *wdr[MAX_LECT];   // timer de watchdog de réception
    T_Pers pers;
    T_Point ptA, ptB, ptF;
    int noBadge;
    int noLect;  // dernier nO de lecteur lu
    int etat;  // bit0:Mouv(0:RAS, 1:TO)   bit1:REC(0:RAS, 1:TO)  bit2:SENS(0:haut, 1:bas) bit3:MOUV0
    int zone;   // lieu géographique d'affichage du badge
  //  int moySens[MAX_LECT][MAX_VAL];
  //  int indMoy[MAX_LECT];
  //  int sdp[MAX_LECT];
  //  int memSdp[MAX_LECT];
} T_ListeLabel;


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
