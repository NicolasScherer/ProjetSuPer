#include "ihm.h"
#include "ui_ihm.h"
#include "contenuonglet.h"
#include <QtSql>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <QLabel>


//////////////////////
/*** CONSTRUCTEUR ***/
Ihm::Ihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ihm)
{
    ui->setupUi(this);
    pLecteur = new Lecteur; //à enlever à l'intégration
    pDynamique = new Dynamique;
    pBdd = new Bdd;

/* //signaux
     Bouton btNewLecteur
    connect(ui->btNewLecteur, SIGNAL(clicked()), this, SLOT(lecteurActif(pLecteur)));

    //connect
    connect(this, SIGNAL(signalNewLecteur(const Lecteur &)), this, SLOT(lecteurActif(const Lecteur &)));
    connect(this, SIGNAL(signalDelLecteur(pLecteur)), this, SLOT(lecteurInactif(pLecteur)));
    //émission signal
   emit signalNewLecteur(pLecteur);
*/


    //obtention du nombre de vue max
    int vueMax = pBdd->getVueMax();

    //déclaration QList
    QList<T_TupleOnglet> listeTupleO;

    //récupération des infos sur les onglets
    pBdd->getVue(&listeTupleO);

    if(!listeTupleO.empty()){
        for(int i = 0; i < listeTupleO.count() && i < vueMax; i++) {
            int num_vue = listeTupleO.at(i).num_vue;
            QString legende = listeTupleO.at(i).legende;
            QString image = listeTupleO.at(i).image;
            //ajout de l'onglet
            this->ajoutOnglet(num_vue, legende, image);
        }
    }

    //supprimer les deux onglets de base
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(vueMax);
    //mettre l'onglet de base dans la vue
    ui->tabWidget->setCurrentIndex(0);

    lecteurActif(pLecteur);     // à enlever à l'intégration
   // lecteurInactif(pLecteur);   // à enlever à l'intégration
   // lecteurInconnu();           // à enlever à l'intégration

 //   traitementTrame("960021A701");  //à enlever à l'intégration
    //trame type : AD D01 6A7 01
    //AD niveau de reception
    //DO1 n° de badge
    //6A7 mouvement
    //01 n° lecteur

    //fenêtre sans bordure
    setWindowFlags(Qt::FramelessWindowHint);

}
/*-------------------------------*
 * Slot traitement de la trame   *
 *-------------------------------*/
