#ifndef CIHMCAMERA_H
#define CIHMCAMERA_H

#include <QDialog>
#include "cbdd.h"
#include "commun.h"

namespace Ui {
    class CIhmCamera;
}

class CIhmCamera : public QDialog
{
    Q_OBJECT

public:
    explicit CIhmCamera(QWidget *parent = 0);
    ~CIhmCamera();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::CIhmCamera *ui;
};

#endif // CIHMCAMERA_H
