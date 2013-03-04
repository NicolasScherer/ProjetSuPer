#include "ihm.h"
#include "ui_ihm.h"
#include <QtSql>
#include <QString>
#include <QtDebug>
#include <QMessageBox>



Ihm::Ihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ihm)
{

    ui->setupUi(this);


    //accès BDD
    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setDatabaseName("bdd_super");
    database.setUserName("user_super");
    database.setPassword("mdp_super");
    bool ok = database.open();
    if (!ok)
        qDebug() << database.lastError();

    QSqlQuery query;

    //requête nombre de vue
    if(!query.exec("SELECT COUNT( * ) FROM vue")){
        qDebug() << "Erreur requete SQL" << endl << database.lastError() << endl;
        //test si problème lors de l'envoi de la requete
    }

    //ajout autant d'onglet que de vue
    while(query.next()){
        int id_rubrique = query.value(0).toInt();

        while(id_rubrique > 0){
            ajoutOnglet(id_rubrique);
/*
            //requête légende pour la vue
             if(!query.exec("SELECT legende FROM vue WHERE num_vue = 'id_rubrique'")){
                qDebug() << "Erreur requete SQL" << endl << database.lastError() << endl;
                //test si problème lors de l'envoi de la requete
             }

                QString libelle_rubrique = query.value(0).toString();
              // legendeOnglet();
*/
            id_rubrique--;
        }
    }

    //supprimer les deux onglets de base
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(0);

}

Ihm::~Ihm()
{
    delete ui;
}

void Ihm::ajoutOnglet(int id_rubrique)
{
    QWidget *ajout = new QTabWidget(this);
    char* legende;
    sprintf(legende, "%d", id_rubrique);
    ui->tabWidget->addTab(ajout,legende);



}
void Ihm::legendeOnglet()
{

}

