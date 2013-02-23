#ifndef CIHMAFFECTER_H
#define CIHMAFFECTER_H

#include <QDialog>
#include <QString>
#include <QListWidgetItem>
#include "cbdd.h"

namespace Ui {
    class CIhmAffecter;
}

class CIhmAffecter : public QDialog
{
    Q_OBJECT

public:
    explicit CIhmAffecter(QWidget *parent = 0);
    ~CIhmAffecter();

private slots:
    void onListBoxClicked(int row);
private:
    Ui::CIhmAffecter *ui;
    CBdd *bdd;
};

#endif // CIHMAFFECTER_H
