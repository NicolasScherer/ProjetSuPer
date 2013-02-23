#ifndef CIHMPARAMETRER_H
#define CIHMPARAMETRER_H

#include <QDialog>
#include "cbdd.h"

namespace Ui {
    class CIhmParametrer;
}

class CIhmParametrer : public QDialog
{
    Q_OBJECT

public:
    explicit CIhmParametrer(QWidget *parent = 0);
    ~CIhmParametrer();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::CIhmParametrer *ui;
    CBdd *bdd;
};

#endif // CIHMPARAMETRER_H
