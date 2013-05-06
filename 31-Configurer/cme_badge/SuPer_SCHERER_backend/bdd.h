#ifndef BDD_H
#define BDD_H

#include <QObject>
#include <QtSql>
#include <QList>
#include <QMessageBox>


//////////////////////////////////////////
/*** STRUCTURE pour retour de fonction***/
//////////////////////////////////////////
//fichier log
typedef struct s_Log {
    QString date;
    QString legende;
    QString nom;
    QString prenom;
    QString societe;
} T_Log;
//personne
typedef struct s_Pers {
    QString nom;
    QString prenom;
    QString societe;
    QString dateDebut;
    QString dateFin;
} T_Personne;

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
    bool removeLog();   //suppression historique

    //gestion badge //lier/délier
    bool getBadgeExistant(QString *);    //obtenir liste badge existant
    bool getPersonneLier(QList<T_Personne>*);   //obtenir liste personne à lier
    int getNumPersonne(QString);       //obtenir numéro de la personne
    bool setLier(int numPersonne, QString numBadge, QString dateService, QString datePile); //affectation

private:
    //pointeurs sur structure
    T_Log * pLog;
    T_Personne * pPersonne;


    QSqlQuery * query;
    QSqlDatabase  database;
    QString requete;  // requête parfois utilisé
    
signals:
    
public slots:
    
};

#endif // BDD_H
