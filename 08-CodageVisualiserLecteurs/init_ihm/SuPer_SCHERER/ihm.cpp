#include "ihm.h"
#include "ui_ihm.h"
#include <QtSql>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>


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

}

Ihm::~Ihm()
{
    delete query;
    delete ui;
}

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

void Ihm::lecteurActif(int num_lecteur){

}

void Ihm::lecteurInactif(int num_lecteur){

}

void Ihm::lecteurInconnu(){

}
