/********************************************************************************
** Form generated from reading UI file 'DrumWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRUMWIDGET_H
#define UI_DRUMWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DrumWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *octSwitch;
    QRadioButton *binSwitch;
    QPushButton *clearButton;
    QHBoxLayout *horizontalLayout_2;
    QTableWidget *drumView;
    QScrollBar *drumScroll;
    QButtonGroup *formatGroup;

    void setupUi(QWidget *DrumWidget)
    {
        if (DrumWidget->objectName().isEmpty())
            DrumWidget->setObjectName(QString::fromUtf8("DrumWidget"));
        DrumWidget->resize(306, 645);
        verticalLayout = new QVBoxLayout(DrumWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(DrumWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        octSwitch = new QRadioButton(groupBox);
        formatGroup = new QButtonGroup(DrumWidget);
        formatGroup->setObjectName(QString::fromUtf8("formatGroup"));
        formatGroup->addButton(octSwitch);
        octSwitch->setObjectName(QString::fromUtf8("octSwitch"));
        octSwitch->setChecked(true);

        horizontalLayout->addWidget(octSwitch);

        binSwitch = new QRadioButton(groupBox);
        formatGroup->addButton(binSwitch);
        binSwitch->setObjectName(QString::fromUtf8("binSwitch"));

        horizontalLayout->addWidget(binSwitch);


        verticalLayout->addWidget(groupBox);

        clearButton = new QPushButton(DrumWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        verticalLayout->addWidget(clearButton);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        drumView = new QTableWidget(DrumWidget);
        if (drumView->columnCount() < 2)
            drumView->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        drumView->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        drumView->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        drumView->setObjectName(QString::fromUtf8("drumView"));
        drumView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        horizontalLayout_2->addWidget(drumView);

        drumScroll = new QScrollBar(DrumWidget);
        drumScroll->setObjectName(QString::fromUtf8("drumScroll"));
        drumScroll->setMaximum(2046);
        drumScroll->setSingleStep(2);
        drumScroll->setPageStep(16);
        drumScroll->setOrientation(Qt::Vertical);

        horizontalLayout_2->addWidget(drumScroll);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(DrumWidget);

        QMetaObject::connectSlotsByName(DrumWidget);
    } // setupUi

    void retranslateUi(QWidget *DrumWidget)
    {
        DrumWidget->setWindowTitle(QApplication::translate("DrumWidget", "\320\234\320\260\320\263\320\275\320\270\321\202\320\275\321\213\320\271 \320\261\320\260\321\200\320\260\320\261\320\260\320\275 (\320\236\320\227\320\243)", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DrumWidget", "\320\237\321\200\320\265\320\264\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\270\320\265", 0, QApplication::UnicodeUTF8));
        octSwitch->setText(QApplication::translate("DrumWidget", "\320\222\320\276\321\201\321\214\320\274\320\265\321\200\320\270\321\207\320\275\320\276\320\265", 0, QApplication::UnicodeUTF8));
        binSwitch->setText(QApplication::translate("DrumWidget", "\320\224\320\262\320\276\320\270\321\207\320\275\320\276\320\265", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("DrumWidget", "\320\241\321\202\320\265\321\200\320\265\321\202\321\214", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = drumView->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DrumWidget", "00", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = drumView->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DrumWidget", "01", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DrumWidget: public Ui_DrumWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRUMWIDGET_H
