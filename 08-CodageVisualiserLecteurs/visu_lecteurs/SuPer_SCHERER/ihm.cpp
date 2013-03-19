#include "ihm.h"
#include "onglet.h"
#include "ui_ihm.h"
#include "contenuonglet.h"
#include <QtSql>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

//////////////////////
/*** CONSTRUCTEUR ***/
Ihm::Ihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ihm)
{
    ui->setupUi(this);
    pLecteur = new Lecteur;
    pOnglet = new Onglet;

//*** signaux
    // Bouton btNewLecteur
    //connect(ui->btNewLecteur, SIGNAL(clicked()), this, SLOT(lecteurActif(pLecteur)));

    //connect
 //   connect(this, SIGNAL(signalNewLecteur(const Lecteur &)), this, SLOT(lecteurActif(const Lecteur &)));
  //  connect(this, SIGNAL(signalDelLecteur(pLecteur)), this, SLOT(lecteurInactif(pLecteur)));
    //émission signal
  // emit signalNewLecteur(pLecteur);

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

    int vueMax = getVueMax();
    //requête
    if(!query->exec("SELECT * FROM vue")){
        qDebug() << "Erreur requete SQL" << endl << database.lastError() << endl;
        //test si problème lors de l'envoi de la requete
    }

    //ajout autant d'onglet que de vue
    while(query->next()){
        int num_vue = query->value(0).toInt();
        QString legende = query->value(1).toString();
        QString image = query->value(2).toString();

        if(num_vue <= vueMax){
            ajoutOnglet(num_vue, legende, image);
        }
    }

    //supprimer les deux onglets de base
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(vueMax);

    lecteurActif(pLecteur);

     // setWindowFlags(Qt::FramelessWindowHint);    //fenêtre sans bordure

}
/////////////////////
/*** DESTRUCTEUR ***/
Ihm::~Ihm()
{
    delete pLecteur;
    delete query;

    // PENSER A DETRUIRE LES ONGLETS

    delete ui;
}
////////////////////////////
/*** SLOT LECTEUR ACTIF ***/
void Ihm::lecteurActif(Lecteur *pLecteur){

    //obtenir le numéro de lecteur grâce à la classe Lecteur
  //  int numLecteur = pLecteur->getnum_lecteur();
    int numLecteur = 1;

    //avec le numéro obtenu, obtenir la vue et la position (x, y)
    QString req;
    req = "SELECT A1.num_lieu, A2.num_vue, A2.x, A2.y ";
    req += "FROM lecteur A1, representationLieuSurVue A2 ";
    req += "WHERE A1.num_lieu = A2.num_lieu AND A1.num_lecteur=:numLecteur";
    query->prepare(req);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL vue/position lecteur" << endl;
    }

    int num_vue, x, y;

    while(query->next()){
        num_vue = query->value(1).toInt();
        x = query->value(2).toInt();
        y = query->value(3).toInt();

        //ajout d'un lecteur (en dynamique)
        ajoutLecteur(numLecteur, num_vue, x, y);
    }

}
///////////////////////////////
/*** méthode AJOUT LECTEUR ***/
void Ihm::ajoutLecteur(int numLecteur, int num_vue, int x, int y){

    //liste onglet récupération du pointeur onglet
    if( pOnglet->num_vue[num_vue] == num_vue ){

        QWidget *onglet;
        onglet = pOnglet->onglet[num_vue];

        qDebug() << "valeur pointeur onglet" << onglet << endl;

        //QWidget *onglet;


       // QLabel *labelL = new QLabel(onglet);
       // labelL->setPixmap(QPixmap("../ressources/lecteur_actif_petit.jpg"));
       // labelL->setGeometry(x, y, 15, 42); // largeur hauteur à définir

        //QTabWidget *onglet;
        //onglet = pOnglet->onglet[num_vue];
       // qDebug() << "valeur dans l onglet" << onglet << endl;
        // QWidget *onglet = new QTabWidget(this);
      //  onglet = pOnglet->onglet[num_vue];

        //nouveau label dynamique pour mettre l'image correspondant
   //     QLabel *labelL = new QLabel(onglet);
     //   labelL->setPixmap(QPixmap("../ressources/lecteur_actif_petit.jpg"));
       // labelL->setGeometry(x, y, 15, 42); // largeur hauteur à définir

    //    QVBoxLayout *layout = new QVBoxLayout;
      //  layout = pOnglet->layout[num_vue];

        //lier le label au layout dynamique
        //layout->addWidget(labelL);

        //ajouter le layout au widget (l'onglet)
        //onglet->setLayout(layout);
    }

/*    //onglet dynamique sur la bonne vue
    QWidget *onglet = new QTabWidget(this);
    int vueCourant = num_vue-1;
    ui->tabWidget->setCurrentIndex(vueCourant);

    //nouveau label dynamique pour mettre l'image correspondant
    QLabel *labelL = new QLabel;
    labelL->setPixmap(QPixmap("/home/scherer/Projet/08-CodageVisualiserLecteurs/visu_lecteurs/ressources/cv.jpg"));
    labelL->setGeometry(x, y, 300, 100); // largeur hauteur à définir

    //sauvegarde du pointeur label lecteur
//    tll->label = labelL;
    //lier le label au layout dynamique
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(labelL);

    //ajouter le layout au widget (l'onglet)
    onglet->setLayout(layout);
*/
}
//////////////////////////////
/*** méthode AJOUT ONGLET ***/
void Ihm::ajoutOnglet(int num_vue, QString legende, QString image)
{
    //sauvegarde du numéro de l'onglet (donc de la vue)
    pOnglet->num_vue[num_vue] = num_vue;

    //nouveau onglet dynamique avec légende
    ContenuOnglet *pContenuOnglet = new ContenuOnglet(0, image);
    ui->tabWidget->insertTab(num_vue, pContenuOnglet, legende);

    //sauvegarde du pointeur onglet
    pOnglet->onglet[num_vue] = pContenuOnglet;
    qDebug() << "valeur dans la classe" << pOnglet->onglet[num_vue] << endl;

}
////////////////////////////////
/*** méthode obtenir VUE MAX **/
int Ihm::getVueMax()
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
/////////////////////////////
/*** SLOT bouton Quitter ***/
void Ihm::on_btQuitter_clicked()
{
    this->~Ihm();
}
