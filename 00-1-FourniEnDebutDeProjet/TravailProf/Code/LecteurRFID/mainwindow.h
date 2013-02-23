#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTimer>
#include <QString>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbConnecter_clicked();
    void on_pbEnvoyerToujours_clicked();
    void on_Timer();
    void on_Error(QAbstractSocket::SocketError socketError);
    void on_pbStop_clicked();
    void on_pbEnvoyer1X_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *client;
    QTimer *timer;
    int sens;
};

#endif // MAINWINDOW_H
