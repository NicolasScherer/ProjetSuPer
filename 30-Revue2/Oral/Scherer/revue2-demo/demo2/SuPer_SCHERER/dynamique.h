#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include <QObject>
#include <QLabel>

#define MAXONGLETS 20   //maximum d'onglets possible
#define MAXLECTEURS 40  //maximum de lecteurs possible

//////////////////////////////////////////////////////////////
/*** CLASSE pour sauvegarder les objets créé dynamiquement***/
class Dynamique : public QObject
{
    Q_OBJECT
public:
    explicit Dynamique(QObject *parent = 0);

    QWidget *onglet[MAXONGLETS];    //pointeur sur l'onglet
    QLabel *labelL[MAXLECTEURS][MAXONGLETS];    //pointeur sur le label du lecteur
    
signals:
    
public slots:
    
};

#endif // DYNAMIQUE_H
