#include "cihmaffecter.h"
#include "ui_cihmaffecter.h"

CIhmAffecter::CIhmAffecter(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIhmAffecter)
{
    QString aff;
    ui->setupUi(this);
    bdd = new CBdd(this);

    int nb = bdd->ListeDesPersonnes();
    for (int i=0 ; i<nb ; i++) {
        bdd->query->next();
        aff = bdd->query->value(1).toString()+" "+bdd->query->value(2).toString();
        ui->cbPers->addItem(aff);
    } // for

    nb=bdd->aQuiSontLesBadges();
    for (int i=0 ; i<nb ; i++) {
        aff = "Badge "+bdd->query->value(0).toString()+
                " Affected to "+bdd->query->value(1).toString()+
                " "+bdd->query->value(2).toString();
        ui->lwBadges->addItem(aff);
        bdd->query->next();
    } // for
    bdd->aQuiSontLesBadges();

    connect(ui->lwBadges, SIGNAL(currentRowChanged(int)), this, SLOT(onListBoxClicked(int)));
} // method

CIhmAffecter::~CIhmAffecter()
{
    delete bdd;
    delete ui;
}

void CIhmAffecter::onListBoxClicked(int row)
{
    if (row != -1)
    {
        bdd->query->first();
        bdd->query->seek(row);
        qDebug(bdd->query->value(1).toString().toLocal8Bit().data());
        if (bdd->query->value(1).toString().length() < 1)  {
            ui->lNonAffected->setVisible(true);
            ui->lAffected->setVisible(false);
            ui->pbAffecter->setText("Affecter");
        } // if nom vide
        else {
            ui->lNonAffected->setVisible(false);
            ui->lAffected->setVisible(true);
            ui->pbAffecter->setText(QString::fromUtf8("Désaffecter"));
        } // else vide
    } // if row
} // method
