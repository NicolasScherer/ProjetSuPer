/********************************************************************************
** Form generated from reading UI file 'ihm.ui'
**
** Created
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IHM_H
#define UI_IHM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Ihm
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QGroupBox *groupBox;
    QTextEdit *txtAlarme;
    QLabel *label2;
    QLabel *label2_2;
    QLabel *label;
    QLabel *lbActivite;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Ihm)
    {
        if (Ihm->objectName().isEmpty())
            Ihm->setObjectName(QString::fromUtf8("Ihm"));
        Ihm->resize(850, 800);
        Ihm->setMaximumSize(QSize(16777215, 16777215));
        centralWidget = new QWidget(Ihm);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(20, 50, 800, 610));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 80, 481, 21));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(60, 50, 531, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_3->setFont(font);
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(90, 100, 481, 21));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 160, 571, 16));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_5->setFont(font1);
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(90, 190, 511, 20));
        tabWidget->addTab(tab_2, QString());
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 660, 801, 111));
        groupBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        txtAlarme = new QTextEdit(groupBox);
        txtAlarme->setObjectName(QString::fromUtf8("txtAlarme"));
        txtAlarme->setEnabled(true);
        txtAlarme->setGeometry(QRect(70, 20, 721, 91));
        txtAlarme->setFont(font);
        txtAlarme->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ForbiddenCursor)));
        txtAlarme->setMouseTracking(false);
        txtAlarme->setAcceptDrops(true);
        txtAlarme->setReadOnly(true);
        txtAlarme->setTextInteractionFlags(Qt::NoTextInteraction);
        label2 = new QLabel(groupBox);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(20, 90, 61, 16));
        label2_2 = new QLabel(groupBox);
        label2_2->setObjectName(QString::fromUtf8("label2_2"));
        label2_2->setGeometry(QRect(10, 20, 61, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(60, 10, 191, 21));
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        lbActivite = new QLabel(centralWidget);
        lbActivite->setObjectName(QString::fromUtf8("lbActivite"));
        lbActivite->setEnabled(true);
        lbActivite->setGeometry(QRect(30, 0, 31, 31));
        lbActivite->setPixmap(QPixmap(QString::fromUtf8("../ressources/activite_vert.png")));
        Ihm->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Ihm);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 850, 20));
        Ihm->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Ihm);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Ihm->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Ihm);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Ihm->setStatusBar(statusBar);

        retranslateUi(Ihm);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Ihm);
    } // setupUi

    void retranslateUi(QMainWindow *Ihm)
    {
        Ihm->setWindowTitle(QApplication::translate("Ihm", "Supervision", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Ihm", "Tab 1", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("Ihm", "Erreur possible : La base de donn\303\251es est inaccessible.", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Ihm", "Erreur : le logiciel n'a pu se mettre \303\240 jour en fonction de la Base de donn\303\251es.", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Ihm", "Erreur possible : La base de donn\303\251es est vide.", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Ihm", "Il est vivement conseill\303\251 de regarder attentivement l'aide fournie avec le logiciel.", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Ihm", "Si le probl\303\250me persiste, contacter la section BTS IRIS qui a d\303\251velopp\303\251 SuPer.", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Ihm", "Erreur", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Ihm", "Alarmes", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("Ihm", "r\303\251centes", 0, QApplication::UnicodeUTF8));
        label2_2->setText(QApplication::translate("Ihm", "anciennes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Ihm", "SuPer : Logiciel de Supervision", 0, QApplication::UnicodeUTF8));
        lbActivite->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Ihm: public Ui_Ihm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHM_H
