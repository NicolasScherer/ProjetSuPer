#ifndef FIDENT_H
#define FIDENT_H

#include <QDialog>
#include <QDesktopWidget>
#include "mainwindow.h"
#include "cbdd.h"

namespace Ui {
    class FIdent;
}

class FIdent : public QDialog
{
    Q_OBJECT

public:
    explicit FIdent(QWidget *parent = 0);
    ~FIdent();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::FIdent *ui;
    MainWindow *ihm;
    CBdd *bdd;
};

#endif // FIDENT_H
