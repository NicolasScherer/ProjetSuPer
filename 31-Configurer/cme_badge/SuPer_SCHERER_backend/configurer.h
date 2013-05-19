#ifndef CONFIGURER_H
#define CONFIGURER_H

#include <QMainWindow>
#include "bdd.h"

namespace Ui {
class Configurer;
}

class Configurer : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Configurer(QWidget *parent = 0);
    ~Configurer();
    
private slots:
    //slots créer avec QT
    void on_btAffLog_clicked();
    void on_btSuppLog_clicked();
    void on_btBadgeExistant_clicked();
    void on_btAnnulerLier_clicked();
    void on_btAnnulerLierMod_clicked();
    void on_btAnnulerDelier_clicked();
    void on_cBoxPersonneLier_activated(int index);
    void on_btOkLier_clicked();
    void on_cBoxLierMod_activated(int index);
    void on_btOkLierMod_clicked();
    void on_cBoxBadgeSupp_activated(int index);
    void on_btOkDelier_clicked();
    void on_btBadgeExistant_2_clicked();
    void on_btAffichage_clicked();
    void on_btAnnulerVueAdd_clicked();
    void on_btAnnulerVueMod_clicked();
    void on_btannulerVueSupp_clicked();
    void on_btVueExistante_clicked();
    void on_btOkVueAdd_clicked();
    void on_cBoxVueMod_activated(int index);
    void on_btOkVueMod_clicked();
    void on_cBoxVueSupp_activated(int index);
    void on_btOKVueSupp_clicked();
    void on_btAnnulerLieuAdd_clicked();
    void on_btAnnulerLieuMod_clicked();
    void on_btAnnulerLieuSupp_clicked();
    void on_btLieuExistant_clicked();
    void on_btOkLieuAdd_clicked();
    void on_cBoxLieuMod_activated(int index);
    void on_cBoxLieuSupp_activated(int index);
    void on_btOkLieuMod_clicked();
    void on_btOkLieuSupp_clicked();
    void on_btAnnulerZoneAdd_clicked();
    void on_btAnnulerZoneMod_clicked();
    void on_btAnnulerZoneSupp_clicked();
    void on_btVueExistante_2_clicked();
    void on_btOkZoneAdd_clicked();
    void on_cBoxZoneMod_activated(int index);
    void on_btOkZoneMod_clicked();
    void on_cBoxZoneSupp_activated(int index);
    void on_btOkZoneSupp_clicked();
    void on_cBoxPositionNumVue_activated(int index);
    void on_cBoxPositionNumZone_activated(int index);
    void on_btAnnulerPosition_clicked();
    void on_btOkPosition_clicked();
    void on_cBoxPositionSuppNumVue_activated(int index);
    void on_cBoxPositionSuppNumZone_activated(int index);
    void on_btAnnulerPositionSupp_clicked();
    void on_btOkPositionSupp_clicked();
    void on_btOkTimer_clicked();

private:
    Ui::Configurer *ui;

    //pointeur sur la classe BDD
    Bdd *pBdd;

    //déclaration QList
    QList<T_Personne> listePersonne;
    QList<T_Badge> listeBadge;
    QList<T_Vue> listeVue;
    QList<T_Lieu> listeLieu;
    QList<T_Zone> listeZone;
    QList<T_Representation> listeRepresentation;

    int etatPosition;  //attribut ajouter (1) ou modifier (0) ou erreur (-1)

   bool actuAffichage();  //méthode permettant l'actualisation de l'affichage
};

#endif // CONFIGURER_H
