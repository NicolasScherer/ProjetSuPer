#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serveur = new QTcpServer(this);
    nbClient=0;  // personne connecté
}

MainWindow::~MainWindow()
{
    delete serveur;
    delete ui;
    client[0]->exit();
    client[1]->exit();
    delete client[0];
    delete client[1];
}

void MainWindow::afficherClient(QString data)
{
  ui->teRec->append(data);
} // method

void MainWindow::deleteThread()
{
    if (client[0]->isFinished()) {
        delete client[0];
        qDebug("liberation thread 0");
    } // if
    if (client[1]->isFinished())  {
        delete client[1];
        qDebug("liberation thread 1");
    } // if

} // method

void MainWindow::onGererClient()
{
    if (nbClient < 2) {
        ui->teRec->append(QString("Client %1 connected").arg(nbClient+1));
        client[nbClient] = new CThreadClient(this, serveur->nextPendingConnection());
        connect(client[nbClient], SIGNAL(finished()), this, SLOT(deleteThread()));
        connect(client[nbClient], SIGNAL(dataLue(QString)), this, SLOT(afficherClient(QString)));
        client[nbClient]->start();   // lancement du Thread de gestion du client.
        nbClient++;
    } // if nbClient
    else {
        ui->teRec->append("Nb client max atteint !");
        QTcpSocket *ac = serveur->nextPendingConnection();
        ac->close();
    } // else
} // method

void MainWindow::on_pbConnecter_clicked()
{
    serveur = new QTcpServer(this);
    serveur->listen(QHostAddress::Any, 2223);
    connect(serveur, SIGNAL(newConnection()), this, SLOT(onGererClient()));
    connect(serveur, SIGNAL(destroyed()), serveur, SLOT(deleteLater()));
    ui->pbConnecter->setEnabled(false);
}
