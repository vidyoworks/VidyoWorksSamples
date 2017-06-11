/********************************************************************************
** Form generated from reading UI file 'vsroomlink.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VSROOMLINK_H
#define UI_VSROOMLINK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VsRoomLink
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEditPortalName;
    QLineEdit *lineEditRoomKey;
    QLineEdit *lineEditDisplayName;
    QLineEdit *lineEditPin;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VsRoomLink)
    {
        if (VsRoomLink->objectName().isEmpty())
            VsRoomLink->setObjectName(QString::fromUtf8("VsRoomLink"));
        VsRoomLink->resize(400, 300);
        verticalLayoutWidget = new QWidget(VsRoomLink);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 20, 361, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEditPortalName = new QLineEdit(verticalLayoutWidget);
        lineEditPortalName->setObjectName(QString::fromUtf8("lineEditPortalName"));

        verticalLayout->addWidget(lineEditPortalName);

        lineEditRoomKey = new QLineEdit(verticalLayoutWidget);
        lineEditRoomKey->setObjectName(QString::fromUtf8("lineEditRoomKey"));

        verticalLayout->addWidget(lineEditRoomKey);

        lineEditDisplayName = new QLineEdit(verticalLayoutWidget);
        lineEditDisplayName->setObjectName(QString::fromUtf8("lineEditDisplayName"));

        verticalLayout->addWidget(lineEditDisplayName);

        lineEditPin = new QLineEdit(verticalLayoutWidget);
        lineEditPin->setObjectName(QString::fromUtf8("lineEditPin"));
        lineEditPin->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(lineEditPin);

        buttonBox = new QDialogButtonBox(verticalLayoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(VsRoomLink);
        QObject::connect(buttonBox, SIGNAL(accepted()), VsRoomLink, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VsRoomLink, SLOT(reject()));

        QMetaObject::connectSlotsByName(VsRoomLink);
    } // setupUi

    void retranslateUi(QDialog *VsRoomLink)
    {
        VsRoomLink->setWindowTitle(QApplication::translate("VsRoomLink", "Dialog", 0, QApplication::UnicodeUTF8));
        lineEditPortalName->setText(QString());
        lineEditPortalName->setPlaceholderText(QApplication::translate("VsRoomLink", "Portal eg http://myportal.com", 0, QApplication::UnicodeUTF8));
        lineEditRoomKey->setText(QString());
        lineEditRoomKey->setPlaceholderText(QApplication::translate("VsRoomLink", "Room key", 0, QApplication::UnicodeUTF8));
        lineEditDisplayName->setText(QString());
        lineEditDisplayName->setPlaceholderText(QApplication::translate("VsRoomLink", "Display name", 0, QApplication::UnicodeUTF8));
        lineEditPin->setPlaceholderText(QApplication::translate("VsRoomLink", "Pin", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VsRoomLink: public Ui_VsRoomLink {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VSROOMLINK_H
