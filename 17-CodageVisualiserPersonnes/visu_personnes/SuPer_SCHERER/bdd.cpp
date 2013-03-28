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
}

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
/////////////////////////////////////////////////////////
/*** METHODE pour OBTENIR VUE en FONCTION du n° LECTEUR ***/
bool Bdd::getVueFctLect(int numLecteur, QList<T_TupleLecteurS> *listeLecteur){

    //avec le numéro obtenu, obtenir la vue
    requete = "SELECT A1.num_lieu, A2.num_vue ";
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
    requete = "SELECT A1.num_lieu, A2.num_vue, A2.x, A2.y ";
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
