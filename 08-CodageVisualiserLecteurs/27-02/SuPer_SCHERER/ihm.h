#ifndef IHM_H
#define IHM_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class Ihm;
}

class Ihm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit Ihm(QWidget *parent = 0);
    ~Ihm();
    
private:
    Ui::Ihm *ui;
    void ajoutOnglet(int id_rubrique);
    void legendeOnglet();
};

#endif // IHM_H
