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

private:
    Ui::Configurer *ui;

    //pointeur sur la classe BDD
    Bdd *pBdd;

    //déclaration QList
    QList<T_Personne> listePersonne;
    QList<T_Badge> listeBadge;
    QList<T_Vue> listeVue;
};

#endif // CONFIGURER_H
