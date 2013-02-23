#ifndef CIHMBADGE_H
#define CIHMBADGE_H

#include <QDialog>
#include "cbdd.h"
#include "commun.h"

namespace Ui {
    class CIhmBadge;
}

class CIhmBadge : public QDialog
{
    Q_OBJECT

public:
    explicit CIhmBadge(QWidget *parent = 0);
    ~CIhmBadge();

private slots:
    void on_buttonBox_destroyed();

private:
    Ui::CIhmBadge *ui;
};

#endif // CIHMBADGE_H
