/********************************************************************************
** Form generated from reading UI file 'configurer.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGURER_H
#define UI_CONFIGURER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Configurer
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_6;
    QListView *listView;
    QPushButton *btAffLog;
    QPushButton *btSuppLog;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QTableWidget *tableWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Configurer)
    {
        if (Configurer->objectName().isEmpty())
            Configurer->setObjectName(QString::fromUtf8("Configurer"));
        Configurer->resize(970, 441);
        centralwidget = new QWidget(Configurer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 10, 971, 361));
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        listView = new QListView(tab_6);
        listView->setObjectName(QString::fromUtf8("listView"));
        listView->setGeometry(QRect(370, 0, 561, 331));
        btAffLog = new QPushButton(tab_6);
        btAffLog->setObjectName(QString::fromUtf8("btAffLog"));
        btAffLog->setGeometry(QRect(200, 40, 140, 30));
        btSuppLog = new QPushButton(tab_6);
        btSuppLog->setObjectName(QString::fromUtf8("btSuppLog"));
        btSuppLog->setGeometry(QRect(190, 250, 171, 30));
        label = new QLabel(tab_6);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 255, 141, 16));
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(tab_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 270, 141, 16));
        label_2->setTextFormat(Qt::AutoText);
        label_3 = new QLabel(tab_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 285, 201, 16));
        label_4 = new QLabel(tab_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 240, 71, 16));
        QFont font;
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_4->setFont(font);
        tableWidget = new QTableWidget(tab_6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(90, 80, 256, 131));
        tabWidget->addTab(tab_6, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tabWidget->addTab(tab_5, QString());
        Configurer->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Configurer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 970, 20));
        Configurer->setMenuBar(menubar);
        statusbar = new QStatusBar(Configurer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        Configurer->setStatusBar(statusbar);

        retranslateUi(Configurer);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Configurer);
    } // setupUi

    void retranslateUi(QMainWindow *Configurer)
    {
        Configurer->setWindowTitle(QApplication::translate("Configurer", "MainWindow", 0, QApplication::UnicodeUTF8));
        btAffLog->setText(QApplication::translate("Configurer", "Obtenir Historique", 0, QApplication::UnicodeUTF8));
        btSuppLog->setText(QApplication::translate("Configurer", "Vider l'Historique", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Configurer", "Cette action entraine", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Configurer", "une suppression totale", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Configurer", "de l'historique des \303\251v\303\251nements.", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Configurer", "Attention", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("Configurer", "Historique des \303\251v\303\251nements", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Configurer", "Affecter/D\303\251safecter Badge \303\240 une Personne", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Configurer", "Configuer Personne", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Configurer", "Configurer Badge", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("Configurer", "Configurer Lecteur", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("Configurer", "Configurer SuPer", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Configurer: public Ui_Configurer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGURER_H
