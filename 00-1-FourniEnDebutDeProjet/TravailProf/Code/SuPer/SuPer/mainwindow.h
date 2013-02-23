#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>
#include <QTimer>

#include "cihmpersonne.h"
#include "cihmcamera.h"
#include "cihmlecteur.h"
#include "cihmbadge.h"
#include "cihmaffecter.h"
#include "cbdd.h"
#include "commun.h"
#include "cthreadclient.h"
#include "cihmparametrer.h"

//#include "cmsg.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_menuQuitter_triggered();
    void on_menuGerer_les_personnes_triggered();
    void on_menuGerer_les_badges_triggered();
    void on_menuGerer_les_lecteurs_triggered();
    void on_menuGerer_les_cameras_triggered();
    void on_menuParametrer_triggered();
    void on_menuBadgesAffecter();
    void on_tbVueC_clicked();
    void on_tbVueSG_clicked();
    void on_tbVueGAS_clicked();
    void on_tbVueCapsule_clicked();
    void on_pbRetour_clicked();
    void on_twOnglets_currentChanged(int index);
    void on_affichage();

public slots:
    void onGererThread();
    void onFinConnexionClient();
    void onTimerMouv();
    void onTimerRec();
    void onTraiterTag(QString tag);
    void onEffacerUnThread();

private:
    Ui::MainWindow *ui;
    bool traitement(QString &trame);
    void toutEteindreIhm();
    void afficherLecteur(int noL, bool etat);
    int calculerMoyenne(T_ListeLabel *tll);
    void calculerDroite(int sens, T_Point pointA, T_Point pointB, T_Point *pointF);
    void sensDePassage(T_ListeLabel *tll);

    CIhmPersonne *ihmPersonne;
    CIhmBadge *ihmBadge;
    CIhmCamera *ihmCamera;
    CIhmLecteur *ihmLecteur;
    CIhmAffecter *ihmAffecter;
    CIhmParametrer *ihmParametrer;

    QTcpServer *serv;
    QTcpSocket *cl;
    bool appli; // si SuPer doit continuer après identification.
    CBdd *bdd;
    QList<T_ListeLabel *> listeLabel;
    QList<T_Thread *> lecteurs;   // pointeur vers les différents lecteurs
    quint64 nbT; // compte le nbre de trame recu
    int nbB;
    quint8 nbLect;  // nombre de lecteur connectés
    int vue;   // image affichée sur lfond
    QTimer *aff;
    T_Config config;
//    CMsg *msg; // classe gérant la file de message
};

#endif // MAINWINDOW_H

