#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include <QObject>
#include <QLabel>

//#define MAXONGLETS 20   //maximum d'onglets possible
//#define MAXLECTEURS 40  //maximum de lecteurs possible (NB : 1 lieu = 1 lecteur)
//#define MAXBADGES 40    //maximum de badges possible
//#define MAXPERSONNES 200    //maximum de personnes possible

//////////////////////////////////////////////////////////////
/*** CLASSE pour sauvegarder les objets créé dynamiquement***/
class Dynamique : public QObject
{
    Q_OBJECT
public:
    explicit Dynamique(QObject *parent = 0);

    static const int MAXONGLETS = 20;       //maximum d'onglets possible
    static const int MAXLECTEURS = 40;      //maximum de lecteurs possible (NB : 1 lieu = 1 lecteur)
    static const int MAXBADGES = 40;        //maximum de badges possible
    static const int MAXPERSONNES = 200;    //maximum de personnes possible
    static const int MAXVAL = 20;           //nombre de valeur pour faire la moyenne sensibilité

    /*---Pointeurs---*/
    QWidget *onglet[MAXONGLETS];    //pointeur sur l'onglet
    QLabel *labelL[MAXONGLETS][MAXLECTEURS];    //pointeur sur le label du lecteur
    QLabel *labelB[MAXONGLETS][MAXBADGES];      //pointeur sur le label du badge

    /*---Personne---*/
    QString nom[MAXPERSONNES];      //sauvegarde identité personne, nom
    QString prenom[MAXPERSONNES];   //prenom
    QString societe[MAXPERSONNES];  //societe

    /*---Badge---*/
    bool BadgeActif[MAXBADGES];     //badge actif ou non

    /*---Points de la droite---*/
    int xPointA[MAXONGLETS][MAXLECTEURS];   // x du point A
    int yPointA[MAXONGLETS][MAXLECTEURS];   // y du point A
    int xPointB[MAXONGLETS][MAXLECTEURS];   // x du point B
    int yPointB[MAXONGLETS][MAXLECTEURS];   // y du point B

    /*---Timer---*/
    QTimer *tpsMouv;                //timer sur le mouvement
    QTimer *tpsSens[MAXLECTEURS];   //timer sur la réception

    /*---Position---*/
    int moySens[MAXLECTEURS][MAXVAL];   //moyenne réception
    int indMoy[MAXLECTEURS];    //indice moyenne
    int sdp[MAXLECTEURS];       //sens de passage
    int sdpMem[MAXLECTEURS];    //sens de passage mémorisé (sdp -1)

    
signals:
    
public slots:
    
};

#endif // DYNAMIQUE_H
