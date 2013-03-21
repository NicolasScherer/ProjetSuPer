#include "ihm.h"
#include "ui_ihm.h"
#include "contenuonglet.h"
#include <QtSql>
#include <QString>
#include <QtDebug>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>

//////////////////////
/*** CONSTRUCTEUR ***/
Ihm::Ihm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ihm)
{
    ui->setupUi(this);
    pLecteur = new Lecteur;
    pDynamique = new Dynamique;
    pBdd = new Bdd;

//*** signaux
    // Bouton btNewLecteur
    //connect(ui->btNewLecteur, SIGNAL(clicked()), this, SLOT(lecteurActif(pLecteur)));

    //connect
 //   connect(this, SIGNAL(signalNewLecteur(const Lecteur &)), this, SLOT(lecteurActif(const Lecteur &)));
  //  connect(this, SIGNAL(signalDelLecteur(pLecteur)), this, SLOT(lecteurInactif(pLecteur)));
    //émission signal
  // emit signalNewLecteur(pLecteur);

    //obtention du nombre de vue max
    int vueMax = pBdd->getVueMax();

    //récupération des infos sur les onglets
    T_Tuple *TtupleIhm = pBdd->getVue();


    if(num_vue <= vueMax){
        ajoutOnglet(num_vue, legende, image);
    }


    //supprimer les deux onglets de base
    ui->tabWidget->removeTab(0);
    ui->tabWidget->removeTab(vueMax);

    //lecteurActif(pLecteur);     // à enlever à l'intégration
    //lecteurInactif(pLecteur);   // à enlever à l'intégration
    //lecteurInconnu();           // à enlever à l'intégration

    //fenêtre sans bordure
    setWindowFlags(Qt::FramelessWindowHint);

}
/////////////////////
/*** DESTRUCTEUR ***/
Ihm::~Ihm()
{
    delete pLecteur;


    // PENSER A DETRUIRE LES ONGLETS

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

    pBdd->getVueFctLect(numLecteur);

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
  //  int numLecteur = pLecteur->getnum_lecteur();
    int numLecteur = 1;

  /*  //avec le numéro obtenu, obtenir la vue et la position (x, y)
    QString req;
    req = "SELECT A1.num_lieu, A2.num_vue, A2.x, A2.y ";
    req += "FROM lecteur A1, representationLieuSurVue A2 ";
    req += "WHERE A1.num_lieu = A2.num_lieu AND A1.num_lecteur=:numLecteur";
    query->prepare(req);
    query->bindValue(":numLecteur", numLecteur);
    if(!query->exec()){
         qDebug() << "Erreur requete SQL vue/position lecteur" << endl;
    }

    int num_vue, x, y;

    while(query->next()){
        num_vue = query->value(1).toInt();
        x = query->value(2).toInt();
        y = query->value(3).toInt();

        //ajout d'un lecteur (en dynamique)
        ajoutLecteur(numLecteur, num_vue, x, y);
    }*/

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
