#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) ,
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // pour le menu
    ihmAffecter = new CIhmAffecter();
    ihmPersonne = new CIhmPersonne();
    ihmLecteur = new CIhmLecteur();
    ihmBadge = new CIhmBadge();
    ihmCamera = new CIhmCamera();
    ihmParametrer = new CIhmParametrer();
    connect(ui->actionBadgesAffecter, SIGNAL(triggered()), this, SLOT(on_menuBadgesAffecter()));
    connect(ui->actionGerer_les_personnes, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_personnes_triggered()));
    connect(ui->actionGerer_les_badges, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_badges_triggered()));
    connect(ui->actionGerer_les_cameras, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_cameras_triggered()));
    connect(ui->actionGerer_les_lecteurs, SIGNAL(triggered()), this, SLOT(on_menuGerer_les_lecteurs_triggered()));
    connect(ui->actionParametrer, SIGNAL(triggered()), this, SLOT(on_menuParametrer_triggered()));
    vue=0; // pour les coordonnées d'affichage
    ui->twOnglets->setCurrentIndex(0);

    // pour la BDD
    bdd = new CBdd(this);
    bdd->initLecteurs();  // tous les lecteurs inoccupés
    bdd->effacerPertes();  // efface les badges perdus
//    bdd->getConfig(&config);

    nbT = 0;   // nbre de trame
    nbB = 0;   // nbre de badges
    nbLect=0; // aucun lecteur connecté

    // pour le réseau
    serv = new QTcpServer(this);
    serv->listen(QHostAddress::Any, 2222);
    connect(serv, SIGNAL(newConnection()), this, SLOT(onGererThread()));
    ui->teRecu->append(QString::fromUtf8("Serveur en écoute des lecteurs."));
    // timer d'actualisation de l'affichage
    aff = new QTimer(this);
    connect(aff, SIGNAL(timeout()), this, SLOT(on_affichage()));
    aff->start(config.tempoA);

//    // pour la file de message
//    msg = new CMsg(this);

} // method

MainWindow::~MainWindow()
{
    delete ihmAffecter;
    delete ihmPersonne;
    delete ihmLecteur;
    delete ihmBadge;
    delete ihmCamera;
    delete serv;
    delete bdd;
    while (!listeLabel.isEmpty()) {
        T_ListeLabel *tll = listeLabel.takeFirst();
        delete tll->l;
        delete tll->wdm;
        for(int i=0 ; i<config.maxLect ; i++)
            if (tll->wdr[i])
                delete tll->wdr[i];
        delete tll;
        delete listeLabel.takeFirst();
    } // while
    T_Thread *th;
    while (!lecteurs.isEmpty()) {
        th = lecteurs.takeFirst();
        delete th->thcl;
        delete th;
    } // while
    lecteurs.clear();
    delete aff;
    delete ui;
    //    delete msg;
} // method

/////////////////////////////////////////////////////////////
void MainWindow::afficherLecteur(int noL, bool etat)
{
    switch(noL) {
      case 1: ui->lLectCon->setEnabled(etat); break;
      case 2: ui->lLectServGen->setEnabled(etat); break;
      case 3: ui->lLectGAS->setEnabled(etat); break;
      case 4: ui->lLectCaps->setEnabled(etat); break;
      default: break;
    } // sw
} // method

///////////////////////////////////////////////////////////
void MainWindow::onEffacerUnThread() {
    T_Thread *th;
    int nb;

    nb = lecteurs.size();
    for (int i=0 ; i<nb ; i++) {
        th = lecteurs.at(i);
        if (th->thcl->isFinished()) {
            afficherLecteur(th->noLect, false);
            bdd->LecteurHorsService(th->noLect);
            ui->teRecu->append("Pb de communication avec le lecteur "+QString("%1").arg(th->noLect));
            delete th->thcl;
            delete th;
            lecteurs.removeAt(i);
            nbLect--;
            ui->lNbL->setText(QString("%1").arg(nbLect));
            break;
        } // if finish
    } // for
} // method

