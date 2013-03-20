#ifndef DYNAMIQUE_H
#define DYNAMIQUE_H

#include <QObject>
#include <QLabel>

#define MAXONGLETS 20
#define MAXLECTEURS 40

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
