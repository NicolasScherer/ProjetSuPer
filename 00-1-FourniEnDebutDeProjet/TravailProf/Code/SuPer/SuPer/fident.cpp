#include "fident.h"
#include "ui_fident.h"

FIdent::FIdent(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FIdent)
{
    ui->setupUi(this);
}

FIdent::~FIdent()
{
    delete ui;
}

void FIdent::on_buttonBox_rejected()
{
    close();
}

void FIdent::on_buttonBox_accepted()
{
    bool ret=false;
    bdd = new CBdd(this);
    ret = bdd->identifier(ui->leIdent->text(), ui->lePass->text());
    if (ret)
    {
      ihm = new MainWindow();
//      QDesktopWidget *a = qApp->desktop();
//      ihm->move(a->width()-ihm->width(),a->height()-ihm->height());
      ihm->show();
    } // if
    delete bdd;
    close();
}
