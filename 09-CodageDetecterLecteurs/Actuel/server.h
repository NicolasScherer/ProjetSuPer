#ifndef SERVER_H
#define SERVER_H

#include "tcpserver.h"
#include "clientconnection.h"

class Server : public QObject
{
    Q_OBJECT

public:
    enum SwitchOnState
    {
        Success,
        AddressNotAvailableError,
        PortProtectedError,
        PortAlreadyInUseError,
        UnknownError
    };

signals:
    void sig_switchedOn();
    void sig_switchedOff();

    void sig_portChanged(quint16);
    void sig_addressChanged(QString);

    void sig_newConnection(const ClientConnection&);
    void sig_closeAllClientConnection();

public slots:
    SwitchOnState switchOn();
    void switchOff();
    bool setAddress(QString);
    bool setPort(QString);
    void closeAllClientConnection();

public:
    explicit Server(QString address, QString port, QObject *parent = 0);
    ~Server();

    QString address();
    quint16 port();

protected slots:
    void incomingConnection(int);

private:
    bool _setAddress(QString);
    bool _setPort(QString);

    QHostAddress _address;
    quint16 _port;
    TcpServer _server;
};

QDebug operator<<(QDebug, const Server::SwitchOnState&);

#endif // SERVER_H
