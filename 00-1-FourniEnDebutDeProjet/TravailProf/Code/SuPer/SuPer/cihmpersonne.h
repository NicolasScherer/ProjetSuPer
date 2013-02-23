#ifndef CIHMPERSONNE_H
#define CIHMPERSONNE_H

#include <QDialog>
#include "cbdd.h"
#include "commun.h"

namespace Ui {
    class CIhmPersonne;
}

class CIhmPersonne : public QDialog
{
    Q_OBJECT

public:
    explicit CIhmPersonne(QWidget *parent = 0);
    ~CIhmPersonne();

private slots:
    void on_buttonBox_rejected();
    void on_cbListe_activated(int index);
    void on_buttonBox_accepted();

    void on_pbEffacer_clicked();

private:
    Ui::CIhmPersonne *ui;
    CBdd *bdd;
    int nbPers;
};

#endif // CIHMPERSONNE_H
