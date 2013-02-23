#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cl = new QTcpSocket(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pbEnvoyer_clicked()));
    timer->setInterval(1000);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete cl;
    delete ui;
}

void MainWindow::displayError(QAbstractSocket::SocketError)
{
    statusBar()->showMessage(tr("Erreur reseau !"));
    ui->pbConnecter->setEnabled(true);
} // method

void MainWindow::onClientConnected()
{
    statusBar()->showMessage(tr("Client connected au serveur !"));
} // method

void MainWindow::onLireData()
{
} // method

void MainWindow::on_pbConnecter_clicked()
{
    cl->connectToHost(ui->leAdresse->text(), ui->lePort->text().toInt());
    connect(cl, SIGNAL(connected()), this, SLOT(clientConnnected()));
    connect(cl, SIGNAL(disconnected()), cl, SLOT(deleteLater()));
    connect(cl, SIGNAL(readyRead()), this, SLOT(lireData()));
    connect(cl, SIGNAL(error(QAbstractSocket::SocketError)),
                 this, SLOT(displayError(QAbstractSocket::SocketError)));
    ui->pbConnecter->setEnabled(false);
}

void MainWindow::on_pbEnvoyer_clicked()
{
    //cl->write(ui->teEm->toPlainText().toLocal8Bit().data());
    //cl->write("[8980000102]");
    int noLect, noSens, noMouv, noBadge;
    QString tag, buf;

    noSens = ui->sbSens->value();
    buf = QString("%1").arg(noSens,0,16);
    tag = QString("[%1").arg(buf,2,QLatin1Char('0'));

    noBadge = ui->sbNum->value();
    buf = QString("%1").arg(noBadge,0,16);
    tag += QString("%1").arg(buf,3,QLatin1Char('0'));

    noMouv = ui->sbMouv->value();
    buf = QString("%1").arg(noMouv,0,16);
    tag += QString("%1").arg(buf,3,QLatin1Char('0'));

    noLect = ui->sbLect->value();
    buf = QString("%1").arg(noLect,0,16);
    tag += QString("%1]").arg(buf,2,QLatin1Char('0'));

    cl->write(tag.toLocal8Bit().data());

}

void MainWindow::on_pb0Mouv_clicked()
{
    cl->write("[8980000002]");
}

void MainWindow::on_pbAuto_clicked()
{
    ui->pbEnvoyer->setEnabled(false);
    timer->start();
}

void MainWindow::on_pbStop_clicked()
{
    ui->pbEnvoyer->setEnabled(true);
    timer->stop();
}
