#include "cihmcamera.h"
#include "ui_cihmcamera.h"

CIhmCamera::CIhmCamera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CIhmCamera)
{
    ui->setupUi(this);
}

CIhmCamera::~CIhmCamera()
{
    delete ui;
}

void CIhmCamera::on_buttonBox_rejected()
{
        this->close();
}
