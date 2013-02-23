#include "cihmbadge.h"
#include "ui_cihmbadge.h"

CIhmBadge::CIhmBadge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIhmBadge)
{
    ui->setupUi(this);
}

/////////////////////////////////////////////////////////
CIhmBadge::~CIhmBadge()
{
    delete ui;
}

/////////////////////////////////////////////////////////
void CIhmBadge::on_buttonBox_destroyed()
{
    this->close();
}

