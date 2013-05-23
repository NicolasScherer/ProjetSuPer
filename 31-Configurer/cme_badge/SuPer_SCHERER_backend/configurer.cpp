#include "configurer.h"
#include "ui_configurer.h"

Configurer::Configurer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Configurer)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    ui->tBoxLier->setCurrentIndex(0);
    ui->tBoxConfigSuper->setCurrentIndex(0);
    pBdd = new Bdd;
    this->actuAffichage();      //actualise l'affichage
    this->etatPosition = -1;    //valeur par défaut
}


Configurer::~Configurer()
{
    delete pBdd;
    delete ui;
}
/////////////////////////////////////////////////////////////////////////////////////
//méthode permettant l'actualisation de l'affichage
bool Configurer::actuAffichage(){

    //nettoyer champs
    ui->txtInfoPersonne->clear();
    ui->txtInfoBadgeLier->clear();
    ui->txtInfoBadgeDelier->clear();
    ui->txtInfoPersonneDelier->clear();

    //nettoyer QList
    listePersonne.clear();
    listeBadge.clear();

    ///////////////////////////////////////////////////////////////////////////////////
    //onglet affecter/désaffecter
    //init personne à lier

    //nettoyer combobox
    ui->cBoxPersonneLier->clear();
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
    //nettoyer combobox
    ui->cBoxLierMod->clear();
    ui->cBoxBadgeSupp->clear();

    //récupération des infos
    pBdd->getBadgeNonActif(&listeBadge);

    if(!listeBadge.empty()){
        for(int i = 0; i < listeBadge.count(); i++) {
            QString nom = listeBadge.at(i).nom;

            //ajout du combo
            ui->cBoxLierMod->addItem(nom);
            ui->cBoxBadgeSupp->addItem(nom);

        }
    }

    ///////////////////////////////////////////////////////////////////
    //onglet gestion des vues (config SuPer)

    //nettoyer QList
    listeVue.clear();

    //init vue existante
    //nettoyer comboBox
    ui->cBoxVueMod->clear();
    ui->cBoxVueSupp->clear();
    ui->cBoxPositionNumVue->clear();
    ui->cBoxPositionSuppNumVue->clear();

    //récupération des infos
    pBdd->getVueExistant(&listeVue);

    if(!listeVue.empty()){
        for(int i = 0; i < listeVue.count(); i++){
            QString numVue = listeVue.at(i).numVue;
            QString legende = listeVue.at(i).legende;

            //ajout du combo
            ui->cBoxVueMod->addItem(legende);
            ui->cBoxVueSupp->addItem(legende);
            ui->cBoxPositionNumVue->addItem(numVue);
            ui->cBoxPositionSuppNumVue->addItem(numVue);
        }
    }

    ///////////////////////////////////////////////////////////////////
    //onglet gestion des lieux (config SuPer)
    //nettoyer QList
    listeLieu.clear();

    //init lieu existant
    //nettoyer comboBox
    ui->cBoxLieuMod->clear();
    ui->cBoxLieuSupp->clear();
    ui->cBoxLieuLier->clear();
    ui->cBoxZoneLieuMod->clear();

    //récupération des infos
    pBdd->getLieuExistant(&listeLieu);

    if(!listeLieu.empty()){
        for(int i = 0; i < listeLieu.count(); i++){
            QString numLieu = listeLieu.at(i).numLieu;
            QString legende = listeLieu.at(i).legende;

            //ajout du combo
            ui->cBoxLieuMod->addItem(legende);
            ui->cBoxLieuSupp->addItem(legende);
            ui->cBoxLieuLier->addItem(legende); //onglet ajouter zone
            ui->cBoxZoneLieuMod->addItem(numLieu);  //onglet modifier zone
        }
    }

    ///////////////////////////////////////////////////////////////////////
    //onglet gestion des zones (config SuPer)
    //nettoyer QList
    listeZone.clear();

    //init lieu existant
    //nettoyer comboBox
    ui->cBoxZoneMod->clear();
    ui->cBoxZoneSupp->clear();
    ui->cBoxPositionNumZone->clear();

    //récupération des infos
    pBdd->getZoneExistant(&listeZone);

    if(!listeZone.empty()){
        for(int i = 0; i < listeZone.count(); i++){
            QString numZone = listeZone.at(i).numZone;

            //ajout du combo
            ui->cBoxZoneMod->addItem(numZone);
            ui->cBoxZoneSupp->addItem(numZone);
            ui->cBoxPositionNumZone->addItem(numZone);
        }
    }

    /////////////////////////////////////////////////////////////////////////
    //onglet gestion des timers (config SuPer)

    //nettoyer champs
    ui->lEditTimerMouv->clear();
    ui->lEditTimerRecep->clear();

    //récupération des infos
    int tempoMouv; // ms tempo pour le timer mouvement
    int tempoRec; // ms tempo pour le timer de réception
    pBdd->getTempo(&tempoMouv, &tempoRec);

    //int to string
    QString tempoMouv_q = QString::number(tempoMouv);
    QString tempoRec_q = QString::number(tempoRec);

    //ajout des champs
    ui->lEditTimerMouv->insert(tempoMouv_q);
    ui->lEditTimerRecep->insert(tempoRec_q);

    //++--++--++//
    return true;
}

