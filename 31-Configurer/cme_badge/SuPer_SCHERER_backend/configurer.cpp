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

 /*   //mettre 5 colonnes
  //  ui->tableWidget->setColumnCount(5);

    ui->tableWidget = new QTableWidget(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(5);

    QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(
           (10+1)*(5+1)));

    newItem->setText("X");
       ui->tableWidget->setItem(10, 5, newItem);


    QTableWidgetItem *itab = new QTableWidgetItem;
    itab->setText("X");
    ui->tableWidget->setItem(0, 0, itab);
*/
    //déclaration QList
    QList<T_Log> listeLog;

    //récupération de l'historique des événements
    pBdd->getLog(&listeLog);

    if(!listeLog.empty()){
        //parcours de la liste
        for(int i =0; i < listeLog.count(); i++){
                QString date_log = listeLog.at(i).date;
                QString legende = listeLog.at(i).legende;
                QString nom = listeLog.at(i).nom;
                QString prenom = listeLog.at(i).prenom;
                QString societe = listeLog.at(i).societe;

                int p=0;
                while(p<50){
                ui->txtLog->textCursor().insertHtml("<b>" +date_log+ "</b>" + " | " + "<font color='red'>"+ legende + "</font>" +  " ||nom: " + nom + " ||prenom: "+ prenom + " ||societe: " + societe +"\n");
                p++;
                }

        }
    }
}





