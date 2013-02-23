#ifndef CSERVEUR_H
#define CSERVEUR_H

#include <QThread>
#include <QTcpSocket>
#include <QTcpServer>

class CServeur : public QThread
{
    Q_OBJECT
public:
    explicit CServeur(QObject *parent = 0);
    ~CServeur();
    void run();
private:
    QTcpServer *server;
    QTcpSocket *client;

signals:

public slots:
    void gererClient();
};

#endif // CSERVEUR_H
