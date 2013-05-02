#include "bdd.h"

//////////////////////
/*** CONSTRUCTEUR ***/
Bdd::Bdd(QObject *parent) :
    QObject(parent)
{
    pDynamique = new Dynamique; //allocation pointeur sur classe Dynamique


    qDebug() << "database deja ouverte" << endl;

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
    delete pDynamique;
    delete query;
    database.close();
}
/////////////////////
void Bdd::setLog(int typeLog, int numBadge){
 //   switch (typeLog){
 //   case 1 :    //nouveau badge


 //   }

    //requete sql en fonction du type de log
    //+num badge

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


///////////////////////////////////////////
void Bdd::setBadgeActif(int numBadge)
{
    //avec le numéro de badge, mettre qu'il n'est pas perdu
    requete = "UPDATE badge ";
    requete += "SET estActif=1 ";
    requete += "WHERE num_badge=:numBadge";
    query->prepare(requete);
    query->bindValue(":numBadge", numBadge);
    if (!query->exec())
        qDebug() << "Erreur requete SQL badge actif (perte badge)" << endl;

}
///////////////////////////////////////////////
void Bdd::setBadgePerdu(int numBadge)
{
    //avec le numéro de badge, mettre qu'il est perdu !
    requete = "UPDATE badge ";
    requete += "SET estActif=0 ";
    requete += "WHERE num_badge=:numBadge";
    query->prepare(requete);
    query->bindValue(":numBadge", numBadge);
    if (!query->exec())
        qDebug() << "Erreur requete SQL badge actif (perte badge)" << endl;

}

//////////////////////////////////////////////
bool Bdd::getPointsZone(int vue, int zone, T_Point *pointA, T_Point *pointB)
{
    //avec la zone et la vue, obtenir les points de la droite
    requete = "SELECT xA, yA, xB, yB ";
    requete += "FROM representationLieuSurVue ";
    requete += "WHERE num_vue =:vue AND num_zone =:zone";
    query->prepare(requete);
    query->bindValue(":vue", vue);
    query->bindValue(":zone", zone);
    if (!query->exec()) return false;
    if (!query->size()) return false;
    query->next();
    pointA->x=query->value(0).toInt();
    pointA->y=query->value(1).toInt();
    pointB->x=query->value(2).toInt();
    pointB->y=query->value(3).toInt();
    return true;
}

////////////////////
// co/déco lecteur
void Bdd::setEtatLect(int numLecteur, bool etat){

    //avec le numéro de lecteur et son état le mettre à jour dans la BDD
    requete = "UPDATE lecteur ";
    requete += "SET estConnecte=:etat ";
    requete += "WHERE num_lecteur=:numLecteur";
    query->prepare(requete);
    query->bindValue(":etat", etat);
    query->bindValue(":num_lecteur", numLecteur);
    if (!query->exec())
        qDebug() << "Erreur requete SQL co/déco lecteur" << endl;

}

///////////////////////
// voir état lecteur (co ou déco)
bool Bdd::getEtatLect(int numLecteur){

    //avec le numéro de lecteur obtenir l'état du lecteur (connecté ou non)
    requete = "SELECT estConnecte ";
    requete += "FROM lecteur ";
    requete += "WHERE num_lecteur=:numLecteur";
    query->prepare(requete);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL etat lecteur" << endl;
         return -1;
    }

    query->next();
    int etat = query->value(0).toInt();
    if (etat == 0)
        return false;

return true;
}



/*-----------------------------------*
 * Méthode pour obtenir l'identité   *
 * de la personne possédant le badge *
 *-----------------------------------*/
int Bdd::badgeIdentite(int num_badge_i, QList<T_Personne> *listePersonne){

    //avec le numéro de badge obtenir l'identité de la personne
    requete = "SELECT A1.num_pers, A2.nom, A2.prenom, A2.societe, A2.photo ";
    requete += "FROM badge A1, personne A2 ";
    requete += "WHERE A1.num_pers=A2.num_pers AND A1.num_badge=:num_badge_i";
    query->prepare(requete);
    query->bindValue(":num_badge_i", num_badge_i);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL identite badge" << endl;
         return -1;
    }

    //allocation pointeur
    this->pPersonne = new T_Personne;

    if (query->size() > 0){
        query->next();
        int num_pers = query->value(0).toInt();

        //ajout liste
        this->pPersonne->nom = query->value(1).toString();
        this->pPersonne->prenom = query->value(2).toString();
        this->pPersonne->societe = query->value(3).toString();
        this->pPersonne->photo = query->value(4).toString();
        listePersonne->append(*pPersonne);

        delete this->pPersonne;

        return num_pers;
    }else{
        return -1;
    }
}

/*--------------------------------------*
 * Méthode pour obtenir les coordonnées *
 * d'un lieu en fonction d'un lecteur   *
 * et d'une vue                         *
 *--------------------------------------*/
