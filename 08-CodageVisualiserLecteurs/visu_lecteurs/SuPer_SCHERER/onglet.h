#ifndef ONGLET_H
#define ONGLET_H

#include <QObject>
#include <QLabel>
#include <QVBoxLayout>
#include <QTabWidget>

#define MAXONGLETS 20

class Onglet : public QObject
{
    Q_OBJECT
public:
    explicit Onglet(QObject *parent = 0);
    QWidget *onglet[MAXONGLETS];
   // QVBoxLayout *layout[];
    int num_vue[];
    
signals:
    
public slots:
    
};

#endif // ONGLET_H

