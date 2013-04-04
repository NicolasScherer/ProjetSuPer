#ifndef CLIENTCONNECTION_H
#define CLIENTCONNECTION_H

#include <QObject>
#include "tcpsocket.h"
#include "reader.h"

class ClientConnection : public QObject
{
Q_OBJECT
signals:
    void sig_connected();
    void sig_isAReader(Reader);
    void sig_isNotAReader(QString);
    void sig_dataRead(QString);
    void sig_disconnected();
    void sig_closed();

public:
    explicit ClientConnection(int);
    ~ClientConnection();

public slots:
    void open();
    void close();

private:
    TcpSocket _tcpSocket;
    int _socketDescriptor;

private slots:
    void filter();
    void readyRead();
};

#endif // CLIENTCONNECTION_H
