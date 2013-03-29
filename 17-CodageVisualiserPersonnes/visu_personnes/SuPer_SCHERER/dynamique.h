#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include <QObject>
#include <QLabel>

#define MAXONGLETS 20   //maximum d'onglets possible
#define MAXLECTEURS 40  //maximum de lecteurs possible
#define MAXBADGES 40    //maximum de badges possible

//////////////////////////////////////////////////////////////
/*** CLASSE pour sauvegarder les objets créé dynamiquement***/
class Dynamique : public QObject
{
    Q_OBJECT
public:
    explicit Dynamique(QObject *parent = 0);

    QWidget *onglet[MAXONGLETS];    //pointeur sur l'onglet
    QLabel *labelL[MAXONGLETS][MAXLECTEURS];    //pointeur sur le label du lecteur
    QLabel *labelB[MAXONGLETS][MAXBADGES];      //pointeur sur le label du badge
    
signals:
    
public slots:
    
};

#endif // DYNAMIQUE_H
