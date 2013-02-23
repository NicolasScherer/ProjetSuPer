#include "cihmparametrer.h"
#include "ui_cihmparametrer.h"

CIhmParametrer::CIhmParametrer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIhmParametrer)
{
    T_Config config;
    ui->setupUi(this);
    bdd = new CBdd(this);

    // init des valeur de la table config
    bdd->getConfig(&config);
    ui->lemaxLect->setText(QString("%1").arg(config.maxLect));
    ui->lemaxVal->setText(QString("%1").arg(config.maxVal));
    ui->letimeoutMouv->setText(QString("%1").arg(config.tempoM));
    ui->letimeoutRec->setText(QString("%1").arg(config.tempoR));
    ui->letimeoutAff->setText(QString("%1").arg(config.tempoA));
}

CIhmParametrer::~CIhmParametrer()
{
    delete bdd;
    delete ui;
}

void CIhmParametrer::on_buttonBox_accepted()
{
    T_Config config;

    try {
      config.tempoA = ui->letimeoutAff->text().toInt();
      config.tempoM = ui->letimeoutMouv->text().toInt();
      config.tempoR = ui->letimeoutRec->text().toInt();
      config.maxLect = ui->lemaxLect->text().toInt();
      config.maxVal = ui->lemaxVal->text().toInt();
      bdd->setConfig(&config);
    } // try
    catch(...)
    {

    } // catch
}
