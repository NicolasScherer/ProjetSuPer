#ifndef CCLIENT_H
#define CCLIENT_H

#include <QThread>
#include <QTcpSocket>

class CThreadClient : public QThread
{
    Q_OBJECT
public:
    explicit CThreadClient(QObject *parent = 0, QTcpSocket *cl = 0);
    ~CThreadClient();
protected:
    void run();

signals:
    void dataLue(QString str);

public slots:
    void lireClient();
    void finConnexionClient();

private:
    QTcpSocket *client;
    int sortie;
};

#endif // CCLIENT_H
