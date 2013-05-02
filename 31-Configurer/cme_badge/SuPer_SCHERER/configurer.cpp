#include "configurer.h"
#include "ui_configurer.h"

Configurer::Configurer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configurer)
{
    ui->setupUi(this);
    pBdd = new Bdd;
}

Configurer::~Configurer()
{
    delete pBdd;
    delete ui;
}

//onglet Historique des événements
//afficher historique des événements

void Configurer::on_btAffLog_clicked()
{

    ui->tableWidget->setColumnCount(5);


}

/*    //déclaration QList
    QList<T_Log> listeLog;

    //récupération de l'historique des événements
    pBdd->getLog(&listeLog);

    if(!listeLog.empty()){
        for(int i =0; i < listeLog.count(); i++)

            //for parcours colonne
        ui->tableView->


    }

    if(!listeTupleO.empty()){
        for(int i = 0; i < listeTupleO.count() && i < vueMax; i++) {
            int num_vue = listeTupleO.at(i).num_vue;
            QString legende = listeTupleO.at(i).legende;
            QString image = listeTupleO.at(i).image;
            //ajout de l'onglet
            this->ajoutOnglet(num_vue, legende, image);
        }
    }
*/

