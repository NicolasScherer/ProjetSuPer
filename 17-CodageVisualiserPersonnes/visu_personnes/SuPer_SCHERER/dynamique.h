#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include <QObject>
#include <QLabel>

#define MAXONGLETS 20   //maximum d'onglets possible
#define MAXLECTEURS 40  //maximum de lecteurs possible (NB : 1 lieu = 1 lecteur)
#define MAXBADGES 40    //maximum de badges possible
#define MAXPERSONNES 200    //maximum de personnes possible

//////////////////////////////////////////////////////////////
/*** CLASSE pour sauvegarder les objets créé dynamiquement***/
class Dynamique : public QObject
{
    Q_OBJECT
public:
    explicit Dynamique(QObject *parent = 0);

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

    
signals:
    
public slots:
    
};

#endif // DYNAMIQUE_H
