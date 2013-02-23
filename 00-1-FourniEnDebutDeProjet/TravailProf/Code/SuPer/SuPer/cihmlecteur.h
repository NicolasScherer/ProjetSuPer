#ifndef CIHMLECTEUR_H
#define CIHMLECTEUR_H

#include <QDialog>
#include "cbdd.h"
#include "commun.h"

namespace Ui {
    class CIhmLecteur;
}

class CIhmLecteur : public QDialog
{
    Q_OBJECT

public:
    explicit CIhmLecteur(QWidget *parent = 0);
    ~CIhmLecteur();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::CIhmLecteur *ui;
};

#endif // CIHMLECTEUR_H