/////////////////////////////////////////////////////////////////////////////////////
//bouton actualisation affichage
void Configurer::on_btAffichage_clicked()
{
    bool affichageOk = this->actuAffichage();

    if(affichageOk == true){
        QMessageBox::information(0, tr("Actualiser Affichage"),
                     tr("Interface Actualisee avec succes.\n"),
                              QMessageBox::Ok);
    }else{
        QMessageBox::information(0, tr("Actualiser Affichage"),
                     tr("Erreur : Interface non Actualisee.\n"),
                              QMessageBox::Ok);
    }
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
             tr("Etes vous sur de vouloir supprimer l'Historique ?\n"),
                      QMessageBox::Ok ,QMessageBox::Cancel);

    if(clic == QMessageBox::Ok){
        //requete de suppression
         if(!pBdd->removeLog()){
             ui->txtLog->clear();
             ui->txtLog->insertHtml("<b> <ERREUR> Impossible de supprimer l'Historique </b>");
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
    ui->txtBadgeExistant_2->clear();
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
void Configurer::on_btBadgeExistant_2_clicked()
{
    //initialisation
    ui->txtBadgeExistant_2->clear();

    QString badgeExistant;

    bool retour = pBdd->getBadgeExistant(&badgeExistant);
    if (retour == false)
        ui->txtBadgeExistant_2->textCursor().insertText("Aucun badge.");

    ui->txtBadgeExistant_2->textCursor().insertText(badgeExistant);
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
        this->actuAffichage();
    }
}
//////////
//SLOT ComboBox modification
void Configurer::on_cBoxLierMod_activated(int index)
{
    QString num_badge = listeBadge.at(index).numBadge;
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
    ui->lEditNumBadgeMod->insert(num_badge);
    ui->lEditDateServiceMod->clear();
    ui->lEditDateServiceMod->insert(dateMiseEnService);
    ui->lEditDatePileMod->clear();
    ui->lEditDatePileMod->insert(dateChangePile);
}
////////
//SLOT bouton de confirmation Modification
void Configurer::on_btOkLierMod_clicked()
{
    //récupération des informations dans les champs
    QString numBadge = ui->lEditNumBadgeMod->text();
    QString dateService = ui->lEditDateServiceMod->text();
    QString datePile = ui->lEditDatePileMod->text();
    QString personne = ui->cBoxLierMod->currentText();

    //obtenir le numéro de la personne
    int numPersonne = pBdd->getNumPersonne(personne);

    if(numPersonne == -1){  //Problème
        QMessageBox::warning(0, tr("Attention : erreur"),
                     tr("Impossible de trouver cette personne.\nVerifier les champs.\nErreur 001b."),
                              QMessageBox::Ok);
    }

    //requête
    bool modif = pBdd->addModLier(numPersonne, numBadge, dateService, datePile);

    if(!modif){
        //erreur
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible d'apporter modification a ce badge.\nVerifier les champs.\nErreur 002b."),
                              QMessageBox::Ok);
    }else{
        //ok
        QMessageBox::information(0, tr("Modification affecter un Badge a une Personne"),
                     tr("Operation reussie.\n"),
                              QMessageBox::Ok);
        this->on_btAnnulerLierMod_clicked();
        this->actuAffichage();
    }
}
//////////
//SLOT ComboBox suppression
void Configurer::on_cBoxBadgeSupp_activated(int index)
{
    QString num_badge = listeBadge.at(index).numBadge;
    QString dateMiseEnService = listeBadge.at(index).dateMiseEnService;
    QString dateChangePile = listeBadge.at(index).dateChangePile;
    QString nom = listeBadge.at(index).nom;
    QString prenom = listeBadge.at(index).prenom;
    QString societe = listeBadge.at(index).societe;
    QString dateDebut = listeBadge.at(index).dateDebut;
    QString dateFin = listeBadge.at(index).dateFin;

    //ajout info txtBadgeDelier
    ui->txtInfoBadgeDelier->clear();
    ui->txtInfoBadgeDelier->textCursor().insertText("Numero de Badge : "+num_badge+". Date de mise en service : "+dateMiseEnService+". Date de changement Pile : "+dateChangePile);
    //ajout info txtInfoPersDelier
    ui->txtInfoPersonneDelier->clear();
    ui->txtInfoPersonneDelier->textCursor().insertText(nom+" "+prenom+" de la societe "+societe+". Date d'intervention : "+dateDebut+" "+dateFin);


    //autre champs
    ui->lEditNumBadgeMod->clear();
    ui->lEditNumBadgeMod->insert(num_badge);
    ui->lEditDateServiceMod->clear();
    ui->lEditDateServiceMod->insert(dateMiseEnService);
    ui->lEditDatePileMod->clear();
    ui->lEditDatePileMod->insert(dateChangePile);
}
////////
//SLOT bouton de confirmation Suppresion
void Configurer::on_btOkDelier_clicked()
{
    //récupération des informations dans les champs
    QString personne = ui->cBoxBadgeSupp->currentText();

    //obtenir le numéro de la personne
    int numPersonne = pBdd->getNumPersonne(personne);

    if(numPersonne == -1){  //Problème
        QMessageBox::warning(0, tr("Attention : erreur"),
                     tr("Impossible de trouver cette personne.\nVerifier les champs.\nErreur 001c."),
                              QMessageBox::Ok);
    }

    //requête
    bool supp = pBdd->setDelier(numPersonne);

    if(!supp){
        //erreur
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de supprimer ce badge.\nVerifier les champs.\nErreur 002c."),
                              QMessageBox::Ok);
    }else{
        //ok
        QMessageBox::information(0, tr("Desaffecter un Badge a une Personne"),
                     tr("Operation reussie.\n"),
                              QMessageBox::Ok);
        this->on_btAnnulerLierMod_clicked();
        this->actuAffichage();
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ONGLET Configurer super / GESTION DES VUES
//Boutons annulés

void Configurer::on_btAnnulerVueAdd_clicked()
{
    //remise à zéro
    ui->lEditNumVueAdd->clear();
    ui->txtVueExiste->clear();
    ui->txtVueLegendeAdd->clear();
    ui->txtVueImageAdd->clear();
}

void Configurer::on_btAnnulerVueMod_clicked()
{
    ui->cBoxVueMod->setCurrentIndex(0);
    ui->lEditNumVueMod->clear();
    ui->txtVueLegendeMod->clear();
    ui->txtVueImageMod->clear();
}

void Configurer::on_btannulerVueSupp_clicked()
{
    ui->cBoxVueSupp->setCurrentIndex(0);
    ui->lEditNumVueSupp->clear();
    ui->txtVueLegendeSupp->clear();
    ui->txtVueImageSupp->clear();
}
//++++++++++
//obtenir vue existante
void Configurer::on_btVueExistante_clicked()
{
    //nettoyer vue
    listeVue.clear();

    //initialisation
    ui->txtVueExiste->clear();

    //récupération des infos
    pBdd->getVueExistant(&listeVue);

    if(!listeVue.empty()){
        for(int i = 0; i < listeVue.count(); i++){
            QString numVue = listeVue.at(i).numVue;
          //  QString legende = listeVue.at(i).legende;
          //  QString image = listeVue.at(i).image;

            //création chaine et affichage
            QString vueExistant = numVue + " ; ";
            ui->txtVueExiste->textCursor().insertText(vueExistant);
        }
    }else{
        ui->txtVueExiste->textCursor().insertText("Aucune Vue.");
    }
}
//++++++++++
//ajouter vue
void Configurer::on_btOkVueAdd_clicked()
{
    //récupération des informations dans les champs
    QString numVue = ui->lEditNumVueAdd->text();
    QString legende = ui->txtVueLegendeAdd->toPlainText();
    QString image = ui->txtVueImageAdd->toPlainText();

    //requête
    bool addVue = pBdd->setVue(numVue, legende, image);

    if(!addVue){
        //erreur
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible d'ajouter cette vue.\nVerifier les champs.\nErreur 004."),
                              QMessageBox::Ok);
    }else{
        //ok
        QMessageBox::information(0, tr("Ajouter une Vue"),
                     tr("Operation reussie.\n"),
                              QMessageBox::Ok);
        this->on_btAnnulerVueAdd_clicked();
        this->actuAffichage();
    }
}
//++++++++++
//SLOT combobox vue mod
void Configurer::on_cBoxVueMod_activated(int index)
{
    QString numVue = listeVue.at(index).numVue;
    QString legende = listeVue.at(index).legende;
    QString image = listeVue.at(index).image;

    //ajout champs
    ui->lEditNumVueMod->clear();
    ui->lEditNumVueMod->insert(numVue);
    ui->txtVueLegendeMod->clear();
    ui->txtVueLegendeMod->textCursor().insertText(legende);
    ui->txtVueImageMod->clear();
    ui->txtVueImageMod->textCursor().insertText(image);

}
//++++++++++
//SLOT bouton ok modifier vue
void Configurer::on_btOkVueMod_clicked()
{
    //récupération des informations dans les champs
    QString legendeActuelle = ui->cBoxVueMod->currentText();
    QString numVue = ui->lEditNumVueMod->text();
    QString legende = ui->txtVueLegendeMod->toPlainText();
    QString image = ui->txtVueImageMod->toPlainText();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numVue == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de modifier cette Vue.\nLes champs sont vides.\nErreur 020."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool modVue = pBdd->addModVue(legendeActuelle, numVue, legende, image);

        if(!modVue){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de modifier cette vue.\nVerifier les champs.\nErreur 005."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Modifier une Vue"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerVueMod_clicked();
            this->actuAffichage();
        }
    }
}
//++++++++++
//SLOT combobox supp vue
void Configurer::on_cBoxVueSupp_activated(int index)
{
    QString numVue = listeVue.at(index).numVue;
    QString legende = listeVue.at(index).legende;
    QString image = listeVue.at(index).image;

    //ajout champs
    ui->lEditNumVueSupp->clear();
    ui->lEditNumVueSupp->insert(numVue);
    ui->txtVueLegendeSupp->clear();
    ui->txtVueLegendeSupp->textCursor().insertText(legende);
    ui->txtVueImageSupp->clear();
    ui->txtVueImageSupp->textCursor().insertText(image);
}
//++++++++++
//SLOT bouton ok supprimer vue
void Configurer::on_btOKVueSupp_clicked()
{
    //récupération des informations dans les champs
    QString numVue = ui->lEditNumVueSupp->text();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numVue == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de supprimer cette vue.\nLes champs sont vides.\nErreur 021."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool supp = pBdd->setSuppVue(numVue);

        if(!supp){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de supprimer cette vue.\nVerifier les champs.\nErreur 006."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Supprimer une vue"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btannulerVueSupp_clicked();
            this->actuAffichage();
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//onglet GESTION DES LIEUX
//Boutons annulés

void Configurer::on_btAnnulerLieuAdd_clicked()
{
    ui->lEditLieuNumAdd->clear();
    ui->txtLieuExiste->clear();
    ui->txtLieuLegendeAdd->clear();
}

void Configurer::on_btAnnulerLieuMod_clicked()
{
    ui->cBoxLieuMod->setCurrentIndex(0);;
    ui->lEditLieuNumMod->clear();
    ui->txtLieuLegendeMod->clear();
}

void Configurer::on_btAnnulerLieuSupp_clicked()
{
   ui->cBoxLieuSupp->setCurrentIndex(0);
   ui->lEditLieuNumSupp->clear();
   ui->txtLieuLegendeSupp->clear();
}
//++++++++++
//obtenir lieu existant
void Configurer::on_btLieuExistant_clicked()
{
    //nettoyer vue
    listeLieu.clear();

    //initialisation
    ui->txtLieuExiste->clear();

    //récupération des infos
    pBdd->getLieuExistant(&listeLieu);

    if(!listeLieu.empty()){
        for(int i = 0; i < listeLieu.count(); i++){
            QString numLieu = listeLieu.at(i).numLieu;
          //  QString legende = listeVue.at(i).legende;

            //création chaine et affichage
            QString lieuExistant = numLieu + " ; ";
            ui->txtLieuExiste->textCursor().insertText(lieuExistant);
        }
    }else{
        ui->txtLieuExiste->textCursor().insertText("Aucun Lieu.");
    }
}

//++++++++++
//ajouter lieu
void Configurer::on_btOkLieuAdd_clicked()
{
    //récupération des informations dans les champs
    QString numLieu = ui->lEditLieuNumAdd->text();
    QString legende = ui->txtLieuLegendeAdd->toPlainText();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numLieu == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible d'ajouter ce Lieu.\nLes champs sont vides.\nErreur 022."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool addLieu = pBdd->setLieu(numLieu, legende);

        if(!addLieu){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible d'ajouter ce Lieu.\nVerifier les champs.\nErreur 007."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Ajouter un Lieu"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerLieuAdd_clicked();
            this->actuAffichage();
        }
    }
}

//++++++++++
//SLOT combobox lieu mod
void Configurer::on_cBoxLieuMod_activated(int index)
{
    QString numLieu = listeLieu.at(index).numLieu;
    QString legende = listeLieu.at(index).legende;

    //ajout champs
    ui->lEditLieuNumMod->clear();
    ui->lEditLieuNumMod->insert(numLieu);
    ui->txtLieuLegendeMod->clear();
    ui->txtLieuLegendeMod->textCursor().insertText(legende);
}

//++++++++++
//SLOT combobox lieu supp
void Configurer::on_cBoxLieuSupp_activated(int index)
{
    QString numLieu = listeLieu.at(index).numLieu;
    QString legende = listeLieu.at(index).legende;

    //ajout champs
    ui->lEditLieuNumSupp->clear();
    ui->lEditLieuNumSupp->insert(numLieu);
    ui->txtLieuLegendeSupp->clear();
    ui->txtLieuLegendeSupp->textCursor().insertText(legende);
}

//++++++++++
//SLOT bouton ok modifier lieu
void Configurer::on_btOkLieuMod_clicked()
{
    //récupération des informations dans les champs
    QString legendeActuelle = ui->cBoxLieuMod->currentText();
    QString numLieu = ui->lEditLieuNumMod->text();
    QString legende = ui->txtLieuLegendeMod->toPlainText();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numLieu == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de modifier ce Lieu.\nLes champs sont vides.\nErreur 023."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool modLieu = pBdd->addModLieu(legendeActuelle, numLieu, legende);

        if(!modLieu){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de modifier ce Lieu.\nVerifier les champs.\nErreur 008."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Modifier un Lieu"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerLieuMod_clicked();
            this->actuAffichage();
        }
    }
}

