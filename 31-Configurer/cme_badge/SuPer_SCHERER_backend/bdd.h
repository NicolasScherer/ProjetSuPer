#ifndef BDD_H
#define BDD_H

#include <QObject>
#include <QtSql>
#include <QList>
#include <QMessageBox>


//////////////////////////////////////////
/*** STRUCTURE pour retour de fonction***/
//////////////////////////////////////////
//identité personne
typedef struct s_Personne {
    QString nom;      //sauvegarde identité personne, nom
    QString prenom;   //prenom
    QString societe;  //societe
    QString photo;    //photographie

} T_Personne;
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

//enregistrement des positions d'un lieu par rapport à une vue
typedef struct s_TuplePositionLieu {
    int xA;
    int yA;
    int xB;
    int yB;
} T_TuplePositionLieu;

//fichier log
typedef struct s_Log {
    QString date;
    QString legende;
    QString nom;
    QString prenom;
    QString societe;
} T_Log;

/////////////////////////////////////////////
/*** CLASSE pour gérer la Base de Données***/
class Bdd : public QObject
{
    Q_OBJECT
public:
    explicit Bdd(QObject *parent = 0);
    ~Bdd();

    //gestion log
    bool getLog(QList<T_Log> *);  //obtenir historique des événements
    void setLog(int typeLog, int numBadge);  //mettre à jour historique des événements


private:
    //pointeurs sur structure
    T_TupleOnglet * pTupleOnglet;
    T_TupleLecteurS * pTupleLecteurS;
    T_TupleLecteurE * pTupleLecteurE;
    T_TuplePositionLieu * pTuplePositionLieu;
    T_Personne * pPersonne;
    T_Log * pLog;


    QSqlQuery * query;
    QSqlDatabase  database;
    QString requete;  // requête parfois utilisé
    
signals:
    
public slots:
    
};

#endif // BDD_H