/*bool Bdd::getPositionLieu(int num_vue, int num_lecteur, QList<T_TuplePositionLieu> *positionLieu){

    //avec le numéro de lecteur et la vue obtenir la position lieu
    requete = "SELECT DISTINCT A1.xA, A1.yA, A1.xB, A1.yB ";
    requete += "FROM representationLieuSurVue A1 ";
    requete += "WHERE A1.num_vue=:num_vue AND A1.num_lieu=:num_lecteur";
    query->prepare(requete);
    query->bindValue(":num_vue", num_vue);
    query->bindValue(":num_lecteur", num_lecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL position lieu" << endl;
         return false;
    }

    //allocation pointeur
    this->pTuplePositionLieu = new T_TuplePositionLieu();

    //réponse requête
    while(query->next()){
        int xA = query->value(0).toInt();
        int yA = query->value(1).toInt();
        int xB = query->value(2).toInt();
        int yB = query->value(3).toInt();

        //ajout sur liste
        this->pTuplePositionLieu->xA = xA;
        this->pTuplePositionLieu->yA = yA;
        this->pTuplePositionLieu->xB = xB;
        this->pTuplePositionLieu->yB = yB;

        positionLieu->append(*pTuplePositionLieu);
    }

    delete this->pTuplePositionLieu;

    return true;
}
*/
//////////////////////////////////////
/*** METHODE pour OBTENIR VUE MAX ***/
int Bdd::getVueMax(){

    //requête
    if(!query->exec("SELECT COUNT(*) FROM vue")){
        qDebug() << "Erreur requete SQL" << endl; //<< database->lastError() << endl;
        //test si problème lors de l'envoi de la requete
    }

    int vueMax;
    //réponse requête
    while(query->next()){
        vueMax = query->value(0).toInt();
    }
    return vueMax;
}
////////////////////////////////////////
/*** obtenir sens de passage (type de zone)
 * montée, descentee, contigu ****/
int Bdd::getSensMonter(int numLecteur){

    //avec le numéro de lecteur, obtenir le type de zone
    requete = "SELECT DISTINCT A1.sensMonter ";
    requete += "FROM zone A1, lecteur A2 ";
    requete += "WHERE A1.num_lieu = A2.num_lieu AND A2.num_lecteur =:numLecteur";
    query->prepare(requete);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL sens de passage (zone)" << endl;
         return -1;
    }
    //réponse requête
    query->next();
    int sensMonter = query->value(0).toInt();
    return sensMonter;

}


/////////////////////////////////////////////////////////
/*** METHODE pour OBTENIR VUE en FONCTION du n° LECTEUR ***/
bool Bdd::getVueFctLect(int numLecteur, QList<T_TupleLecteurS> *listeLecteur){

    //avec le numéro obtenu, obtenir la vue
    requete = "SELECT DISTINCT A1.num_lieu, A2.num_vue ";
    requete += "FROM lecteur A1, representationLieuSurVue A2 ";
    requete += "WHERE A1.num_lieu = A2.num_lieu AND A1.num_lecteur=:numLecteur";
    query->prepare(requete);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL vue lecteur" << endl;
    }

    //allocation pointeur
    this->pTupleLecteurS = new T_TupleLecteurS();

    //réponse requête
    while(query->next()){
         int num_vue = query->value(1).toInt();

        //ajout sur liste
         this->pTupleLecteurS->num_vue = num_vue;
         listeLecteur->append(*pTupleLecteurS);
    }

    delete this->pTupleLecteurS;

    return true;
}
///////////////////////////////////////////////////////////////////
/*** METHODE OBTENIR VUE et POSITION en FONCTION du n° LECTEUR ***/
bool Bdd::getVuePosFctLect(int numLecteur, QList<T_TupleLecteurE> *listeLecteur){

    //avec le numéro obtenu, obtenir la vue et la position (x,y)
    requete = "SELECT DISTINCT A1.num_lieu, A2.num_vue, A2.x, A2.y ";
    requete += "FROM lecteur A1, representationLieuSurVue A2 ";
    requete += "WHERE A1.num_lieu = A2.num_lieu AND A1.num_lecteur=:numLecteur";
    query->prepare(requete);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL vue/position lecteur" << endl;
    }

    //allocation pointeur
    this->pTupleLecteurE = new T_TupleLecteurE();

    //réponse requête
    while(query->next()){
         int num_vue = query->value(1).toInt();
         int x = query->value(2).toInt();
         int y = query->value(3).toInt();

        //ajout sur liste
         this->pTupleLecteurE->num_vue = num_vue;
         this->pTupleLecteurE->x = x;
         this->pTupleLecteurE->y = y;
         listeLecteur->append(*pTupleLecteurE);
    }

    delete this->pTupleLecteurE;

    return true;
}
/////////////////////////////////////////
/*** METHODE OBTENIR TOUTES LES VUES ***/
bool Bdd::getVue(QList<T_TupleOnglet> *listeOnglet){

    // requête
    if(!query->exec("SELECT * FROM vue")){
        qDebug() << "Erreur requete SQL" << endl << database.lastError() << endl;
        //test si problème lors de l'envoi de la requete
    }

    //allocation pointeur
    this->pTupleOnglet = new T_TupleOnglet;

    //réponse requete
    while(query->next()){
        int num_vue = query->value(0).toInt();
        QString legende = query->value(1).toString();
        QString image = query->value(2).toString();

        //ajout liste
        this->pTupleOnglet->num_vue = num_vue;
        this->pTupleOnglet->legende = legende;
        this->pTupleOnglet->image = image;
        listeOnglet->append(*pTupleOnglet);

    }

    delete this->pTupleOnglet;

    return true;
}
////////////////////////////////////////////
/*** METHODE est-ce qu'un badge existe ?***/
bool Bdd::badgeExiste(QString &num_badge){

    //requête
    requete = "SELECT * FROM badge WHERE num_badge=:numBadge LIMIT 1";
    query->prepare(requete);
    query->bindValue(":numBadge", num_badge);

    if (!query->exec()){
        qDebug("Erreur MySQL badgeExiste");
        return false;
    }

    //réponse requête
    //astuce : connaitre son nombre de ligne renvoyé permet de savoir si la requête est fructueuse
    //puisqu'on a demandé LIMIT 1
    int nbLigne = query->size();

    //le badge existe
    if(nbLigne == 1){
        query->next();
        return true;
    }

    //le badge n'existe pas
    return false;
}
