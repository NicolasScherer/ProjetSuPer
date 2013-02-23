#include "cthreadclient.h"

CThreadClient::CThreadClient(QObject *parent, QTcpSocket *cl) :
    QThread(parent)
{
 client = cl;
 sortie=0;
}

CThreadClient::~CThreadClient()
{
    qDebug("Fin Thread");
} // method


void CThreadClient::lireClient()
{
    QString data;
    data = client->readAll();
    emit(dataLue(data));
} // method

void CThreadClient::finConnexionClient()
{
    this->exit(-1);
} // method


void CThreadClient::run()
{
  connect(client, SIGNAL(readyRead()), this, SLOT(lireClient()));
  connect(client, SIGNAL(disconnected()), client, SLOT(deleteLater()));
  connect(client, SIGNAL(destroyed()), this, SLOT(finConnexionClient()));
  connect(client, SIGNAL(readyRead()), this, SLOT(lireClient()));
  exec();
} // method
