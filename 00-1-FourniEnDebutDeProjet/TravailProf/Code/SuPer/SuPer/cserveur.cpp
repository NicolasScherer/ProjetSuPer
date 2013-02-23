#include "cserveur.h"

CServeur::CServeur(QObject *parent) :
    QThread(parent)
{
    server = new QTcpServer(this);
}

//////////////////////////////////////////////////////
CServeur::~CServeur()
{
    delete server;
    delete client;
} // method


///////////////////////////////////////////////////////
void CServeur::run()
 {
    if (!server->listen(QHostAddress::Any, 2222))
        qDebug("Erreur listen.");
    connect(server, SIGNAL(newConnection()), this, SLOT(gererClient()));
    exec(); // démarrage de la boucle d'événements
}

////////////////////////////////////////////////////////
void CServeur::gererClient()
{
 client = server->nextPendingConnection();
 qDebug("Connexion reçue.");
 delete client;
} // method
