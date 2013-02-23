#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHostAddress>
#include <QLineEdit>
#include <QMessageBox>
#include <cstdlib>  // qsrand, qrand

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QTcpSocket(this);
    connect(client, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(on_Error(QAbstractSocket::SocketError)));
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_Timer()));
    sens = 0;
} // method

MainWindow::~MainWindow()
{
    delete client;
     delete timer;
    delete ui;
} // method

void MainWindow::on_Error(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
       case QAbstractSocket::RemoteHostClosedError:
           break;
       case QAbstractSocket::HostNotFoundError:
           QMessageBox::information(this, tr("Fortune Client"),
                                    tr("The host was not found. Please check the "
                                       "host name and port settings."));
           break;
       case QAbstractSocket::ConnectionRefusedError:
           QMessageBox::information(this, tr("Fortune Client"),
                                    tr("The connection was refused by the peer. "
                                       "Make sure the fortune server is running, "
                                       "and check that the host name and port "
                                       "settings are correct."));
           break;
       default:
           QMessageBox::information(this, tr("Fortune Client"),
                                    tr("The following error occurred: %1.")
                                    .arg(client->errorString()));
       }
} // method

void MainWindow::on_pbConnecter_clicked()
{
    client->abort();
    client->connectToHost(QHostAddress(ui->leAdresse->text()), ui->lePort->text().toInt());

} // method

void MainWindow::on_pbEnvoyerToujours_clicked()
{
    timer->setInterval(ui->leFreq->text().toInt());
    timer->start();
} // method

void MainWindow::on_Timer()
{
//    if (sens > 200)
//        sens = 0;
//    sens += 10;
//    QString sSens = QString("%1").arg(sens,2,16,'0');
//    QString nouv = ui->leTrame->text();
//    nouv.replace(1,2,sSens);
    client->write(ui->leTrame->text().toLocal8Bit().data());
} // method


void MainWindow::on_pbStop_clicked()
{
    timer->stop();
} // method

void MainWindow::on_pbEnvoyer1X_clicked()
{
    client->write(ui->leTrame->text().toLocal8Bit().data());
}  // method
