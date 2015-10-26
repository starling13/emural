/********************************************************************************
** Form generated from reading UI file 'DisplayPanel.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYPANEL_H
#define UI_DISPLAYPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DisplayPanel
{
public:

    void setupUi(QWidget *DisplayPanel)
    {
        if (DisplayPanel->objectName().isEmpty())
            DisplayPanel->setObjectName(QString::fromUtf8("DisplayPanel"));
        DisplayPanel->resize(400, 300);

        retranslateUi(DisplayPanel);

        QMetaObject::connectSlotsByName(DisplayPanel);
    } // setupUi

    void retranslateUi(QWidget *DisplayPanel)
    {
        DisplayPanel->setWindowTitle(QApplication::translate("DisplayPanel", "DisplayPanel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DisplayPanel: public Ui_DisplayPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYPANEL_H
