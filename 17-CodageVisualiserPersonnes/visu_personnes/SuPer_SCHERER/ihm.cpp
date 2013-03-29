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

    traitementTrame("960021A701");  //à enlever à l'intégration
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
    bool existe = false;
    //T_ListeLabel *tll;

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

    //test si le badge existe dans la BDD
    if(!pBdd->badgeExiste(num_badge)){
        ui->txtAlarme->textCursor().insertText("<Erreur><Badge "+num_badge+"> Badge non reference dans la Base de donnees\n");
        return false;
    }

    //test si le badge existe sur l'ihm
   /* int nbLigneBadge = listeLabel.size();
    for(int i=0 ; i<nbLigneBadge ; i++){
        tll = listeLabel.at(i);
        if (num_badge_i == tll->noBadge) {
            existe=true;
            break;
        } // if trouvé
    } // for
*/
    //n'existe pas sur l'ihm
    //combien de vue ?
    int vueMax = pBdd->getVueMax();
    //se placer sur les différentes vues
    for(int num_vue=vueMax ; num_vue>0 ; num_vue--){
        //se placer sur un onglet
        QWidget *onglet;
        onglet = pDynamique->onglet[num_vue];

        //nouveau label dynamique pour un badge
        QLabel *labelB = new QLabel(onglet);

        //sauvegarde du pointeur du label pour un badge
        pDynamique->labelB[num_vue][num_badge_i];

    }
    //ajouter label défaut vert
    //sauvegarde label

    /*

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
    */



 /*   //creation label si existe pas
    if(!existe){
        tll = new T_ListeLabel();
        nbB++;
        for(int i=0 ; i<config.maxLect ; i++)   // init à 100
            for(int j=0 ; j<config.maxVal ; j++)
                tll->moySens[i][j]=100;
        for(int i=0 ; i<config.maxLect ; i++)
        {
            tll->sdp[i]=0;
            tll->memSdp[i]=0;
        } // for
        memset(tll->indMoy, 0, sizeof(tll->indMoy));   // init à 0
        tll->l = new QLabel(ui->centralWidget);
        tll->noBadge = inoB;
        tll->noLect = inoLect;
        tll->etat = 0; // aller
        // réglage du timer associé au mouvement
        tll->wdm = new QTimer(this);
        connect(tll->wdm, SIGNAL(timeout()), this, SLOT(onTimerMouv()));
        tll->wdm->setSingleShot(true);
        tll->wdm->start(config.tempoM); // secondes
        // réglage du timer associé à la réception
        tll->wdr[inoLect] = new QTimer(this);
        connect(tll->wdr[inoLect], SIGNAL(timeout()), this, SLOT(onTimerRec()));
        tll->wdr[inoLect]->setSingleShot(true);
        tll->wdr[inoLect]->start(config.tempoR); // secondes
        // ajout à la liste mémoire et affichage
        listeLabel.append(tll);
        nbB = listeLabel.size();
        ui->lNbB->setText(QString("%1").arg(nbB)); // affiche nb de badge actuel
        // réglage par défaut du nouveau label
        tll->l->setEnabled(true);
        tll->l->setGeometry(QRect(590, 620, 20, 20));
        tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flechevertehaut.jpg")));
        tll->l->setScaledContents(true);
        tll->l->show();
    } // if !existe
    */
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
    ui->txtAlarme->textCursor().insertText("<Erreur> quelque chose a tenter de se connecter\n");
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


