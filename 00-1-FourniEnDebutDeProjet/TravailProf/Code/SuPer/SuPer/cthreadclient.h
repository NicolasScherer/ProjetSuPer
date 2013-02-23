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

private:
    QTcpSocket *client;

signals:
    void dataLue(QString str);  // avertissement réception d'un tag

public slots:
    void onLireTag();
    void onFinConnexionClient();
};

#endif // CCLIENT_H
