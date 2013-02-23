#include "cihmlecteur.h"
#include "ui_cihmlecteur.h"

CIhmLecteur::CIhmLecteur(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIhmLecteur)
{
    ui->setupUi(this);
}

//////////////////////////////////////////////
CIhmLecteur::~CIhmLecteur()
{
    delete ui;
}

//////////////////////////////////////////////
void CIhmLecteur::on_buttonBox_rejected()
{
     this->close();
}