//++++++++++
//SLOT bouton ok supprimer lieu
void Configurer::on_btOkLieuSupp_clicked()
{
    //récupération des informations dans les champs
    QString numLieu = ui->lEditLieuNumSupp->text();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numLieu == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de supprimer ce Lieu.\nLes champs sont vides.\nErreur 024."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool supp = pBdd->setSuppLieu(numLieu);

        if(!supp){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de supprimer ce Lieu.\nCe Lieu est probablement lie avec une zone.\nErreur 009."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Supprimer un Lieu"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerLieuSupp_clicked();
            this->actuAffichage();
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ONGLET GESTION des ZONES (config Super)
//boutons annulés

void Configurer::on_btAnnulerZoneAdd_clicked()
{
    ui->lEditNumZoneAdd->clear();
    ui->txtZoneExiste->clear();
    ui->cBoxLieuLier->setCurrentIndex(0);
    ui->lEditZoneSensMonterAdd->clear();
    ui->txtZoneLegendeAdd->clear();
}

void Configurer::on_btAnnulerZoneMod_clicked()
{
    ui->cBoxZoneMod->setCurrentIndex(0);
    ui->lEditNumLieuActuel->clear();
    ui->cBoxZoneLieuMod->setCurrentIndex(0);
    ui->lEditZoneSensMonterMod->clear();
    ui->txtZoneLegendeMod->clear();
}

void Configurer::on_btAnnulerZoneSupp_clicked()
{
    ui->cBoxZoneSupp->setCurrentIndex(0);
    ui->txtZoneLieuSupp->clear();
    ui->lEditZoneSensMonterSupp->clear();
    ui->txtZoneLegendeSupp->clear();
}

//obtenir zones existantes
void Configurer::on_btVueExistante_2_clicked()
{
    //nettoyer vue
    listeZone.clear();

    //initialisation
    ui->txtZoneExiste->clear();

    //récupération des infos
    pBdd->getZoneExistant(&listeZone);

    if(!listeZone.empty()){
        for(int i = 0; i < listeZone.count(); i++){
            QString numZone = listeZone.at(i).numZone;

            //création chaine et affichage
            QString zoneExistant = numZone + " ; ";
            ui->txtZoneExiste->textCursor().insertText(zoneExistant);
        }
    }else{
        ui->txtZoneExiste->textCursor().insertText("Aucune Zone.");
    }
}
//ajouter zone
void Configurer::on_btOkZoneAdd_clicked()
{
    //récupération des informations dans les champs
    QString numZone = ui->lEditNumZoneAdd->text();
    QString legendeLieu = ui->cBoxLieuLier->currentText();
    QString sensMonter = ui->lEditZoneSensMonterAdd->text();
    QString legende = ui->txtZoneLegendeAdd->toPlainText();

    if(sensMonter == ""){
        //évite les enregistrements involontaires
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible d'ajouter cette Zone.\nVerifier les champs.\nErreur 013."),
                              QMessageBox::Ok);
    }
    else{
        //obtenir le numéro de la personne
        int numLieu = pBdd->getNumLieu(legendeLieu);

        if(numLieu == -1){  //Problème
            QMessageBox::warning(0, tr("Attention : erreur"),
                         tr("Impossible de trouver ce Lieu.\nVerifier les champs.\nErreur 010."),
                                  QMessageBox::Ok);
        }
        //requête
        bool addZone = pBdd->setZone(numZone, numLieu, sensMonter, legende);

        if(!addZone){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible d'ajouter cette Zone.\nVerifier les champs.\nErreur 011."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Ajouter une Zone"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerZoneAdd_clicked();
            this->actuAffichage();
        }
    }
}
//SLOT combobox zone mod
void Configurer::on_cBoxZoneMod_activated(int index)
{
    QString numLieuActuel = listeZone.at(index).numLieu;
    QString sensMonter = listeZone.at(index).sensMonter;
    QString legende = listeZone.at(index).legende;

    //ajout champs
    ui->lEditNumLieuActuel->clear();
    ui->lEditNumLieuActuel->insert(numLieuActuel);
    ui->lEditZoneSensMonterMod->clear();
    ui->lEditZoneSensMonterMod->insert(sensMonter);
    ui->txtZoneLegendeMod->clear();
    ui->txtZoneLegendeMod->textCursor().insertText(legende);
}
//SLOT bouton ok zone mod
void Configurer::on_btOkZoneMod_clicked()
{
    //récupération des informations dans les champs
    QString numZone = ui->cBoxZoneMod->currentText();
    QString numLieuActuel = ui->lEditNumLieuActuel->text();
    QString numLieu = ui->cBoxZoneLieuMod->currentText();
    QString sensMonter = ui->lEditZoneSensMonterMod->text();
    QString legende = ui->txtZoneLegendeMod->toPlainText();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(sensMonter == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de modifier cette Zone.\nLes champs sont vides.\nErreur 025."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool modZone = pBdd->addModZone(numZone, numLieuActuel, numLieu, sensMonter, legende);

        if(!modZone){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de modifier cette Zone.\nVerifier les champs.\nErreur 012."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Modifier une Zone"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerZoneMod_clicked();
            this->actuAffichage();
        }
    }
}
//SLOT combobox zone supp
void Configurer::on_cBoxZoneSupp_activated(int index)
{
    QString numLieu = listeZone.at(index).numLieu;
    QString sensMonter = listeZone.at(index).sensMonter;
    QString legende = listeZone.at(index).legende;

    //ajout champs
    ui->txtZoneLieuSupp->clear();
    ui->txtZoneLieuSupp->textCursor().insertText(numLieu);
    ui->lEditZoneSensMonterSupp->clear();
    ui->lEditZoneSensMonterSupp->insert(sensMonter);
    ui->txtZoneLegendeSupp->clear();
    ui->txtZoneLegendeSupp->textCursor().insertText(legende);
}
//SLOT bouton ok zone supp
void Configurer::on_btOkZoneSupp_clicked()
{
    //récupération des informations dans les champs
    QString numZone = ui->cBoxZoneSupp->currentText();
    QString numLieu = ui->txtZoneLieuSupp->toPlainText();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numLieu == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de supprimer ce Lieu.\nLes champs sont vides.\nErreur 026."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool supp = pBdd->setSuppZone(numZone);

        if(!supp){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de supprimer cette Zone.\nVerifier les champs.\nErreur 014."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Supprimer une Zone"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerZoneSupp_clicked();
            this->actuAffichage();
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ONGLET GESTION POSITIONS

//combobox numéro de vue
void Configurer::on_cBoxPositionNumVue_activated(int index)
{
    QString legende = listeVue.at(index).legende;

    //ajout champs
    ui->txtPositionInfoVue->clear();
    ui->txtPositionInfoVue->textCursor().insertText(legende);
}
//combobox numéro de zone
void Configurer::on_cBoxPositionNumZone_activated(int index)
{
    QString legende = listeZone.at(index).legende;
    QString numLieu = listeZone.at(index).numLieu;

    //ajout champs
    ui->txtPositionInfoZone->clear();
    ui->txtPositionInfoZone->textCursor().insertText(legende);
    ui->lEditPositionNumLieu->clear();
    ui->lEditPositionNumLieu->insert(numLieu);

    //obtenir legende Lieu
    QString legendeLieu = pBdd->getLegendeLieu(numLieu);
    //ajout champs
    ui->txtPositionInfoLieu->clear();
    if(legendeLieu == "" || legendeLieu == "erreur"){
        ui->txtPositionInfoLieu->textCursor().insertText("Aucune légende");
    }else{
        ui->txtPositionInfoLieu->textCursor().insertText(legendeLieu);
    }

    //recherche si position existe déjà
    //récupération info nécessaire dans les champs
    QString numVue = ui->cBoxPositionNumVue->currentText();
    QString numZone = ui->cBoxPositionNumZone->currentText();

    //nettoyage QList
    listeRepresentation.clear();

    bool representation = pBdd->getRepresentation(&listeRepresentation, numVue, numZone);
    if(!representation){
        this->etatPosition = true;
        //pas de position enregistré
        QMessageBox::information(0, tr("Ajouter Coordonnees"),
                     tr("Il n'existe pas encore de position.\nVeuiller remplir les champs.\n"),
                              QMessageBox::Ok);
    }else{
        this->etatPosition = false;
        //position déjà enregistrée
        QMessageBox::information(0, tr("Modifier Coordonnees"),
                     tr("Il existe deja des positions.\nVeuiller remplir les champs pour faire des modifications.\n"),
                              QMessageBox::Ok);
        if(!listeRepresentation.empty()){
            for(int i=0; i < listeRepresentation.count(); i++){
                QString x = listeRepresentation.at(i).x;
                QString y = listeRepresentation.at(i).y;
                QString xA = listeRepresentation.at(i).xA;
                QString yA = listeRepresentation.at(i).yA;
                QString xB = listeRepresentation.at(i).xB;
                QString yB = listeRepresentation.at(i).yB;

                //affichage
                ui->lEditPositionLieuX->clear();
                ui->lEditPositionLieuX->insert(x);
                ui->lEditPositionLieuY->clear();
                ui->lEditPositionLieuY->insert(y);
                ui->lEditPositionZoneXA->clear();
                ui->lEditPositionZoneXA->insert(xA);
                ui->lEditPositionZoneYA->clear();
                ui->lEditPositionZoneYA->insert(yA);
                ui->lEditPositionZoneXB->clear();
                ui->lEditPositionZoneXB->insert(xB);
                ui->lEditPositionZoneYB->clear();
                ui->lEditPositionZoneYB->insert(yB);

            }
        }else{
            //affichage par défaut (0)
            ui->lEditPositionLieuX->clear();
            ui->lEditPositionLieuX->insert(0);
            ui->lEditPositionLieuY->clear();
            ui->lEditPositionLieuY->insert(0);
            ui->lEditPositionZoneXA->clear();
            ui->lEditPositionZoneXA->insert(0);
            ui->lEditPositionZoneYA->clear();
            ui->lEditPositionZoneYA->insert(0);
            ui->lEditPositionZoneXB->clear();
            ui->lEditPositionZoneXB->insert(0);
            ui->lEditPositionZoneYB->clear();
            ui->lEditPositionZoneYB->insert(0);
        }

    }//fin representation
}
//bouton annulé ajouter/modifier position
void Configurer::on_btAnnulerPosition_clicked()
{
    ui->cBoxPositionNumVue->setCurrentIndex(0);
    ui->txtPositionInfoVue->clear();
    ui->cBoxPositionNumZone->setCurrentIndex(0);
    ui->txtPositionInfoZone->clear();
    ui->lEditPositionZoneXA->clear();
    ui->lEditPositionZoneYA->clear();
    ui->lEditPositionZoneXB->clear();
    ui->lEditPositionZoneYB->clear();
    ui->lEditPositionNumLieu->clear();
    ui->txtPositionInfoLieu->clear();
    ui->lEditPositionLieuX->clear();
    ui->lEditPositionLieuY->clear();
    this->etatPosition = -1;
}
//SLOT bouton ok ajouter/modifier position
void Configurer::on_btOkPosition_clicked()
{
    //récupération des informations dans les champs
    QString numVue = ui->cBoxPositionNumVue->currentText();
    QString numZone = ui->cBoxPositionNumZone->currentText();
    QString numLieu = ui->lEditPositionNumLieu->text();
    QString xA = ui->lEditPositionZoneXA->text();
    QString yA = ui->lEditPositionZoneYA->text();
    QString xB = ui->lEditPositionZoneXB->text();
    QString yB = ui->lEditPositionZoneYB->text();
    QString x = ui->lEditPositionLieuX->text();
    QString y = ui->lEditPositionLieuY->text();

    //ajouter position
    if(this->etatPosition == 1){
        //requête
        bool addPosition = pBdd->setPosition(numVue, numZone, numLieu, xA, yA, xB, yB, x, y);

        if(!addPosition){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible d'ajouter ces coordonnees.\nVerifier les champs.\nErreur 015."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Ajouter Coordonnees"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerPosition_clicked();
            this->etatPosition = -1;
            this->actuAffichage();
        }
    //modifier position
    } else if (this->etatPosition == 0){
        //requête
        bool modPosition = pBdd->addModPosition(numVue, numZone, numLieu, xA, yA, xB, yB, x, y);

        if(!modPosition){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de modifier ces coordonnees.\nVerifier les champs.\nErreur 016."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Modifier Coordonnees"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerPosition_clicked();
            this->etatPosition = -1;
            this->actuAffichage();
        }
    }else{
        //ok
        QMessageBox::warning(0, tr("Attention champs vides"),
                     tr("Operation echouee.\nLes champs sont vides.\nErreur 017."),
                              QMessageBox::Ok);
    }
}
//SLOT comboBox supp vue
void Configurer::on_cBoxPositionSuppNumVue_activated(int index)
{
    QString legende = listeVue.at(index).legende;
    QString numVue = listeVue.at(index).numVue;

    //ajout champs
    ui->txtPositionSuppInfoVue->clear();
    ui->txtPositionSuppInfoVue->textCursor().insertText(legende);

    //nettoyer combobox
    ui->cBoxPositionSuppNumZone->clear();

    //nettoyer QList
    listeRepresentation.clear();

    //obtenir les zones liées avec cette vue
    pBdd->getZoneLierVue(&listeRepresentation, numVue);

    if(!listeRepresentation.empty()){
        for(int i = 0; i < listeRepresentation.count(); i++) {
            QString numZone = listeRepresentation.at(i).numZone;

            //ajout du combo
            ui->cBoxPositionSuppNumZone->addItem(numZone);
        }
    }
}
//SLOT comboBox supp Zone
void Configurer::on_cBoxPositionSuppNumZone_activated(int index)
{
    QString legende = listeZone.at(index).legende;
    QString numLieu = listeZone.at(index).numLieu;

    //ajout champs
    ui->txtPositionSuppInfoZone->clear();
    ui->txtPositionSuppInfoZone->textCursor().insertText(legende);
    ui->lEditPositionSuppNumLieu->clear();
    ui->lEditPositionSuppNumLieu->insert(numLieu);

    //obtenir legende Lieu
    QString legendeLieu = pBdd->getLegendeLieu(numLieu);
    //ajout champs
    ui->txtPositionSuppInfoLieu->clear();
    if(legendeLieu == "" || legendeLieu == "erreur"){
        ui->txtPositionSuppInfoLieu->textCursor().insertText("Aucune légende");
    }else{
        ui->txtPositionSuppInfoLieu->textCursor().insertText(legendeLieu);
    }

    //récupération des champs
    QString numVue = ui->cBoxPositionSuppNumVue->currentText();
    QString numZone = ui->cBoxPositionSuppNumZone->currentText();

    listeRepresentation.clear();

    pBdd->getRepresentation(&listeRepresentation, numVue, numZone);

    if(!listeRepresentation.empty()){
        for(int i=0; i < listeRepresentation.count(); i++){
            QString x = listeRepresentation.at(i).x;
            QString y = listeRepresentation.at(i).y;
            QString xA = listeRepresentation.at(i).xA;
            QString yA = listeRepresentation.at(i).yA;
            QString xB = listeRepresentation.at(i).xB;
            QString yB = listeRepresentation.at(i).yB;

            //affichage
            ui->lEditPositionSuppLieuX->clear();
            ui->lEditPositionSuppLieuX->insert(x);
            ui->lEditPositionSuppLieuY->clear();
            ui->lEditPositionSuppLieuY->insert(y);
            ui->lEditPositionSuppZoneXA->clear();
            ui->lEditPositionSuppZoneXA->insert(xA);
            ui->lEditPositionSuppZoneYA->clear();
            ui->lEditPositionSuppZoneYA->insert(yA);
            ui->lEditPositionSuppZoneXB->clear();
            ui->lEditPositionSuppZoneXB->insert(xB);
            ui->lEditPositionSuppZoneYB->clear();
            ui->lEditPositionSuppZoneYB->insert(yB);
        }
    }
}
//SLOT bouton annulé supp positions
void Configurer::on_btAnnulerPositionSupp_clicked()
{
    ui->cBoxPositionSuppNumVue->setCurrentIndex(0);
    ui->txtPositionSuppInfoVue->clear();
    ui->cBoxPositionSuppNumZone->clear();
    ui->txtPositionSuppInfoZone->clear();
    ui->lEditPositionSuppZoneXA->clear();
    ui->lEditPositionSuppZoneYA->clear();
    ui->lEditPositionSuppZoneXB->clear();
    ui->lEditPositionSuppZoneYB->clear();
    ui->lEditPositionSuppNumLieu->clear();
    ui->txtPositionSuppInfoLieu->clear();
    ui->lEditPositionSuppLieuX->clear();
    ui->lEditPositionSuppLieuY->clear();
}
//SLOT bouton ok supp positions
void Configurer::on_btOkPositionSupp_clicked()
{
    //récupération des informations dans les champs
    QString numVue = ui->cBoxPositionSuppNumVue->currentText();
    QString numZone = ui->cBoxPositionSuppNumZone->currentText();

    //évite d'avoir appuyer sur le bouton par mégarde
    if(numZone == ""){
        QMessageBox::warning(0, tr("Attention : requete impossible"),
                             tr("Impossible de supprimer ces coordonnees.\nLes champs sont vides.\nErreur 027."),
                              QMessageBox::Ok);
    }
    else{
        //requête
        bool supp = pBdd->setSuppPosition(numVue, numZone);

        if(!supp){
            //erreur
            QMessageBox::warning(0, tr("Attention : requete impossible"),
                                 tr("Impossible de supprimer ces coordonnees.\nVerifier les champs.\nErreur 018."),
                                  QMessageBox::Ok);
        }else{
            //ok
            QMessageBox::information(0, tr("Supprimer Coordonnees"),
                         tr("Operation reussie.\n"),
                                  QMessageBox::Ok);
            this->on_btAnnulerPositionSupp_clicked();
            this->actuAffichage();
        }
    }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ONGLET GESTION DES TIMERS

//SLOT bouton ok régler timer
void Configurer::on_btOkTimer_clicked()
{
    int clic = QMessageBox::warning(0, tr("Attention : modification des durees"),
             tr("Etes vous sur de vouloir modifier les durees des Timers ?\n"),
                      QMessageBox::Ok ,QMessageBox::Cancel);

    if(clic == QMessageBox::Ok){
        //récupération des champs
        QString tempoMouv = ui->lEditTimerMouv->text();
        QString tempoRecep = ui->lEditTimerRecep->text();

        if(tempoMouv == "" || tempoRecep == "" || tempoMouv == "0" || tempoRecep == "0"){
            QMessageBox::warning(0, tr("Attention : champs vides"),
                         tr("Vous ne pouvez pas laisser des champs vides.\nErreur 028."),
                                  QMessageBox::Ok);
        }else{
            //requête
            bool regler = pBdd->setTempo(tempoMouv, tempoRecep);
            if(!regler){
                //erreur
                QMessageBox::warning(0, tr("Attention : requete impossible"),
                                     tr("Impossible de modifier les durees des Timers.\nVerifier les champs.\nErreur 019."),
                                      QMessageBox::Ok);
            }else{
                //ok
                QMessageBox::information(0, tr("Modifier durees Timers"),
                             tr("Operation reussie.\n"),
                                      QMessageBox::Ok);
                this->actuAffichage();
            }//si requete bien passée
        }//si champs vide
   }//si modif ok
}