///////////////////////////////////////////////////////////
// return true si trame au bon format
bool MainWindow::traitement(QString &trame) {
 QString noBadge, sens, lect, mouv;
 int nbB;
 bool existe = false;
 T_ListeLabel *tll;

 nbT++; // compteur de trames

 // séparation des parties de la trame
 noBadge = trame.mid(3,3);
 if (noBadge == "000") {
     qDebug("Mauvais badge.");
     //qDebug(trame.toLocal8Bit().data());
     ui->teRecu->append("Mauvais badge no=000");
     return false;
 } // if noB
 sens = trame.mid(1,2);
 mouv = trame.mid(6,3);
 lect = trame.mid(9,2);
 //qDebug(mouv.toLocal8Bit().data());
 int inoB = noBadge.toInt(0,16);  // conversion
 int iSens = sens.toInt(0,16);   // conversion en int à partir de ascii hexa et mise à l'echelle
 int inoLect = lect.toInt(0,16);  // conversion

 // le badge existe-t-il dans la BDD ?
 if (!bdd->isBadgeExiste(noBadge)) {
     qDebug("Le badge n'est pas référencé dans la BDD.");
     ui->teRecu->append("Le badge "+noBadge+" n'est pas référencé dans la BDD.");
     return false;
 } // if isB

 // le badge est-il représenté sur l'IHM ?
 nbB = listeLabel.size();
 for (int i=0 ; i<nbB ; i++) {
     tll = listeLabel.at(i);
     if (inoB == tll->noBadge) {
         existe=true;
         break;
     } // if trouvé
 } // for

 // creation label si existe pas
 if (!existe) {
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

 tll->noLect = inoLect;

 tll->etat |= MOUV0;   // mouv=0
 // relance du timer si mouvement, réception et affichage
 if (mouv.toInt(0,16) > 0 ) {  // si mouvement
     tll->etat &= ~MOUV;    // alarme mouvement
     tll->etat &= ~MOUV0;   // un seul mouvement
     tll->wdm->setSingleShot(true);
     tll->wdm->start(config.tempoM); //  ms
 } // if mouvement

 // réarmer le timer REC, le créer si nouveau lecteur
 tll->etat &= ~REC;
 if (!tll->wdr[inoLect]) {
     tll->wdr[inoLect] = new QTimer(this);
     connect(tll->wdr[inoLect], SIGNAL(timeout()), this, SLOT(onTimerRec()));
 } // si création timer wdr
 tll->wdr[inoLect]->setSingleShot(true);
 tll->wdr[inoLect]->start(config.tempoR);

 // recherche identité
 if (bdd->aQuiAppartientCeBadge(noBadge) != -1) {
    tll->pers.nom = bdd->query->value(1).toString();
    tll->pers.pnom = bdd->query->value(2).toString();
    tll->pers.societe = bdd->query->value(3).toString();
    tll->pers.noPers = bdd->query->value(6).toInt();
 } else {  // a personne !
     tll->pers.noPers = -1;
 } // else

 // calcul de la moyenne de la sensibilité
 tll->moySens[inoLect][tll->indMoy[inoLect]++] = iSens;
 if (tll->indMoy[inoLect] == config.maxVal)
     tll->indMoy[inoLect] = 0;   // indice du tableau de moyenne
 int moy=0;
 moy = calculerMoyenne(tll);  // sur MAX_VAL valeur
 tll->sdp[inoLect] = moy;  // memo pour calcul sens de passage
 moy -= 100;

 sensDePassage(tll);  // maj de zone et du sens de passage de ce badge

 // recherche position affichage
 if (!bdd->infoDeCeLecteur(lect)) {
     qDebug("Je ne connais pas ce lecteur.");
     ui->teRecu->append("Lecteur inconnu !");
     return false;
 } // if ou ?
 bdd->getPointsZone(vue, tll->zone,&tll->ptA, &tll->ptB);
 calculerDroite(moy, tll->ptA, tll->ptB, &tll->ptF);  // retourne ptF

 bdd->receptionRetrouvee(inoB);  // efface badge dans perte

 // affichage ihm
 ui->teRecu->append(" S:"+sens+" B:"+noBadge+" M:"+mouv+" L:"+lect+" "+trame);

 return true;
}

///////////////////////////////////////////////////////////////
void MainWindow::on_affichage()   // toutes les TEMPOA ms
{
    T_ListeLabel *tll;
    int nbB;

    // témoin timer OK
    if (ui->lAff->isVisible())
        ui->lAff->setVisible(false);
    else
        ui->lAff->setVisible(true);

    nbB = listeLabel.size();  // nbre de badge
    for (int i=0 ; i<nbB ; i++)
    {
        tll = listeLabel.at(i);
        tll->l->setEnabled(true);
        switch(tll->etat) {
        case 0:  // ALLER
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flechevertehaut.jpg")));
            break;
        case 1:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flecherougehaut.jpg")));
            break;
        case 2:
            tll->l->setEnabled(false);
            break;
        case 3:
            tll->l->setEnabled(false);
            break;
        case 4:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flechevertebas.jpg")));
            break;
        case 5:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flecherougebas.jpg")));
            break;
        case 6:
            tll->l->setEnabled(false);
            break;
        case 7:
            tll->l->setEnabled(false);
            break;
        case 8:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flecheorangehaut.jpg")));
            break;
        case 9:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flecherougehaut.jpg")));
            break;
        case 10:
            tll->l->setEnabled(false);
            break;
        case 11:
            tll->l->setEnabled(false);
            break;
        case 12:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flecheorangebas.jpg")));
            break;
        case 13:
            tll->l->setPixmap(QPixmap(QString::fromUtf8("../ressources/flecherougebas.jpg")));
            break;
        case 14:
            tll->l->setEnabled(false);
            break;
        case 15:
            tll->l->setEnabled(false);
            break;
        } // sw etat

        if (tll->pers.noPers != -1) {
            tll->l->setGeometry(tll->ptF.x+(20*tll->pers.noPers),tll->ptF.y,20,20);
            tll->l->setToolTip("Badge "+ QString("%1").arg(tll->noBadge)+" de : "+tll->pers.nom+" "
                               +tll->pers.pnom+QString::fromUtf8(" Société : ")+tll->pers.societe+" "
                               +QString("Zone:%1").arg(tll->zone));
        } else {
            tll->pers.noPers = bdd->getNoPersSuivant();
            tll->l->setGeometry(tll->ptF.x+(20*tll->pers.noPers), tll->ptF.y, 20, 20);
            tll->l->setToolTip(QString::fromUtf8("Badge non affecté : ")+QString("%1 zone:%2").arg(tll->noBadge).arg(tll->zone));
        } // else
    } // for
} // method


///////////////////////////////////////////////////////////////
void MainWindow::sensDePassage(T_ListeLabel *tll)
{
    // pour l'instant, une seule zone
    if (tll->sdp[tll->noLect] < tll->memSdp[tll->noLect])
        tll->etat &= ~AR;  // retour
    if (tll->sdp[tll->noLect] > tll->memSdp[tll->noLect])
        tll->etat |= AR;  // aller
    if (tll->sdp[tll->noLect] != tll->noLect)
        tll->memSdp[tll->noLect] = tll->sdp[tll->noLect];

    // détermination de la zone contigüe
    if (tll->sdp[tll->noLect]>0)
        tll->zone = tll->noLect;
    if (tll->sdp[tll->noLect+1]>0)
        tll->zone = tll->noLect*11+1;
    if (tll->sdp[tll->noLect-1]>0)
        tll->zone = (tll->noLect-1)*11+1;
    ui->lZone->setText(QString("Zone %1").arg(tll->zone));
} // method

///////////////////////////////////////////////////////////////
void MainWindow::calculerDroite(int sens, T_Point pointA, T_Point pointB, T_Point *pointF)
{
    float dx, dy, a, x, y;

    dx = pointB.x - pointA.x;
    dy = pointB.y - pointA.y;

    x = sens*dx/100;  // mise à l'échelle
    a = dy/dx;     // coeff directeur, pas d'ordonnée à l'origine car changement de repère
    y = a*x;   // équation de la droite
    pointF->x = pointA.x + x;
    pointF->y = pointA.y + y;
} // methode



///////////////////////////////////////////////////////////////
int MainWindow::calculerMoyenne(T_ListeLabel *tll)
{
    // calcul de la moyenne de la sensibilité
    int sumMoy=0;
    for (int i=0 ; i<config.maxVal ; i++)
        sumMoy += tll->moySens[tll->noLect][i];
    return sumMoy / config.maxVal;

} // method

///////////////////////////////////////////////////////////
void MainWindow::onTimerMouv() {
    T_ListeLabel *tll;
    int nbB = listeLabel.size();
    for (int i=0 ; i<nbB ; i++) {
        tll = listeLabel.at(i);
        if (!tll->wdm->isActive()) {
            tll->etat |= MOUV;   // homme en danger
        } // if trouvé
    } // for
} // method

///////////////////////////////////////////////////////////
void MainWindow::onTimerRec() {
    T_ListeLabel *tll;
    int nbB = listeLabel.size();
    for (int i=0 ; i<nbB ; i++) {
        tll = listeLabel.at(i);
        for (int j=1 ; j<config.maxLect ; j++) {
            if (tll->wdr[j])
                if (!tll->wdr[j]->isActive() && bdd->isLecteurExiste(j)) {
                    ui->teRecu->append(QString::fromUtf8("Perte de réception du badge ")+QString("%1").arg(tll->noBadge,0,16));
                    tll->wdm->stop();  // arrêt du timer mouvement
                    tll->etat |= REC;
                    bdd->perteDuBadge(tll->noBadge, j);
                    // maj tableaux pour sens de passage
                    tll->sdp[j] = 0;
                    tll->memSdp[j] = 0;
                } // if trouvé
        } // for j
    } // for i
} // method

///////////////////////////////////////////////////////////
void MainWindow::onFinConnexionClient() {
} // method


///////////////////////////////////////////////////////////
void MainWindow::onTraiterTag(QString tag) {
    if (!traitement(tag)){
        qDebug("Pb trame !");
           ui->teRecu->append(tag);
    } // if decode
} // method

///////////////////////////////////////////////////////////
void MainWindow::onGererThread()
{
    T_Thread *th;
    QString adr;

    th = new T_Thread;
    cl = serv->nextPendingConnection();
    adr = cl->peerAddress().toString();
    ui->teRecu->append(adr);
    th->noLect = bdd->getNoLecteur(adr); // retrouve le no en fonction de l'adresse
    cl->readAll(); // vide le buffer
    th->thcl = new CThreadClient(this,cl);  // mémorisation dans la liste des lecteurs
    connect(th->thcl, SIGNAL(terminated()), this, SLOT(onEffacerUnThread()));
    connect(th->thcl, SIGNAL(dataLue(QString)), this, SLOT(onTraiterTag(QString)));
    th->thcl->start();
    lecteurs.append(th);  // ajout a la liste de mémorisation des lecteurs
    nbLect++;
    bdd->LecteurEnService(th->noLect); // maj BDD
    // IHM
    ui->lNbL->setText(QString("%1").arg(nbLect));
    afficherLecteur(th->noLect, true);
} // MainWindow::method

void MainWindow::toutEteindreIhm() {
/*    T_ListeLabel *tll;
    int nbB = listeLabel.size();

    for (int i=0 ; i<nbB ; i++) {
      tll = listeLabel.at(i);
      tll->l->setVisible(false);
    } // for
*/
} // method

/////////////////////////////////////////////////////////////
void MainWindow::on_menuBadgesAffecter()
{
    ihmAffecter->show();
} // method

void MainWindow::on_menuParametrer_triggered()
{
    ihmParametrer->show(); // termine l'application
} // method

void MainWindow::on_menuQuitter_triggered()
{
    this->close(); // termine l'application
} // method

void MainWindow::on_menuGerer_les_personnes_triggered()
{
    ihmPersonne->show();
} // method

void MainWindow::on_menuGerer_les_lecteurs_triggered()
{
//    ihmLecteur->show();
} // method

void MainWindow::on_menuGerer_les_badges_triggered()
{
//    ihmBadge->show();
} // method

void MainWindow::on_menuGerer_les_cameras_triggered()
{
//    ihmCamera->show();
} // method

void MainWindow::on_tbVueC_clicked()
{
// ui->twOnglets->setCurrentIndex(1);
// vue=1;
}

void MainWindow::on_tbVueSG_clicked()
{
//  ui->twOnglets->setCurrentIndex(2);
//  vue=2;
}

void MainWindow::on_tbVueGAS_clicked()
{
//  ui->twOnglets->setCurrentIndex(3);
//  vue=3;
}

void MainWindow::on_tbVueCapsule_clicked()
{
//  ui->twOnglets->setCurrentIndex(4);
//  vue=4;
}

void MainWindow::on_pbRetour_clicked()
{
  ui->twOnglets->setCurrentIndex(0);
  vue=0;
}

void MainWindow::on_twOnglets_currentChanged(int index)
{
// T_ListeLabel *tll;

//    vue=index;
//    toutEteindreIhm();
/*
    // affichage des badges non reçus
    int nb = bdd->lirePertes(vue);
    int nbB = listeLabel.size();
    if (nb>0) {
      for (int i=0 ; i<nb ; i++) {
          bdd->query->next();
          for (int j=0 ; j<nbB ; j++) {
             tll = listeLabel.at(j);
             if (bdd->query->value(1).toInt() == tll->noBadge) {
                 QString lect=QString("%1").arg(tll->noLect,0,16);
                 if (bdd->infoDeCeLecteur(lect,vue)) {
                    int x = bdd->query->value(0).toInt();
                    int y = bdd->query->value(1).toInt();
                    tll->l->setGeometry(x+(j*20),y,20,20);
                    tll->l->setVisible(true);
                 } // if bdd
                 break;
             } // if trouvé
          } // for j
      } // for i
    } // if nb
    */
} // method
