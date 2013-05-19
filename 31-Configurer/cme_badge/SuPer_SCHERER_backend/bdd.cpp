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
    requete = "SELECT personne.nom, personne.prenom, personne.societe, personne.dateDebut, personne.dateFin ";
    requete += "FROM badge ";
    requete += "RIGHT JOIN personne ON personne.num_pers = badge.num_pers ";
    requete += "WHERE badge.num_pers IS NULL";
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
//apporter des modification à l'affectation
bool Bdd::addModLier(int numPersonne, QString numBadge, QString dateService, QString datePile){
    //requete

    requete = "UPDATE badge ";
    requete += "SET num_badge = :numBadge, dateMiseEnService = :dateService, dateChangePile = :datePile ";
    requete += "WHERE num_pers = :numPersonne";
    query->prepare(requete);
    query->bindValue(":numBadge", numBadge);
    query->bindValue(":dateService", dateService);
    query->bindValue(":datePile", datePile);
    query->bindValue(":numPersonne", numPersonne);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL modif affectation " << database.lastError() << endl;
        return false;
    }
    return true;

}
////////
//désaffecter badge à une personne
bool Bdd::setDelier(int numPersonne){
    //requete
    requete = "DELETE FROM badge ";
    requete += "WHERE num_pers = :numPersonne";
    query->prepare(requete);
    query->bindValue(":numPersonne", numPersonne);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL desaffectation " << database.lastError() << endl;
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
////////
//obtenir badge qui ne sont pas actif
bool Bdd::getBadgeNonActif(QList<T_Badge> *listeBadge){
    //requête
    requete = "SELECT A1.num_badge, A1.dateMiseEnService, A1.dateChangePile, A2.nom, A2.prenom, A2.societe, A2.dateDebut, A2.dateFin ";
    requete += "FROM badge A1, personne A2 ";
    requete += "WHERE A1.estActif = 0 AND A1.num_pers = A2.num_pers";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL badge non actif" << endl << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pBadge = new T_Badge;

    //réponse requête
    while(query->next()){
        QString num_badge = query->value(0).toString();
        QString dateMiseEnService = query->value(1).toString();
        QString dateChangePile = query->value(2).toString();
        QString nom = query->value(3).toString();
        QString prenom = query->value(4).toString();
        QString societe = query->value(5).toString();
        QString dateDebut = query->value(6).toString();
        QString dateFin = query->value(7).toString();

        //ajout liste
        this->pBadge->numBadge = num_badge;
        this->pBadge->dateMiseEnService = dateMiseEnService;
        this->pBadge->dateChangePile = dateChangePile;
        this->pBadge->nom = nom;
        this->pBadge->prenom = prenom;
        this->pBadge->societe = societe;
        this->pBadge->dateDebut = dateDebut;
        this->pBadge->dateFin = dateFin;
        listeBadge->append(*pBadge);
    }

    delete this->pBadge;
    return true;
}
////////
//ajouter une vue
bool Bdd::setVue(QString numVue, QString legende, QString image){
    //requete
    requete = "INSERT INTO vue (num_vue, legende, image) ";
    requete += "VALUES (:numVue, :legende, :image)";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    query->bindValue(":legende", legende);
    query->bindValue(":image", image);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL ajouter vue " << database.lastError() << endl;
        return false;
    }
    return true;

}
/////
//obtenir vue existante (QList)
bool Bdd::getVueExistant(QList<T_Vue> *listeVue){
    //requête
    requete = "SELECT num_vue, legende, image ";
    requete += "FROM vue";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL liste vue " << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pVue = new T_Vue;

    //réponse requête
    while(query->next()){
        QString num_vue = query->value(0).toString();
        QString legende = query->value(1).toString();
        QString image = query->value(2).toString();

        //ajout liste
        this->pVue->numVue = num_vue;
        this->pVue->legende = legende;
        this->pVue->image = image;

        listeVue->append(*pVue);
    }

    delete this->pVue;
    return true;
}
//////
//modifier vue
bool Bdd::addModVue(QString legendeActuelle, QString numVue, QString legende, QString image){
    //requete
    requete = "UPDATE vue ";
    requete += "SET num_vue = :numVue, legende = :legende, image = :image ";
    requete += "WHERE legende = :legendeActuelle";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    query->bindValue(":legende", legende);
    query->bindValue(":image", image);
    query->bindValue(":legendeActuelle", legendeActuelle);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL modif vue " << database.lastError() << endl;
        return false;
    }
    return true;
}
//////
//supprimer vue
bool Bdd::setSuppVue(QString numVue){
    //requete
    requete = "DELETE FROM vue ";
    requete += "WHERE num_vue = :numVue";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL supp vue " << database.lastError() << endl;
        return false;
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////
//obtenir liste des lieux existants
bool Bdd::getLieuExistant(QList<T_Lieu> *listeLieu){
    //requête
    requete = "SELECT num_lieu, legende ";
    requete += "FROM lieu";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL liste lieu " << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pLieu = new T_Lieu;

    //réponse requête
    while(query->next()){
        QString num_lieu = query->value(0).toString();
        QString legende = query->value(1).toString();

        //ajout liste
        this->pLieu->numLieu = num_lieu;
        this->pLieu->legende = legende;

        listeLieu->append(*pLieu);
    }

    delete this->pLieu;
    return true;
}
//////////
//ajouter lieu
bool Bdd::setLieu(QString numLieu, QString legende){
    //requete
    requete = "INSERT INTO lieu (num_lieu, legende) ";
    requete += "VALUES (:numLieu, :legende)";
    query->prepare(requete);
    query->bindValue(":numLieu", numLieu);
    query->bindValue(":legende", legende);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL ajouter lieu " << database.lastError() << endl;
        return false;
    }
    return true;
}
//////////
//modifier lieu
bool Bdd::addModLieu(QString legendeActuelle, QString numLieu, QString legende){
    //requete
    requete = "UPDATE lieu ";
    requete += "SET num_lieu = :numLieu, legende = :legende ";
    requete += "WHERE legende = :legendeActuelle";
    query->prepare(requete);
    query->bindValue(":numLieu", numLieu);
    query->bindValue(":legende", legende);
    query->bindValue(":legendeActuelle", legendeActuelle);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL modif lieu " << database.lastError() << endl;
        return false;
    }
    return true;
}
////////
//supprimer lieu
bool Bdd::setSuppLieu(QString numLieu){
    //requete
    requete = "DELETE FROM lieu ";
    requete += "WHERE num_lieu = :numLieu";
    query->prepare(requete);
    query->bindValue(":numLieu", numLieu);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL supp lieu " << database.lastError() << endl;
        return false;
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
//obtenir zone existante
bool Bdd::getZoneExistant(QList<T_Zone> * listeZone){
    //requête
    requete = "SELECT num_zone, num_lieu, sensMonter, legende ";
    requete += "FROM zone";
    query->prepare(requete);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL liste zone " << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pZone = new T_Zone;

    //réponse requête
    while(query->next()){
        QString num_zone = query->value(0).toString();
        QString num_lieu = query->value(1).toString();
        QString sensMonter = query->value(2).toString();
        QString legende = query->value(3).toString();

        //ajout liste
        this->pZone->numZone = num_zone;
        this->pZone->numLieu = num_lieu;
        this->pZone->sensMonter = sensMonter;
        this->pZone->legende = legende;

        listeZone->append(*pZone);
    }

    delete this->pZone;
    return true;
}
////////
//ajouter zone
bool Bdd::setZone(QString numZone, int numLieu, QString sensMonter, QString legende){
    //requete
    requete = "INSERT INTO zone (num_zone, num_lieu, sensMonter, legende) ";
    requete += "VALUES (:numZone, :numLieu, :sensMonter, :legende)";
    query->prepare(requete);
    query->bindValue(":numZone", numZone);
    query->bindValue(":numLieu", numLieu);
    query->bindValue(":sensMonter", sensMonter);
    query->bindValue(":legende", legende);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL ajouter zone " << database.lastError() << endl;
        return false;
    }
    return true;
}
///////
//obtenir numéro du lieu
int Bdd::getNumLieu(QString legende){
    //requete
    requete = "SELECT num_lieu ";
    requete += "FROM lieu ";
    requete += "WHERE legende=:legende";
    query->prepare(requete);
    query->bindValue(":legende", legende);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL obtenir num lieu " << database.lastError() << endl;
        return -1;
    }
    //réponse requete
    query->next();
    int numLieu = query->value(0).toInt();
    return numLieu;
}
////////
//modifier zone
bool Bdd::addModZone(QString numZone, QString numLieuActuel, QString numLieu, QString sensMonter, QString legende){
    //requete
    requete = "UPDATE zone ";
    requete += "SET num_lieu = :numLieu, sensMonter = :sensMonter, legende = :legende ";
    requete += "WHERE num_lieu = :numLieuActuel AND num_zone = :numZone";
    query->prepare(requete);
    query->bindValue(":numZone", numZone);
    query->bindValue(":numLieu", numLieu);
    query->bindValue(":sensMonter", sensMonter);
    query->bindValue(":legende", legende);
    query->bindValue(":numLieuActuel", numLieuActuel);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL modif zone " << database.lastError() << endl;
        return false;
    }
    return true;
}
///////
//supprimer zone
bool Bdd::setSuppZone(QString numZone){
    //requete
    requete = "DELETE FROM zone ";
    requete += "WHERE num_zone = :numZone";
    query->prepare(requete);
    query->bindValue(":numZone", numZone);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL supp zone " << database.lastError() << endl;
        return false;
    }
    return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////