bool Ihm::traitementTrame(QString trame){

    //décodage trame
    QString num_badge, sens, mouvement, num_lecteur;
    T_ListeLabel *tll;  //pointeur sur structure
    //nbT++; // compteur de trames

    //séparation des parties de la trame
    num_badge = trame.mid(2,3); //numéro de badge

    //suppression mauvais badge
    if(num_badge == "000") {
        qDebug("Mauvais badge.");
        ui->txtAlarme->textCursor().insertText("<Erreur> Mauvais badge num=000\n");
        return false;
    }

    sens = trame.mid(0,2); //niveau de réception du tag
    mouvement = trame.mid(5,3); //niveau de mouvement mesuré
    num_lecteur = trame.mid(8,2);   //numéro du lecteur

    //conversion des valeurs en int à partir de ASCII hexa et mise à l'échelle
    //c'est-à-dire conversion de l'hexadécimal en décimal
    int num_badge_i = num_badge.toInt(0,16);
    int sens_i = sens.toInt(0,16);
    int num_lecteur_i = num_lecteur.toInt(0,16);
    int mouvement_i = mouvement.toInt(0,16);

    //si le badge n'existe dans la BDD
    if(!pBdd->badgeExiste(num_badge)){
        ui->txtAlarme->textCursor().insertText("<Erreur><Badge "+num_badge+"> Badge inconnu  dans la Base de donnees\n");
        return false;
    }

    //badge n'existe pas sur l'IHM
    if(!pDynamique->BadgeActif[num_badge_i]){

        tll = new T_ListeLabel();

        for(int i=0 ; i<MAXLECTEURS ; i++){   // init à 100
            for(int j=0 ; j<MAXVAL ; j++){
                tll->moySens[i][j]=100;
            }
        }
        for(int i=0 ; i<MAXLECTEURS ; i++){
            tll->sdp[i]=0;      //sens de passage
            tll->sdpMem[i]=0;
        }
        memset(tll->indMoy, 0, sizeof(tll->indMoy));    //init à 0

        //obtenir vue(s) en fonction du lecteur
        //déclaration QList
        QList<T_TupleLecteurS> listeTupleL;

        pBdd->getVueFctLect(num_lecteur_i, &listeTupleL);

        //récupération des infos dans la liste
        if (!listeTupleL.empty()){
            for (int i = 0; i < listeTupleL.count(); i++) {

                int num_vue = listeTupleL.at(i).num_vue;

                //se placer sur l'onglet
                QWidget *onglet;
                onglet = pDynamique->onglet[num_vue];

                //nouveau label dynamique pour un badge
                tll->labelB[num_vue][num_badge_i] = new QLabel(onglet);

                //réglage par défaut du nouveau badge (vert + haut)
                tll->labelB[num_vue][num_badge_i]->setPixmap(QPixmap("../ressources/lecteur_actif_petit.jpg"));
                tll->labelB[num_vue][num_badge_i]->setGeometry(590, 620, 15, 42); // largeur hauteur à définir
            }
        }

        tll->numBadge = num_badge_i;        //numéro de badge
        tll->numLecteur = num_lecteur_i;    //numéro de lecteur
        tll->etat = 0;                      //aller

        // réglage du timer associé au mouvement
        tll->tpsMouv = new QTimer(this);                                    //nouveau Timer
        connect(tll->tpsMouv, SIGNAL(timeout()), this, SLOT(TimerMouv()));  //connect timeout
        tll->tpsMouv->setSingleShot(true);                                  //un seul temps
        tll->tpsMouv->start(this->tempoM);                                  //débute le timer

        // réglage du timer associé à la réception
        tll->tpsSens[num_lecteur_i] = new QTimer(this);                                     //nouveau Timer
        connect(tll->tpsSens[num_lecteur_i], SIGNAL(timeout()), this, SLOT(TimerSens()));   //connect timeout
        tll->tpsSens[num_lecteur_i]->setSingleShot(true);                                   //un seul temps
        tll->tpsSens[num_lecteur_i]->start(this->tempoR);                                   //débute le timer

        // ajout à la liste mémoire
        listeLabel.append(tll);

        //maintenant le badge existe sur l'IHM donc le sauvegarder
        pDynamique->BadgeActif[num_badge_i] = true;
    }

    tll->numLecteur = num_lecteur_i;    //sauvegarde numéro lecteur

    tll->etat |= MOUV0;   // mouv=0
    //relance du timer si mouvement
    if (mouvement_i > 0 ) {  // si mouvement
        tll->etat &= ~MOUV;    // alarme mouvement
        tll->etat &= ~MOUV0;   // un seul mouvement
        tll->tpsMouv->setSingleShot(true);
        tll->tpsMouv->start(this->tempoM);  //ms
    }

    // réarmer le timer REC, le créer si nouveau lecteur
    tll->etat &= ~REC;
    //création timer réception, si nouveau lecteur
    if (!tll->tpsSens[num_lecteur_i]) {
        tll->tpsSens[num_lecteur_i] = new QTimer(this);
        connect(tll->tpsSens[num_lecteur_i], SIGNAL(timeout()), this, SLOT(TimerRec()));
    }
    //réarmer le timer de réception
    tll->tpsSens[num_lecteur_i]->setSingleShot(true);
    tll->tpsSens[num_lecteur_i]->start(this->tempoR);

    //Recherche identité de la personne
    int num_pers = pBdd->badgeIdentite(num_badge_i);
    if (num_pers == -1){
        //le badge n'est pas lié avec une personne
        ui->txtAlarme->textCursor().insertText("<Erreur><Badge "+num_badge+"> Badge non lie a une personne\n");
    }

    // calcul de la moyenne de la sensibilité
    tll->moySens[num_lecteur_i][tll->indMoy[num_lecteur_i]++] = sens_i ;

    if (tll->indMoy[num_lecteur_i] == MAXVAL){
        tll->indMoy[num_lecteur_i] = 0;     //indice du tableau de moyenne
    }
    int moy = 0;
    moy = calculerMoyenne(tll);     //sur MAXVAL valeur
    tll->sdp[num_lecteur_i] = moy;  //mémo pour calcul sens de passage
    moy -= 100;

    sensDePassage(tll);  //maj de zone et du sens de passage de ce badge




/*
        //---obtenir position du badge


            //obtenir lieu (xA,yA et xB,yB) en fonction du lecteur et de la vue (en cours)

            //déclaration QList
            QList<T_TuplePositionLieu> listePositionLieu;

            pBdd->getPositionLieu(num_vue, num_lecteur_i, &listePositionLieu);

            //récupération des infos dans la liste
            if(!listePositionLieu.empty()){
     //inutile? // for(int i = 0; i < listePositionLieu.count(); i++) {
  //              int xA[num_vue] = listePositionLieu.at(0).xA;
    //            int yA[num_vue] = listePositionLieu.at(0).yA;
      //          int xB[num_vue] = listePositionLieu.at(0).xB;
        //        int yB[num_vue] = listePositionLieu.at(0).yB;

*/




    }


    //sinon afficher la personne
    //comme on connait le numéro de la personne, on peut aller taper dans la classe Dynamique

}
///////////////////////////////////////////////////////////
void Ihm::TimerMouv() {
    T_ListeLabel *tll;
    int nbB = listeLabel.size();
    for (int i=0 ; i<nbB ; i++) {
        tll = listeLabel.at(i);
        //si Timer n'est pas actif
        if (!tll->tpsMouv->isActive()) {
            tll->etat |= MOUV;   // homme en danger
        }
    }
}

