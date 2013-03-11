#include "ihm.h"
#include "ui_ihm.h"
#include <QtSql>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

    Lecteur *pLecteur = new Lecteur;

/*** CONSTRUCTEUR ***/
Ihm::Ihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ihm)
{
    ui->setupUi(this);

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

    // Bouton btNewLecteur
   // connect(ui->btNewLecteur, SIGNAL(clicked()), this, SLOT(tpNewLecteur()));


    //connect
    connect(this, SIGNAL(signalNewLecteur(pLecteur)), this, SLOT(lecteurActif(pLecteur)));
    //émission signal
    emit signalNewLecteur(pLecteur);
}

/*** DESTRUCTEUR ***/
Ihm::~Ihm()
{
    delete pLecteur;
    delete query;
    delete ui;
}

/*** SLOT LECTEUR ACTIF ***/
void Ihm::lecteurActif(Lecteur *pLecteur){

    //obtenir le numéro de lecteur grâce à la classe Lecteur
    int num_lecteur = pLecteur->getnum_lecteur();

    //avec le numéro obtenu, obtenir la vue et la position (x, y)
//****ATTENTION le num_lecteur est égal à 1 dans la requete SQL (à modifier)
    if(!query->exec("SELECT A1.num_lieu, A2.num_vue, A2.x, A2.y FROM lecteur A1, representationLieuSurVue A2 WHERE A1.num_lieu = A2.num_lieu AND A1.num_lecteur =1")){
        qDebug() << "Erreur requete SQL getNumLieu" << endl;
    }

    int num_vue;
    int x;
    int y;
    while(query->next()){
        num_vue = query->value(1).toInt();
        x = query->value(2).toInt();
        y = query->value(3).toInt();

        //ajout d'un lecteur (en dynamique)
        ajoutLecteur(num_vue, x, y);
    }

}

/*** méthode AJOUT LECTEUR ***/
void Ihm::ajoutLecteur(int num_vue, int x, int y){
    //onglet dynamique sur la bonne vue
    QWidget *onglet = new QTabWidget(this);
    ui->tabWidget->setCurrentIndex(num_vue);

    //nouveau label dynamique pour mettre l'image correspondant
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(/*image antenne à mettre*/));
    label->setGeometry(x, y, 50, 50); //50 50 largeur hauteur à définir

    //lier le label au layout dynamique
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    //ajouter le layout au widget (l'onglet)
    onglet->setLayout(layout);
}

/*** méthode AJOUT ONGLET ***/
void Ihm::ajoutOnglet(int num_vue, QString legende, QString image)
{
    //nouveau onglet dynamique avec légende
    QWidget *ajout = new QTabWidget(this);
    ui->tabWidget->insertTab(num_vue, ajout, legende);

    //nouveau label dynamique pour mettre l'image correspondant
    QLabel *label = new QLabel;
    label->setPixmap(QPixmap(image));

    //lier le label au layout dynamique
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);

    //ajouter le layout au widget (l'onglet)
    ajout->setLayout(layout);
}

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