//obtenir legende lieu
QString Bdd::getLegendeLieu(QString numLieu){
    //requête
    requete = "SELECT legende ";
    requete += "FROM lieu ";
    requete += "WHERE num_lieu = :numLieu";
    query->prepare(requete);
    query->bindValue(":numLieu", numLieu);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL get legende lieu " << database.lastError() << endl;
        return "erreur";
    }
    query->next();
    QString legende = query->value(0).toString();
    return legende;
}
//obtenir représentation
bool Bdd::getRepresentation(QList<T_Representation> *listeRepresentation, QString numVue, QString numZone){
    //requête
    requete = "SELECT A1.x, A1.y, A1.xA, A1.yA, A1.xB, A1.yB ";
    requete += "FROM representationLieuSurVue A1 ";
    requete += "WHERE num_vue=:numVue AND num_zone=:numZone";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    query->bindValue(":numZone", numZone);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL liste representation " << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pRepresentation = new T_Representation;

    //bdd vide
    if(query->size() == 0)
        return false;

    //réponse requête
    while(query->next()){
        QString x = query->value(0).toString();
        QString y = query->value(1).toString();
        QString xA = query->value(2).toString();
        QString yA = query->value(3).toString();
        QString xB = query->value(4).toString();
        QString yB = query->value(5).toString();

        //ajout liste
        this->pRepresentation->x = x;
        this->pRepresentation->y = y;
        this->pRepresentation->xA = xA;
        this->pRepresentation->yA = yA;
        this->pRepresentation->xB = xB;
        this->pRepresentation->yB = yB;

        listeRepresentation->append(*pRepresentation);
    }

    delete this->pRepresentation;
    return true;
}
//ajouter positions
bool Bdd::setPosition(QString numVue, QString numZone, QString numLieu, QString xA, QString yA, QString xB, QString yB, QString x, QString y){
    //requête
    requete = "INSERT INTO representationLieuSurVue (num_vue, num_lieu, num_zone, x, y, xA, yA, xB, yB) ";
    requete += "VALUES (:numVue, :numLieu, :numZone, :x, :y, :xA, :yA, :xB, :yB)";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    query->bindValue(":numLieu", numLieu);
    query->bindValue(":numZone", numZone);
    query->bindValue(":x", x);
    query->bindValue(":y", y);
    query->bindValue(":xA", xA);
    query->bindValue(":yA", yA);
    query->bindValue(":xB", xB);
    query->bindValue(":yB", yB);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL ajouter positions " << database.lastError() << endl;
        return false;
    }
    return true;
}
//modifier positions
bool Bdd::addModPosition(QString numVue, QString numZone, QString numLieu, QString xA, QString yA, QString xB, QString yB, QString x, QString y){
    //requete
    requete = "UPDATE representationLieuSurVue ";
    requete += "SET x=:x, y=:y, xA=:xA, yA=:yA, xB=:xB, yB=:yB ";
    requete += "WHERE num_vue=:numVue AND num_lieu=:numLieu AND num_zone=:numZone";
    query->prepare(requete);
    query->bindValue(":x", x);
    query->bindValue(":y", y);
    query->bindValue(":xA", xA);
    query->bindValue(":yA", yA);
    query->bindValue(":xB", xB);
    query->bindValue(":yB", yB);
    query->bindValue(":numVue", numVue);
    query->bindValue(":numLieu", numLieu);
    query->bindValue(":numZone", numZone);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL modif positions " << database.lastError() << endl;
        return false;
    }
    return true;
}
//recherche zones liées à une vue
bool Bdd::getZoneLierVue(QList<T_Representation> *listeRepresentation, QString numVue){
    //requête
    requete = "SELECT num_zone ";
    requete += "FROM representationLieuSurVue ";
    requete += "WHERE num_vue=:numVue ";
    requete += "ORDER BY num_zone ASC";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL liste zone lier vue " << database.lastError() << endl;
        return false;
    }

    //allocation pointeur
    this->pRepresentation = new T_Representation;

    //réponse requête
    while(query->next()){
        QString num_zone = query->value(0).toString();

        //ajout liste
        this->pRepresentation->numZone = num_zone;
        listeRepresentation->append(*pRepresentation);
    }

    delete this->pRepresentation;
    return true;
}
//supprimer position
bool Bdd::setSuppPosition(QString numVue, QString numZone){
    //requete
    requete = "DELETE FROM representationLieuSurVue ";
    requete += "WHERE num_vue = :numVue AND num_zone=:numZone";
    query->prepare(requete);
    query->bindValue(":numVue", numVue);
    query->bindValue(":numZone", numZone);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL supp position " << database.lastError() << endl;
        return false;
    }
    return true;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//obtenir tempo
void Bdd::getTempo(int *tempoM, int *tempoR){
    //requête
    requete = "SELECT tempoM, tempoR ";
    requete += "FROM super ";
    requete += "LIMIT 1";
    query->prepare(requete);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL obtenir tempo " << database.lastError() << endl;
    }

    //réponse requête
    query->next();
    *tempoM = query->value(0).toInt();
    *tempoR = query->value(1).toInt();

}
//modifier tempo
bool Bdd::setTempo(QString tempoMouv, QString tempoRecep){
    //requête
    requete = "UPDATE super ";
    requete += "SET tempoM=:tempoMouv, tempoR=:tempoRecep ";
    requete += "WHERE config=1";
    query->prepare(requete);
    query->bindValue("tempoMouv", tempoMouv);
    query->bindValue("tempoRecep", tempoRecep);
    if(!query->exec()){
        qDebug() << "Erreur requete SQL modif tempo " << database.lastError() << endl;
        return false;
    }
    return true;
}
