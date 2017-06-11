/********************************************************************************
** Form generated from reading UI file 'MyGlCanvas.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYGLCANVAS_H
#define UI_MYGLCANVAS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MyGlCanvas
{
public:

    void setupUi(QWidget *MyGlCanvas)
    {
        if (MyGlCanvas->objectName().isEmpty())
            MyGlCanvas->setObjectName(QString::fromUtf8("MyGlCanvas"));
        MyGlCanvas->resize(400, 300);

        retranslateUi(MyGlCanvas);

        QMetaObject::connectSlotsByName(MyGlCanvas);
    } // setupUi

    void retranslateUi(QWidget *MyGlCanvas)
    {
        MyGlCanvas->setWindowTitle(QApplication::translate("MyGlCanvas", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MyGlCanvas: public Ui_MyGlCanvas {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYGLCANVAS_H
