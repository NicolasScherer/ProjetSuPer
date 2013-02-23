#ifndef CMSG_H
#define CMSG_H

#include <QObject>
#include "commun.h"

class CMsg : public QObject
{
    Q_OBJECT
public:
    explicit CMsg(QObject *parent = 0);
    ~CMsg();

    int ajouterMsg(QString &trame);
    int lireMsg(int type, T_MSG *mess); // 0 pour n'importe quel type

signals:

public slots:

private:
    key_t key;
    int id;
};

#endif // CMSG_H
