#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QStatusBar>
#include <QTimer>
#include <QLatin1Char>

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
    void onClientConnected();
    void onLireData();
    void displayError(QAbstractSocket::SocketError);
    void on_pbEnvoyer_clicked();
    void on_pb0Mouv_clicked();

    void on_pbAuto_clicked();

    void on_pbStop_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *cl;
    QTimer *timer;
};

#endif // MAINWINDOW_H
