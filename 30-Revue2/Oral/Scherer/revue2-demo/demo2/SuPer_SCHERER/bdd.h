#ifndef BDD_H
#define BDD_H

#include <QObject>
#include <QtSql>
#include <QList>
#include <QMessageBox>

//////////////////////////////////////////
/*** STRUCTURE pour retour de fonction***/
//enregistrement d'un onglet
typedef struct s_TupleOnglet {
    int num_vue;
    QString legende;
    QString image;

} T_TupleOnglet;
//enregistrement d'un lecteur qui veut se déconnecter
typedef struct s_TupleLecteurS {
    int num_vue;
} T_TupleLecteurS;

//enregistrement d'un lecteur qui se connecte
typedef struct s_TupleLecteurE {
    int num_vue;
    int x;
    int y;
} T_TupleLecteurE;

/////////////////////////////////////////////
/*** CLASSE pour gérer la Base de Données***/
class Bdd : public QObject
{
    Q_OBJECT
public:
    explicit Bdd(QObject *parent = 0);
    ~Bdd();

    int getVueMax();    //obtenir vue max
    bool getVueFctLect(int numLecteur, QList<T_TupleLecteurS> *); //obtenir la vue en fonction du lecteur
    bool getVuePosFctLect(int numLecteur, QList<T_TupleLecteurE> *);   //obtenir la vue et la position (x,y) en fonction du lecteur
    bool getVue(QList<T_TupleOnglet>*);   //obtenir toutes les vues

private:
    //pointeurs sur structure
    T_TupleOnglet *pTupleOnglet;
    T_TupleLecteurS * pTupleLecteurS;
    T_TupleLecteurE * pTupleLecteurE;

    QSqlQuery * query;
    QSqlDatabase  database;
    
signals:
    
public slots:
    
};

#endif // BDD_H
