#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "cthreadclient.h"

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
    void onGererClient();
    void on_pbConnecter_clicked();
    void afficherClient(QString data);
    void deleteThread();

private:
    Ui::MainWindow *ui;
    QTcpServer *serveur;
    CThreadClient *client[2];   // pour l'instant deux clients max
    int nbClient;
};

#endif // MAINWINDOW_H