/////////////////////
/*** DESTRUCTEUR ***/
Ihm::~Ihm()
{
    delete pLecteur;
    delete pDynamique;
    delete pBdd;
    delete ui;
}
//////////////////////////////
/*** SLOT LECTEUR INCONNU ***/
void Ihm::lecteurInconnu(){
    //ajout texte Ihm
    ui->txtAlarme->textCursor().insertText("<Erreur> quelque chose a tente de se connecter\n");
}
//////////////////////////////
/*** SLOT LECTEUR INACTIF ***/
void Ihm::lecteurInactif(Lecteur *pLecteur){
    //obtenir le numéro de lecteur grâce à la classe Lecteur
    //int numLecteur = pLecteur->getnum_lecteur();
    int numLecteur = 1; //doit disparaitre à l'intégration

    //déclaration QList
    QList<T_TupleLecteurS> listeTupleL;

    pBdd->getVueFctLect(numLecteur, &listeTupleL);

    //récupération des infos dans la liste
    if(!listeTupleL.empty()){
        for(int i = 0; i < listeTupleL.count(); i++) {
            int num_vue = listeTupleL.at(i).num_vue;
            //suppression d'un lecteur (en dynamique)
            this->suppLecteur(numLecteur, num_vue);
            //listeTupleL.removeAt(i);    //A VERIFIER
        }
    }

}
/////////////////////////////////////
/*** méthode SUPPRESSION LECTEUR ***/
void Ihm::suppLecteur(int numLecteur, int num_vue){

    //se placer sur le bon onglet
    QWidget *onglet;
    onglet = pDynamique->onglet[num_vue];
    //test valeur
    qDebug() << "valeur pointeur onglet" << onglet << endl;

    //se placer sur le bon label du lecteur
    QLabel *labelL;
    labelL = pDynamique->labelL[num_vue][numLecteur];

    //supprimer le label
    labelL->clear();
    delete labelL;

    //message d'avertissement (Alarmes)
    QString numLecteurS = QString::number(numLecteur);
    QString numVueS = QString::number(num_vue);
    QString supLecteur = "<Lecteur ";
    supLecteur += numLecteurS;
    supLecteur += "><Vue ";
    supLecteur += numVueS;
    supLecteur += "> vient de se deconnecter";
    ui->txtAlarme->textCursor().insertText(supLecteur + "\n");
}
////////////////////////////
/*** SLOT LECTEUR ACTIF ***/
void Ihm::lecteurActif(Lecteur *pLecteur){
    //obtenir le numéro de lecteur grâce à la classe Lecteur
    //int numLecteur = pLecteur->getnum_lecteur();
    int numLecteur = 1; //doit disparaitre à l'intégration

    //déclaration QList
    QList<T_TupleLecteurE> listeTupleLA;

    pBdd->getVuePosFctLect(numLecteur, &listeTupleLA);

    //récupération des infos dans la liste
    if(!listeTupleLA.empty()){
        for(int i = 0; i < listeTupleLA.count(); i++) {
            int num_vue = listeTupleLA.at(i).num_vue;
            int x = listeTupleLA.at(i).x;
            int y = listeTupleLA.at(i).y;

            //ajout d'un lecteur (en dynamique)
            this->ajoutLecteur(numLecteur, num_vue, x, y);
        }
    }

}
///////////////////////////////
/*** méthode AJOUT LECTEUR ***/
void Ihm::ajoutLecteur(int numLecteur, int num_vue, int x, int y){

    //se placer sur le bon onglet
    QWidget *onglet;
    onglet = pDynamique->onglet[num_vue];
    //test valeur
    qDebug() << "valeur pointeur onglet" << onglet << endl;

    //nouveau label dynamique pour mettre l'image correspondant
    QLabel *labelL = new QLabel(onglet);
    //différente taille d'images utilisées
    if(num_vue == 1){
        labelL->setPixmap(QPixmap("../ressources/lecteur_actif_petit.jpg"));
    }else{
        labelL->setPixmap(QPixmap("../ressources/lecteur_actif.jpg"));
        }
    labelL->setGeometry(x, y, 15, 42); // largeur hauteur à définir

    //sauvegarde du pointeur du label du lecteur
    pDynamique->labelL[num_vue][numLecteur] = labelL;

}
//////////////////////////////
/*** méthode AJOUT ONGLET ***/
void Ihm::ajoutOnglet(int num_vue, QString legende, QString image)
{
    //nouveau onglet dynamique avec légende
    ContenuOnglet *pContenuOnglet = new ContenuOnglet(0, image);
    ui->tabWidget->insertTab(num_vue, pContenuOnglet, legende);

    //sauvegarde du pointeur onglet
    pDynamique->onglet[num_vue] = pContenuOnglet;
    qDebug() << "valeur dans la classe" << pDynamique->onglet[num_vue] << endl;

}

/////////////////////////////
/*** SLOT bouton Quitter ***/
void Ihm::on_btQuitter_clicked()
{
    this->~Ihm();
}


