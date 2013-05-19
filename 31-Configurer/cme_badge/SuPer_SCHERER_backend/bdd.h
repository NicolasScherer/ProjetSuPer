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

//badge
typedef struct s_Badge {
    QString numBadge;
    QString dateMiseEnService;
    QString dateChangePile;
    QString nom;
    QString prenom;
    QString societe;
    QString dateDebut;
    QString dateFin;
} T_Badge;

//vue
typedef struct s_Vue {
    QString numVue;
    QString legende;
    QString image;
} T_Vue;

//lieu
typedef struct s_Lieu {
    QString numLieu;
    QString legende;
} T_Lieu;

//zone
typedef struct s_Zone {
    QString numZone;
    QString numLieu;
    QString sensMonter;
    QString legende;
} T_Zone;

//représentation
typedef struct s_Representation {
    QString numVue;
    QString numLieu;
    QString numZone;
    QString x;
    QString y;
    QString xA;
    QString yA;
    QString xB;
    QString yB;
} T_Representation;

/////////////////////////////////////////////
/*** CLASSE pour gérer la Base de Données***/
class Bdd : public QObject
{
    Q_OBJECT
public:
    explicit Bdd(QObject *parent = 0);
    ~Bdd();

    //+++ gestion log +++
    bool getLog(QList<T_Log> *);  //obtenir historique des événements
    bool removeLog();   //suppression historique

    //+++ gestion badge +++
    //lier/délier
    bool getBadgeExistant(QString *);    //obtenir liste badge existant
    bool getPersonneLier(QList<T_Personne>*);   //obtenir liste personne à lier
    int getNumPersonne(QString);       //obtenir numéro de la personne
    bool setLier(int numPersonne, QString numBadge, QString dateService, QString datePile); //affectation
    bool getBadgeNonActif(QList<T_Badge> *);   //obtenir badge non actifs   
    bool addModLier(int numPersonne, QString numBadge, QString dateService, QString datePile); //modifier affectation
    bool setDelier(int numPersonne);        //desaffectation

    //+++ gestion configurer SuPer +++
    //--- gestion des vues ---
    bool getVueExistant(QList<T_Vue> *);   //obtenir liste vue existante
    bool setVue(QString numVue, QString legende, QString image); //ajouter vue
    bool addModVue(QString legendeActuelle, QString numVue, QString legende, QString image); //modifier vue
    bool setSuppVue(QString numVue);    //supprimer vue

    //--- gestion des lieux ---
    bool getLieuExistant(QList<T_Lieu> *);  //obtenir liste lieu existant
    bool setLieu(QString numLieu, QString legende); //ajouter lieu
    bool addModLieu(QString legendeActuelle, QString numLieu, QString legende); //modifier lieu
    bool setSuppLieu(QString numLieu);      //supprimer lieu

    //--- gestion des zones ---
    bool getZoneExistant(QList<T_Zone> *);  //obtenir liste zone existante
    bool setZone(QString numZone, int numLieu, QString sensMonter, QString legende);    //ajouter zone
    int getNumLieu(QString);    //obtenir numéro du lieu
    bool addModZone(QString numZone, QString numLieuActuel, QString numLieu, QString sensMonter, QString legende); //modifier zone
    bool setSuppZone(QString numZone);  //supprimer zone

    //--- gestion des positions ---
    QString getLegendeLieu(QString numLieu);    //obtenir legende lieu
    bool getRepresentation(QList<T_Representation> *, QString numVue, QString numZone);  //obtenir représentation si elle existe
    bool setPosition(QString, QString, QString, QString, QString, QString, QString, QString, QString);   //ajouter positions
    bool addModPosition(QString, QString, QString, QString, QString, QString, QString, QString, QString); //modifier positions
    bool getZoneLierVue(QList<T_Representation> *, QString numVue);     //obtenir les zones liées avec cette vue
    bool setSuppPosition(QString numVue, QString numZone);  //supprimer position

    //--- gestion des timers ---
    void getTempo(int *, int *);    //obtenir tempo
    bool setTempo(QString tempoMouv, QString tempoRecep);   //modifier tempo

private:
    //pointeurs sur structure
    T_Log * pLog;
    T_Personne * pPersonne;
    T_Badge * pBadge;
    T_Vue * pVue;
    T_Lieu * pLieu;
    T_Zone * pZone;
    T_Representation * pRepresentation;


    QSqlQuery * query;
    QSqlDatabase  database;
    QString requete;  // requête parfois utilisé
    
signals:
    
public slots:
    
};

#endif // BDD_H
