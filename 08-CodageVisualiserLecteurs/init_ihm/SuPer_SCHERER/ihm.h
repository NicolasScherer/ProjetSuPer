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

    //onglet dynamique
    void ajoutOnglet(int num_vue, QString legende, QString image);
    int getVueMax();    //lié à BDD

    //BDD
    QSqlQuery * query;
    QSqlDatabase  database;

    //activitée lecteur
    void lecteurActif(int num_lecteur);
    void lecteurInactif(int num_lecteur);
    void lecteurInconnu();
};

#endif // IHM_H
