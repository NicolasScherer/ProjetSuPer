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
    if (!ok)
        qDebug() << database.lastError();

    query = new QSqlQuery;
}

////////////////////////////////
/*** méthode obtenir VUE MAX **/
int Bdd::getVueMax()
{
    if(!query->exec("SELECT COUNT(*) FROM vue")){
        qDebug() << "Erreur requete SQL" << endl; //<< database->lastError() << endl;
        //test si problème lors de l'envoi de la requete
    }

    int vueMax;
    while(query->next()){
        vueMax = query->value(0).toInt();
    }
    return vueMax;
}
/////////////////////////////////////////
/*** méthode obtenir toutes les vues ***/
T_Tuple *Bdd::getVue(){
    if(!query->exec("SELECT * FROM vue")){
        qDebug() << "Erreur requete SQL" << endl << database.lastError() << endl;
        //test si problème lors de l'envoi de la requete
    }

    //réponse requete
    while(query->next()){
        int num_vue = query->value(0).toInt();
        QString legende = query->value(1).toString();
        QString image = query->value(2).toString();

        T_Tuple *pTtuple;
        pTtuple = new T_Tuple();

        pTtuple->num_vue = num_vue;
        pTtuple->legende = legende;
        pTtuple->image = image;
        listeTuple.append(pTtuple);

    }
    return listeTuple;
}

/////////////////////
/*** DESTRUCTEUR ***/
Bdd::~Bdd(){
   delete query;
}

////////////////////////////////////////////////////
/*** méthode obtenir vue en fonction du lecteur ***/
int Bdd::getVueFctLect(int numLecteur){
 /*   //avec le numéro obtenu, obtenir la vue et la position (x, y)
    QString req;
    req = "SELECT A1.num_lieu, A2.num_vue ";
    req += "FROM lecteur A1, representationLieuSurVue A2 ";
    req += "WHERE A1.num_lieu = A2.num_lieu AND A1.num_lecteur=:numLecteur";
    query->prepare(req);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL vue/position lecteur" << endl;
    }

    int num_vue;

    while(query->next()){
        num_vue = query->value(1).toInt();

        //suppresion d'un lecteur (en dynamique)
        suppLecteur(numLecteur, num_vue);
    }*/
}
