/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "myglcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButtonRoomLink;
    QPushButton *pushButtonRefresh;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonEndCall;
    QPushButton *pushButton_Stop;
    QCheckBox *checkBoxQuality;
    QPushButton *pushButtonMuteCamera;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_MuteStatusVideo;
    QLabel *label_Router;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_CallStatus;
    QTextEdit *textEditPaticipantIndex;
    QLabel *label_MuteStatusMic;
    QPushButton *pushButtonStatistics;
    MyGlCanvas *openGLWidget1;
    MyGlCanvas *openGLWidget2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(924, 935);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(20, 20, 351, 181));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButtonRoomLink = new QPushButton(gridLayoutWidget);
        pushButtonRoomLink->setObjectName(QString::fromUtf8("pushButtonRoomLink"));

        gridLayout->addWidget(pushButtonRoomLink, 2, 0, 1, 1);

        pushButtonRefresh = new QPushButton(gridLayoutWidget);
        pushButtonRefresh->setObjectName(QString::fromUtf8("pushButtonRefresh"));

        gridLayout->addWidget(pushButtonRefresh, 4, 0, 1, 1);

        pushButtonStart = new QPushButton(gridLayoutWidget);
        pushButtonStart->setObjectName(QString::fromUtf8("pushButtonStart"));
        pushButtonStart->setEnabled(true);

        gridLayout->addWidget(pushButtonStart, 0, 0, 1, 1);

        pushButtonEndCall = new QPushButton(gridLayoutWidget);
        pushButtonEndCall->setObjectName(QString::fromUtf8("pushButtonEndCall"));

        gridLayout->addWidget(pushButtonEndCall, 3, 0, 1, 1);

        pushButton_Stop = new QPushButton(gridLayoutWidget);
        pushButton_Stop->setObjectName(QString::fromUtf8("pushButton_Stop"));

        gridLayout->addWidget(pushButton_Stop, 1, 0, 1, 1);

        checkBoxQuality = new QCheckBox(gridLayoutWidget);
        checkBoxQuality->setObjectName(QString::fromUtf8("checkBoxQuality"));

        gridLayout->addWidget(checkBoxQuality, 6, 0, 1, 1);

        pushButtonMuteCamera = new QPushButton(gridLayoutWidget);
        pushButtonMuteCamera->setObjectName(QString::fromUtf8("pushButtonMuteCamera"));

        gridLayout->addWidget(pushButtonMuteCamera, 5, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QString::fromUtf8("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(380, 20, 521, 181));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_MuteStatusVideo = new QLabel(gridLayoutWidget_2);
        label_MuteStatusVideo->setObjectName(QString::fromUtf8("label_MuteStatusVideo"));

        gridLayout_2->addWidget(label_MuteStatusVideo, 7, 0, 1, 1);

        label_Router = new QLabel(gridLayoutWidget_2);
        label_Router->setObjectName(QString::fromUtf8("label_Router"));

        gridLayout_2->addWidget(label_Router, 8, 0, 1, 1);

        label = new QLabel(gridLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 5, 0, 1, 1);

        label_CallStatus = new QLabel(gridLayoutWidget_2);
        label_CallStatus->setObjectName(QString::fromUtf8("label_CallStatus"));

        gridLayout_2->addWidget(label_CallStatus, 2, 0, 1, 1);

        textEditPaticipantIndex = new QTextEdit(gridLayoutWidget_2);
        textEditPaticipantIndex->setObjectName(QString::fromUtf8("textEditPaticipantIndex"));

        gridLayout_2->addWidget(textEditPaticipantIndex, 3, 0, 1, 1);

        label_MuteStatusMic = new QLabel(gridLayoutWidget_2);
        label_MuteStatusMic->setObjectName(QString::fromUtf8("label_MuteStatusMic"));

        gridLayout_2->addWidget(label_MuteStatusMic, 6, 0, 1, 1);

        pushButtonStatistics = new QPushButton(gridLayoutWidget_2);
        pushButtonStatistics->setObjectName(QString::fromUtf8("pushButtonStatistics"));

        gridLayout_2->addWidget(pushButtonStatistics, 4, 0, 1, 1);

        openGLWidget1 = new MyGlCanvas(centralWidget);
        openGLWidget1->setObjectName(QString::fromUtf8("openGLWidget1"));
        openGLWidget1->setGeometry(QRect(20, 220, 1280, 720));
        openGLWidget2 = new MyGlCanvas(centralWidget);
        openGLWidget2->setObjectName(QString::fromUtf8("openGLWidget2"));
        openGLWidget2->setGeometry(QRect(600, 700, 320, 180));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 924, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButtonRoomLink->setText(QApplication::translate("MainWindow", "RoomLink", 0, QApplication::UnicodeUTF8));
        pushButtonRefresh->setText(QApplication::translate("MainWindow", "Refresh", 0, QApplication::UnicodeUTF8));
        pushButtonStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        pushButtonEndCall->setText(QApplication::translate("MainWindow", "EndCall", 0, QApplication::UnicodeUTF8));
        pushButton_Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        checkBoxQuality->setText(QApplication::translate("MainWindow", "Quality High", 0, QApplication::UnicodeUTF8));
        pushButtonMuteCamera->setText(QApplication::translate("MainWindow", "MuteCamera", 0, QApplication::UnicodeUTF8));
        label_MuteStatusVideo->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_Router->setText(QApplication::translate("MainWindow", "Mute Status Video", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Call status", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Mute Status Mic", 0, QApplication::UnicodeUTF8));
        label_CallStatus->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_MuteStatusMic->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
        pushButtonStatistics->setText(QApplication::translate("MainWindow", "Statistics", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
