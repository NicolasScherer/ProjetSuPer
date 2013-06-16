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
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
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
    QGroupBox *groupBox;
    QTextEdit *txtAlarme;
    QLabel *label2;
    QLabel *label2_2;
    QPushButton *btClear;
    QLabel *label;
    QLabel *lbActivite;
    QGroupBox *groupBox_2;
    QLabel *addressLabel;
    QLabel *portLabel;
    QSpinBox *portSpinBox;
    QLineEdit *addressLineEdit;
    QPushButton *onPushButton;
    QPushButton *killAllComPushButton;
    QPushButton *offPushButton;
    QLabel *label_7;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_9;
    QLabel *label_8;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Ihm)
    {
        if (Ihm->objectName().isEmpty())
            Ihm->setObjectName(QString::fromUtf8("Ihm"));
        Ihm->resize(850, 840);
        Ihm->setMaximumSize(QSize(16777215, 16777215));
        centralWidget = new QWidget(Ihm);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(20, 60, 800, 610));
        tabWidget->setMaximumSize(QSize(16777215, 16777215));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 670, 801, 111));
        groupBox->setContextMenuPolicy(Qt::DefaultContextMenu);
        txtAlarme = new QTextEdit(groupBox);
        txtAlarme->setObjectName(QString::fromUtf8("txtAlarme"));
        txtAlarme->setEnabled(true);
        txtAlarme->setGeometry(QRect(70, 20, 721, 91));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        txtAlarme->setFont(font);
        txtAlarme->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ForbiddenCursor)));
        txtAlarme->setMouseTracking(false);
        txtAlarme->setAcceptDrops(true);
        txtAlarme->setReadOnly(true);
        txtAlarme->setTextInteractionFlags(Qt::NoTextInteraction);
        label2 = new QLabel(groupBox);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(20, 20, 61, 16));
        label2_2 = new QLabel(groupBox);
        label2_2->setObjectName(QString::fromUtf8("label2_2"));
        label2_2->setGeometry(QRect(10, 90, 61, 20));
        btClear = new QPushButton(groupBox);
        btClear->setObjectName(QString::fromUtf8("btClear"));
        btClear->setEnabled(false);
        btClear->setGeometry(QRect(7, 45, 65, 35));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 20, 191, 21));
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignCenter);
        lbActivite = new QLabel(centralWidget);
        lbActivite->setObjectName(QString::fromUtf8("lbActivite"));
        lbActivite->setEnabled(true);
        lbActivite->setGeometry(QRect(40, 10, 31, 31));
        lbActivite->setPixmap(QPixmap(QString::fromUtf8("ressources/activite_vert.png")));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(440, 0, 381, 61));
        addressLabel = new QLabel(groupBox_2);
        addressLabel->setObjectName(QString::fromUtf8("addressLabel"));
        addressLabel->setGeometry(QRect(15, 40, 57, 22));
        addressLabel->setAlignment(Qt::AlignCenter);
        portLabel = new QLabel(groupBox_2);
        portLabel->setObjectName(QString::fromUtf8("portLabel"));
        portLabel->setGeometry(QRect(190, 40, 45, 22));
        portLabel->setAlignment(Qt::AlignCenter);
        portSpinBox = new QSpinBox(groupBox_2);
        portSpinBox->setObjectName(QString::fromUtf8("portSpinBox"));
        portSpinBox->setGeometry(QRect(239, 40, 133, 22));
        portSpinBox->setMaximum(65535);
        portSpinBox->setValue(43210);
        addressLineEdit = new QLineEdit(groupBox_2);
        addressLineEdit->setObjectName(QString::fromUtf8("addressLineEdit"));
        addressLineEdit->setGeometry(QRect(76, 40, 110, 22));
        addressLineEdit->setText(QString::fromUtf8("127.0.0.254"));
        addressLineEdit->setAlignment(Qt::AlignCenter);
        onPushButton = new QPushButton(groupBox_2);
        onPushButton->setObjectName(QString::fromUtf8("onPushButton"));
        onPushButton->setGeometry(QRect(15, 20, 57, 23));
        killAllComPushButton = new QPushButton(groupBox_2);
        killAllComPushButton->setObjectName(QString::fromUtf8("killAllComPushButton"));
        killAllComPushButton->setGeometry(QRect(76, 20, 110, 23));
        offPushButton = new QPushButton(groupBox_2);
        offPushButton->setObjectName(QString::fromUtf8("offPushButton"));
        offPushButton->setEnabled(false);
        offPushButton->setGeometry(QRect(190, 20, 45, 23));
        offPushButton->setStyleSheet(QString::fromUtf8("background-color:red;"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(50, 160, 531, 16));
        label_7->setFont(font);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(80, 210, 481, 21));
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(80, 300, 511, 20));
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(80, 190, 481, 21));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(50, 270, 571, 16));
        QFont font1;
        font1.setBold(true);
        font1.setItalic(true);
        font1.setWeight(75);
        label_8->setFont(font1);
        Ihm->setCentralWidget(centralWidget);
        label_8->raise();
        label_9->raise();
        label_11->raise();
        label_7->raise();
        label_10->raise();
        groupBox->raise();
        label->raise();
        lbActivite->raise();
        groupBox_2->raise();
        tabWidget->raise();
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
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Ihm", "Erreur", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("Ihm", "Alarmes", 0, QApplication::UnicodeUTF8));
        label2->setText(QApplication::translate("Ihm", "r\303\251centes", 0, QApplication::UnicodeUTF8));
        label2_2->setText(QApplication::translate("Ihm", "anciennes", 0, QApplication::UnicodeUTF8));
        btClear->setText(QApplication::translate("Ihm", "Nettoyer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Ihm", "SuPer : Logiciel de Supervision", 0, QApplication::UnicodeUTF8));
        lbActivite->setText(QString());
        groupBox_2->setTitle(QApplication::translate("Ihm", "R\303\251glage du Serveur", 0, QApplication::UnicodeUTF8));
        addressLabel->setText(QApplication::translate("Ihm", "Address :", 0, QApplication::UnicodeUTF8));
        portLabel->setText(QApplication::translate("Ihm", "Port :", 0, QApplication::UnicodeUTF8));
        onPushButton->setText(QApplication::translate("Ihm", "On", 0, QApplication::UnicodeUTF8));
        killAllComPushButton->setText(QApplication::translate("Ihm", "Close all com.", 0, QApplication::UnicodeUTF8));
        offPushButton->setText(QApplication::translate("Ihm", "Off", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("Ihm", "Erreur : le logiciel n'a pu se mettre \303\240 jour en fonction de la Base de donn\303\251es.", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("Ihm", "Erreur possible : La base de donn\303\251es est vide.", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("Ihm", "Si le probl\303\250me persiste, contacter la section BTS IRIS qui a d\303\251velopp\303\251 SuPer.", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("Ihm", "Erreur possible : La base de donn\303\251es est inaccessible.", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("Ihm", "Il est vivement conseill\303\251 de regarder attentivement l'aide fournie avec le logiciel.", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Ihm: public Ui_Ihm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IHM_H
