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


