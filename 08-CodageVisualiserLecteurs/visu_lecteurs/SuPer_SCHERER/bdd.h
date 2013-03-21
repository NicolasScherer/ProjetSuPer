#ifndef BDD_H
#define BDD_H

#include <QObject>
#include <QtSql>
#include <QList>

////////////////////////////
typedef struct s_Tuple {
    int num_vue;
    QString legende;
    QString image;

} T_Tuple;

///////////////////////////
class Bdd : public QObject
{
    Q_OBJECT
public:
    explicit Bdd(QObject *parent = 0);
    ~Bdd();
    QList<T_Tuple *> listeTuple;

    int getVueMax();    //obtenir vue max
    T_Tuple* getVue();   //obtenir toutes les vues
    int getVueFctLect(int numLecteur); //obtenir la vue en fonction du lecteur

private:
    QSqlQuery * query;
    QSqlDatabase  database;
    
signals:
    
public slots:
    
};

#endif // BDD_H
