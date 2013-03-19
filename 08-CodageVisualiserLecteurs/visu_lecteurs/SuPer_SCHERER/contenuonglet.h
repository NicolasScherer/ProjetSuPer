#ifndef CONTENUONGLET_H
#define CONTENUONGLET_H

#include <QWidget>
#include <QString>
#include <QLabel>

class ContenuOnglet : public QWidget
{
    Q_OBJECT
public:
    explicit ContenuOnglet(QWidget *parent = 0, QString image="default");
    
signals:
    
public slots:
    
};

#endif // CONTENUONGLET_H
