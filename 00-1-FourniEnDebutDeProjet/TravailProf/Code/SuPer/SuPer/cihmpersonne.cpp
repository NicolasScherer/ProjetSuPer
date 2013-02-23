#include "cihmpersonne.h"
#include "ui_cihmpersonne.h"

CIhmPersonne::CIhmPersonne(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIhmPersonne)
{
    ui->setupUi(this);
    bdd = new CBdd(this);
    nbPers = bdd->ListeDesPersonnes();
    ui->cbListe->addItem("Nouvelle personne");
    if (nbPers > 0)
    {
      while (bdd->query->next()) {
        QString nom = bdd->query->value(1).toString();
        QString pnom = bdd->query->value(2).toString();
        ui->cbListe->addItem(nom+" "+pnom);
      } // while
    } // if nbPers
    ui->fIdent->hide();
} // method

CIhmPersonne::~CIhmPersonne()
{
    delete ui;
    delete bdd;
} // method

void CIhmPersonne::on_buttonBox_rejected()
{
    close();
} // method

void CIhmPersonne::on_cbListe_activated(int index)
{
    T_Pers pers;

    if (index > 0) {
      index--;
      // recherche du noPers sélectionné
      bdd->query->first();
      bdd->query->seek(index);
      // extraction du res de la req
      pers.nom = bdd->query->value(1).toString();
      pers.pnom = bdd->query->value(2).toString();
      pers.societe = bdd->query->value(3).toString();
      pers.dateDeb = bdd->query->value(4).toString();
      pers.dateFin = bdd->query->value(5).toString();
      pers.noPers = bdd->query->value(6).toInt();
      pers.email = bdd->query->value(7).toString();
      pers.ident = bdd->query->value(8).toString();
      pers.pass = bdd->query->value(9).toString();
      pers.exploit = bdd->query->value(10).toString();
      // affichage
      ui->leNom->setText(pers.nom);
      ui->lePnom->setText(pers.pnom);
      ui->leSociete->setText(pers.societe);
      ui->leDateDeb->setText(pers.dateDeb);
      ui->leDateFin->setText(QString(pers.dateFin));
      ui->leNoPers->setText(QString("%1").arg(pers.noPers, 0, 10));
      ui->leEmail->setText(pers.email);
      if (pers.exploit == "Y") {
          ui->rbExploitOui->setChecked(true);
          ui->fIdent->setVisible(true);
          ui->leLogin->setText(pers.ident);
          ui->lePass->setText(pers.pass);
      } // if exploit
      else {
          ui->rbExploitNon->setChecked(true);
          ui->fIdent->setVisible(false);
      } // else

      ui->pbEffacer->setEnabled(true);
    } // if index
    else { // nouvelle personne
        ui->leNom->setText("");
        ui->lePnom->setText("");
        ui->leSociete->setText("");
        ui->leDateDeb->setText("");
        ui->leDateFin->setText("");
        ui->leNoPers->setText("");
        ui->leEmail->setText("");
        ui->fIdent->setVisible(false);
        ui->rbExploitNon->setChecked(true);
    } // else
} // method

void CIhmPersonne::on_buttonBox_accepted()
{
    T_Pers pers;

    pers.nom = ui->leNom->text();
    pers.pnom = ui->lePnom->text();
    pers.societe = ui->leSociete->text();
    pers.dateDeb = ui->leDateDeb->text();
    pers.dateFin = ui->leDateFin->text();
    pers.email = ui->leEmail->text();
    if (pers.exploit == "Y") {
        pers.exploit = "Y";
        pers.ident = ui->leLogin->text();
        pers.pass = ui->lePass->text();
    } // if exploit
    else {
        pers.exploit = "N";
    } // else

    if (ui->cbListe->currentIndex() > 0) {
      // extraction du formulaire
      pers.noPers = ui->leNoPers->text().toInt();

      // sauvegarde dans la base de données
      if (!bdd->majPersonne(&pers)) {  // maj de la personne
          qDebug("Erreur de maj de la personne");
      } // if maj
    } // if index
    else
    { // creation de la personne
        pers.noPers = bdd->getNoPersSuivant();
        // sauvegarde dans la base de données
        if (!bdd->addPersonne(&pers)) {  // maj de la personne
            qDebug("Erreur de creation de la personne");
        } // if maj
    } // else
} // method

void CIhmPersonne::on_pbEffacer_clicked()
{
    T_Pers pers;

    pers.noPers = ui->leNoPers->text().toInt();
    // efface la personne dans la base de données
    if (!bdd->effPersonne(&pers)) {
        qDebug("Erreur eff de la personne");
    } // if maj
    close();
}
