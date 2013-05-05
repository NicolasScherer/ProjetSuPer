#include "configurer.h"
#include "ui_configurer.h"

Configurer::Configurer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configurer)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
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
    //déclaration QList
    QList<T_Log> listeLog;

    //supprimer ce qu'il pourrait y avoir à l'écran
    ui->txtLog->clear();

    //récupération de l'historique des événements
    if(!pBdd->getLog(&listeLog)){
        ui->txtLog->insertHtml("<b>L'historique est vide !</b>");
    }

    if(!listeLog.empty()){
        //parcours de la liste
        for(int i =0; i < listeLog.count(); i++){
            QString date_log = listeLog.at(i).date;
            QString legende = listeLog.at(i).legende;
            QString nom = listeLog.at(i).nom;
            QString prenom = listeLog.at(i).prenom;
            QString societe = listeLog.at(i).societe;
            //ajout sur textedit
            ui->txtLog->textCursor().insertHtml("<b>" +date_log+ "</b>" + " | " + "<font color='red'>"+ legende + "</font>" +  " ||nom: " + nom + " ||prenom: "+ prenom + " ||societe: " + societe +"<br>");
        }
    }
}

//onglet Historique des événements
//supprimer historique des événements
void Configurer::on_btSuppLog_clicked()
{
    int clic = QMessageBox::warning(0, tr("Attention : suppression des donnees"),
             tr("Etes vous sur de vouloir supprimer l'historique ?\n"),
                      QMessageBox::Ok ,QMessageBox::Cancel);

    if(clic == QMessageBox::Ok){
        //requete de suppression
         if(!pBdd->removeLog()){
             ui->txtLog->clear();
             ui->txtLog->insertHtml("<b> <ERREUR> Impossible de supprimer l'historique </b>");
         }else{
             ui->txtLog->clear();
             ui->txtLog->insertHtml("<b> Operation reussie ! </b>");
        }
    }
}
//onglet Affecter/désaffecter badge
//Boutons annuler
void Configurer::on_btAnnulerLier_clicked()
{
    //nettoyer et remettre par défaut
    ui->lEditNumBadgeLier->clear();
    ui->lEditDateServiceLier->clear();
    ui->lEditDatePileLier->clear();
    ui->txtBadgeExistant->clear();
    ui->txtInfoPersonne->clear();
    ui->cBoxPersonneLier->setCurrentIndex(0);
}
void Configurer::on_btAnnulerLierMod_clicked()
{
    //nettoyer et remettre par défaut
    ui->txtInfoBadgeLier->clear();
    ui->lEditNumBadgeMod->clear();
    ui->lEditDateServiceMod->clear();
    ui->lEditDatePileMod->clear();
    ui->txtBadgeExistantMod->clear();
    ui->cBoxLierMod->setCurrentIndex(0);
}
void Configurer::on_btAnnulerDelier_clicked()
{
    //nettoyer et remettre par défaut
    ui->txtInfoBadgeDelier->clear();
    ui->txtInfoPersonneDelier->clear();
    ui->cBoxBadgeSupp->setCurrentIndex(0);
}

//bouton badge existant
void Configurer::on_btBadgeExistant_clicked()
{
    //initialisation
    ui->txtBadgeExistant->clear();

    QString badgeExistant;

    bool retour = pBdd->getBadgeExistant(&badgeExistant);
    if (retour == false)
        ui->txtBadgeExistant->textCursor().insertText("Aucun badge.");

    ui->txtBadgeExistant->textCursor().insertText(badgeExistant);

}
