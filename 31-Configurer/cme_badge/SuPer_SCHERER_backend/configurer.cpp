#include "configurer.h"
#include "ui_configurer.h"

Configurer::Configurer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configurer)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->tBoxLier->setCurrentIndex(0);
    pBdd = new Bdd;

    //onglet affecter/désaffecter
    //init personne à lier

    //récupération des infos
    pBdd->getPersonneLier(&listePersonne);

    if(!listePersonne.empty()){
        for(int i = 0; i < listePersonne.count(); i++) {
            QString nom = listePersonne.at(i).nom;

            //ajout du combo
            ui->cBoxPersonneLier->addItem(nom);

        }
    }
    //init badge non actif
    //récupération des infos
    pBdd->getBadgeNonActif(&listeBadge);

    if(!listeBadge.empty()){
        for(int i = 0; i < listeBadge.count(); i++) {
            int num_badge = listeBadge.at(i).numBadge;
            QString dateMiseEnService = listeBadge.at(i).dateMiseEnService;
            QString dateChangePile = listeBadge.at(i).dateChangePile;
            QString nom = listeBadge.at(i).nom;
            QString prenom = listeBadge.at(i).prenom;
            QString societe = listeBadge.at(i).societe;
            QString dateDebut = listeBadge.at(i).dateDebut;
            QString dateFin = listeBadge.at(i).dateFin;

            //ajout du combo
            ui->cBoxLierMod->addItem(nom);

        }
    }

}


Configurer::~Configurer()
{
    delete pBdd;
    delete ui;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////////////////////////
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
/////////
//SLOT comboBox Lier Personne
void Configurer::on_cBoxPersonneLier_activated(int index)
{

    QString nom = listePersonne.at(index).nom;
    QString prenom = listePersonne.at(index).prenom;
    QString societe = listePersonne.at(index).societe;
    QString dateDebut = listePersonne.at(index).dateDebut;
    QString dateFin = listePersonne.at(index).dateFin;

    //ajout info txtInfoPersonne
    //selon la personne (d'où le slot)
    ui->txtInfoPersonne->clear();
    ui->txtInfoPersonne->textCursor().insertText(nom+" "+prenom+" de la societe "+societe+". Date d'intervention : "+dateDebut+" "+dateFin);

}
////////
//SLOT bouton de confirmation
void Configurer::on_btOkLier_clicked()
{

    //récupération des informations dans les champs
    QString numBadge = ui->lEditNumBadgeLier->text();
    QString dateService = ui->lEditDateServiceLier->text();
    QString datePile = ui->lEditDatePileLier->text();
    QString personne = ui->cBoxPersonneLier->currentText();

    //obtenir le numéro de la personne
    int numPersonne = pBdd->getNumPersonne(personne);

    if(numPersonne == -1){  //Problème
        QMessageBox::warning(0, tr("Attention : erreur"),
                     tr("Impossible de trouver cette personne.\nVerifier les champs.\nErreur 001."),
                              QMessageBox::Ok);
    }

    //requête
    bool lier = pBdd->setLier(numPersonne, numBadge, dateService, datePile);

    if(!lier){
        //erreur
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                     tr("Impossible de lier cette personne a ce badge.\nVerifier les champs.\nErreur 002."),
                              QMessageBox::Ok);
    }else{
        //ok
        QMessageBox::information(0, tr("Lier un Badge a une Personne"),
                     tr("Operation reussie.\n"),
                              QMessageBox::Ok);
        this->on_btAnnulerLier_clicked();

        //supprimer combo
        int indexEnCours = ui->cBoxPersonneLier->currentIndex();
        ui->cBoxPersonneLier->removeItem(indexEnCours);

        //nettoyer QList
        listePersonne.clear();

        //init personne à lier
        //récupération des infos
        pBdd->getPersonneLier(&listePersonne);

        if(!listePersonne.empty()){
            for(int i = 0; i < listePersonne.count(); i++) {
                QString nom = listePersonne.at(i).nom;

                //ajout du combo
                ui->cBoxPersonneLier->addItem(nom);

            }
        }
    }
}
//////////
//SLOT ComboBox modification
void Configurer::on_cBoxLierMod_activated(int index)
{
    int num_badge = listeBadge.at(index).numBadge;
    QString dateMiseEnService = listeBadge.at(index).dateMiseEnService;
    QString dateChangePile = listeBadge.at(index).dateChangePile;
    QString nom = listeBadge.at(index).nom;
    QString prenom = listeBadge.at(index).prenom;
    QString societe = listeBadge.at(index).societe;
    QString dateDebut = listeBadge.at(index).dateDebut;
    QString dateFin = listeBadge.at(index).dateFin;

    //ajout info txtInfoPersonne
    //selon la personne (d'où le slot)
    ui->txtInfoBadgeLier->clear();
    ui->txtInfoBadgeLier->textCursor().insertText(nom+" "+prenom+" de la societe "+societe+". Date d'intervention : "+dateDebut+" "+dateFin+ " Date de mise en service : "+dateMiseEnService+" Date de changement Pile : "+dateChangePile);

    //autre champs
    ui->lEditNumBadgeMod->clear();
    ui->lEditNumBadgeMod->insert(nom);
    ui->lEditDateServiceMod->clear();
   // ui->lEditDateServiceMod->insertText(dateMiseEnService);
}
