#include "bdd.h"

//////////////////////
/*** CONSTRUCTEUR ***/
Bdd::Bdd(QObject *parent) :
    QObject(parent)
{
    //accès BDD
    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("bdd_super");
    database.setUserName("user_super");
    database.setPassword("mdp_super");
    bool ok = database.open();
    if (!ok){
        qDebug() << database.lastError();
        QMessageBox::critical(0, tr("Impossible d'ouvrir la BDD."),
                 tr("Impossible d'etablir une connexion avec la Base de Donnees.\n"),
                          QMessageBox::Cancel);

    }
    query = new QSqlQuery;
}
/////////////////////
/*** DESTRUCTEUR ***/
Bdd::~Bdd(){
    delete query;
    database.close();
}
////////
//obtenir uniquement les numéros de personne qui n'apparraissent pas dans badge
bool Bdd::getPersonneLier(QList<T_Personne> *listePersonne){

    // requête
    requete = "SELECT A1.nom, A1.prenom, A1.societe, A1.dateDebut, A1.dateFin ";
    requete += "FROM personne A1, badge ";
    requete += "WHERE NOT A1.num_pers = badge.num_pers";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL personneLier" << endl << database.lastError() << endl;
        return false;
    }

    if(query->size() == 0)
        return false;

    //allocation pointeur
    this->pPersonne = new T_Personne;

    //réponse requete
    while(query->next()){
        QString nom = query->value(0).toString();
        QString prenom = query->value(1).toString();
        QString societe = query->value(2).toString();
        QString dateDebut = query->value(3).toString();
        QString dateFin = query->value(4).toString();

        //ajout liste
        this->pPersonne->nom = nom;
        this->pPersonne->prenom = prenom;
        this->pPersonne->societe = societe;
        this->pPersonne->dateDebut = dateDebut;
        this->pPersonne->dateFin = dateFin;
        listePersonne->append(*pPersonne);

    }

    delete this->pPersonne;

    return true;
}
////////
//obtenir le numéro de la personne
int Bdd::getNumPersonne(QString personne){
    //requete
    requete = "SELECT num_pers ";
    requete += "FROM personne ";
    requete += "WHERE nom=:personne";
    query->prepare(requete);
    query->bindValue(":personne", personne);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL obtenir num personne" << endl << database.lastError() << endl;
        return -1;
    }
    //réponse requete
    query->next();
    int numPersonne = query->value(0).toInt();
    return numPersonne;
}
////////
//mettre en oeuvre l'affectation
bool Bdd::setLier(int numPersonne, QString numBadge, QString dateService, QString datePile){
    //requete
    requete = "INSERT INTO badge (num_badge, num_pers, dateMiseEnService, dateChangePile) ";
    requete += "VALUES (:numBadge, :numPersonne, :dateService, :datePile)";
    query->prepare(requete);
    query->bindValue(":numBadge", numBadge);
    query->bindValue(":numPersonne", numPersonne);
    query->bindValue(":dateService", dateService);
    query->bindValue(":datePile", datePile);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL affectation" << endl << database.lastError() << endl;
        return false;
    }
    return true;

}

////////
//obtenir la liste de l'historique des événements
bool Bdd::getLog(QList<T_Log> * listeLog){

    // requête
    //obtenir date, legende, nom, prénom, société (pour historique)
    requete = "SELECT A1.dateLog, A1.legende, A2.nom, A2.prenom, A2.societe ";
    requete += "FROM log A1, personne A2, badge A3 ";
    requete += "WHERE A1.num_badge=A3.num_badge AND A3.num_pers=A2.num_pers";
    query->prepare(requete);
    if (!query->exec()){
        qDebug() << "Erreur requete SQL historique evenement" << endl << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pLog = new T_Log;

    //bdd vide
    if(query->size() == 0)
        return false;

    //réponse requete
    while(query->next()){
        QString date_log = query->value(0).toString();
        QString legende = query->value(1).toString();
        QString nom = query->value(2).toString();
        QString prenom = query->value(3).toString();
        QString societe = query->value(4).toString();

        //ajout liste
        this->pLog->date = date_log;
        this->pLog->legende = legende;
        this->pLog->nom = nom;
        this->pLog->prenom = prenom;
        this->pLog->societe = societe;
        listeLog->append(*pLog);
    }

    delete this->pLog;

    return true;
}

/////////
//supprimer l'historique des événements
bool Bdd::removeLog(){
    //requête
    //supprimer tout les tuples de la table log
    requete = "DELETE FROM log";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL suppression historique" << endl << database.lastError() << endl;
        return false;
    }
    return true;

}

/////////
//obtenir badge existant
bool Bdd::getBadgeExistant(QString *badgeExistant){

    badgeExistant->fromUtf8("");

    //requête
    requete = "SELECT num_badge ";
    requete += "FROM badge";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL badge existant" << endl << database.lastError() << endl;
        return false;
    }

    //bdd vide
    if(query->size() == 0)
        return false;

    //réponse requete
    while(query->next()){
        badgeExistant->append(query->value(0).toString());
        badgeExistant->append(" ; ");
    }
    return true;
}


