/********************************************************************************
** Form generated from reading UI file 'PultWIdget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PULTWIDGET_H
#define UI_PULTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <controls.hpp>
#include "qwt_dial.h"
#include "qwt_knob.h"

QT_BEGIN_NAMESPACE

class Ui_PultWIdget
{
public:
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    BlackButton *masterOn;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    BlackButton *masterOff;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    BlackButton *shiftOn;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    BlackButton *shiftOff;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout_5;
    BlackButton *anodeOn;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_6;
    BlackButton *anodeOff;
    QLabel *label_9;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_8;
    QwtKnob *Knob;
    QwtKnob *Knob_2;
    QwtDial *Dial;
    QWidget *horizontalLayoutWidget_6;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_10;
    QHBoxLayout *horizontalLayout_9;
    BlackButton *shiftOn_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_11;
    QHBoxLayout *horizontalLayout_10;
    BlackButton *shiftOn_3;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_12;
    QHBoxLayout *horizontalLayout_11;
    BlackButton *shiftOn_4;

    void setupUi(QWidget *PultWIdget)
    {
        if (PultWIdget->objectName().isEmpty())
            PultWIdget->setObjectName(QString::fromUtf8("PultWIdget"));
        PultWIdget->resize(895, 521);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(80, 79, 77, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush3(QColor(158, 158, 158, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        QBrush brush4(QColor(106, 104, 100, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        PultWIdget->setPalette(palette);
        PultWIdget->setCursor(QCursor(Qt::OpenHandCursor));
        horizontalLayoutWidget_3 = new QWidget(PultWIdget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(10, 370, 361, 141));
        horizontalLayout_7 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(horizontalLayoutWidget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        masterOn = new BlackButton(horizontalLayoutWidget_3);
        masterOn->setObjectName(QString::fromUtf8("masterOn"));
        masterOn->setMinimumSize(QSize(30, 30));
        masterOn->setMaximumSize(QSize(30, 30));
        masterOn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout->addWidget(masterOn);


        verticalLayout->addLayout(horizontalLayout);

        label = new QLabel(horizontalLayoutWidget_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        masterOff = new BlackButton(horizontalLayoutWidget_3);
        masterOff->setObjectName(QString::fromUtf8("masterOff"));
        masterOff->setMinimumSize(QSize(30, 30));
        masterOff->setMaximumSize(QSize(30, 30));
        masterOff->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_2->addWidget(masterOff);


        verticalLayout->addLayout(horizontalLayout_2);

        label_3 = new QLabel(horizontalLayoutWidget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);


        horizontalLayout_7->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_4 = new QLabel(horizontalLayoutWidget_3);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        shiftOn = new BlackButton(horizontalLayoutWidget_3);
        shiftOn->setObjectName(QString::fromUtf8("shiftOn"));
        shiftOn->setMinimumSize(QSize(30, 30));
        shiftOn->setMaximumSize(QSize(30, 30));
        shiftOn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_3->addWidget(shiftOn);


        verticalLayout_2->addLayout(horizontalLayout_3);

        label_5 = new QLabel(horizontalLayoutWidget_3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        shiftOff = new BlackButton(horizontalLayoutWidget_3);
        shiftOff->setObjectName(QString::fromUtf8("shiftOff"));
        shiftOff->setMinimumSize(QSize(30, 30));
        shiftOff->setMaximumSize(QSize(30, 30));
        shiftOff->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_4->addWidget(shiftOff);


        verticalLayout_2->addLayout(horizontalLayout_4);

        label_6 = new QLabel(horizontalLayoutWidget_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_6);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_7 = new QLabel(horizontalLayoutWidget_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_7);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        anodeOn = new BlackButton(horizontalLayoutWidget_3);
        anodeOn->setObjectName(QString::fromUtf8("anodeOn"));
        anodeOn->setMinimumSize(QSize(30, 30));
        anodeOn->setMaximumSize(QSize(30, 30));
        anodeOn->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_5->addWidget(anodeOn);


        verticalLayout_3->addLayout(horizontalLayout_5);

        label_8 = new QLabel(horizontalLayoutWidget_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        anodeOff = new BlackButton(horizontalLayoutWidget_3);
        anodeOff->setObjectName(QString::fromUtf8("anodeOff"));
        anodeOff->setMinimumSize(QSize(30, 30));
        anodeOff->setMaximumSize(QSize(30, 30));
        anodeOff->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_6->addWidget(anodeOff);


        verticalLayout_3->addLayout(horizontalLayout_6);

        label_9 = new QLabel(horizontalLayoutWidget_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_9);


        horizontalLayout_7->addLayout(verticalLayout_3);

        horizontalLayoutWidget_4 = new QWidget(PultWIdget);
        horizontalLayoutWidget_4->setObjectName(QString::fromUtf8("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(20, 210, 341, 151));
        horizontalLayout_8 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        Knob = new QwtKnob(horizontalLayoutWidget_4);
        Knob->setObjectName(QString::fromUtf8("Knob"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Knob->setPalette(palette1);
        Knob->setUpperBound(12);
        Knob->setScaleMaxMajor(12);
        Knob->setScaleMaxMinor(1);
        Knob->setTotalSteps(12u);
        Knob->setInvertedControls(false);
        Knob->setKnobStyle(QwtKnob::Raised);
        Knob->setTotalAngle(340);
        Knob->setMarkerStyle(QwtKnob::Tick);
        Knob->setBorderWidth(1);

        horizontalLayout_8->addWidget(Knob);

        Knob_2 = new QwtKnob(horizontalLayoutWidget_4);
        Knob_2->setObjectName(QString::fromUtf8("Knob_2"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette2.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        Knob_2->setPalette(palette2);
        Knob_2->setUpperBound(12);
        Knob_2->setScaleMaxMajor(12);
        Knob_2->setScaleMaxMinor(1);
        Knob_2->setTotalSteps(12u);
        Knob_2->setPageSteps(2u);
        Knob_2->setTotalAngle(340);
        Knob_2->setMarkerStyle(QwtKnob::Tick);
        Knob_2->setBorderWidth(0);

        horizontalLayout_8->addWidget(Knob_2);

        Dial = new QwtDial(PultWIdget);
        Dial->setObjectName(QString::fromUtf8("Dial"));
        Dial->setGeometry(QRect(90, 0, 200, 200));
        Dial->setUpperBound(240);
        Dial->setScaleMaxMajor(12);
        Dial->setScaleMaxMinor(1);
        Dial->setLineWidth(4);
        Dial->setFrameShadow(QwtDial::Sunken);
        Dial->setOrigin(100);
        Dial->setMinScaleArc(100);
        Dial->setMaxScaleArc(235);
        horizontalLayoutWidget_6 = new QWidget(PultWIdget);
        horizontalLayoutWidget_6->setObjectName(QString::fromUtf8("horizontalLayoutWidget_6"));
        horizontalLayoutWidget_6->setGeometry(QRect(380, 420, 411, 91));
        horizontalLayout_12 = new QHBoxLayout(horizontalLayoutWidget_6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_12->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_10 = new QLabel(horizontalLayoutWidget_6);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_10);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        shiftOn_2 = new BlackButton(horizontalLayoutWidget_6);
        shiftOn_2->setObjectName(QString::fromUtf8("shiftOn_2"));
        shiftOn_2->setMinimumSize(QSize(30, 30));
        shiftOn_2->setMaximumSize(QSize(30, 30));
        shiftOn_2->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_9->addWidget(shiftOn_2);


        verticalLayout_4->addLayout(horizontalLayout_9);


        horizontalLayout_12->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_11 = new QLabel(horizontalLayoutWidget_6);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_11);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        shiftOn_3 = new BlackButton(horizontalLayoutWidget_6);
        shiftOn_3->setObjectName(QString::fromUtf8("shiftOn_3"));
        shiftOn_3->setMinimumSize(QSize(30, 30));
        shiftOn_3->setMaximumSize(QSize(30, 30));
        shiftOn_3->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_10->addWidget(shiftOn_3);


        verticalLayout_5->addLayout(horizontalLayout_10);


        horizontalLayout_12->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_12 = new QLabel(horizontalLayoutWidget_6);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(label_12);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        shiftOn_4 = new BlackButton(horizontalLayoutWidget_6);
        shiftOn_4->setObjectName(QString::fromUtf8("shiftOn_4"));
        shiftOn_4->setMinimumSize(QSize(30, 30));
        shiftOn_4->setMaximumSize(QSize(30, 30));
        shiftOn_4->setCursor(QCursor(Qt::PointingHandCursor));

        horizontalLayout_11->addWidget(shiftOn_4);


        verticalLayout_6->addLayout(horizontalLayout_11);


        horizontalLayout_12->addLayout(verticalLayout_6);


        retranslateUi(PultWIdget);
        QObject::connect(masterOn, SIGNAL(toggled(bool)), masterOff, SLOT(setUnckecked(bool)));
        QObject::connect(masterOff, SIGNAL(toggled(bool)), masterOn, SLOT(setUnckecked(bool)));
        QObject::connect(anodeOn, SIGNAL(toggled(bool)), anodeOff, SLOT(setUnckecked(bool)));
        QObject::connect(shiftOn, SIGNAL(toggled(bool)), shiftOff, SLOT(setUnckecked(bool)));
        QObject::connect(anodeOff, SIGNAL(toggled(bool)), anodeOn, SLOT(setUnckecked(bool)));

        QMetaObject::connectSlotsByName(PultWIdget);
    } // setupUi

    void retranslateUi(QWidget *PultWIdget)
    {
        PultWIdget->setWindowTitle(QApplication::translate("PultWIdget", "\320\237\321\203\320\273\321\214\321\202", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("PultWIdget", "\320\262\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("PultWIdget", "\320\241\320\225\320\242\320\254", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("PultWIdget", "\320\262\321\213\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("PultWIdget", "\320\262\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("PultWIdget", "\320\235\320\220\320\232\320\220\320\233-\320\241\320\234\320\225\320\251\320\225\320\235\320\230\320\225", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("PultWIdget", "\320\262\321\213\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("PultWIdget", "\320\262\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("PultWIdget", "\320\220\320\235\320\236\320\224", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("PultWIdget", "\320\262\321\213\320\272\320\273\321\216\321\207\320\265\320\275\320\276", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("PultWIdget", "\320\276\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("PultWIdget", "\320\277\321\203\321\201\320\272", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("PultWIdget", "\320\276\320\264\320\275\320\276\321\202\320\260\320\272\321\202\320\275\321\213\320\271 \321\200\320\265\320\266\320\270\320\274", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class PultWIdget: public Ui_PultWIdget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PULTWIDGET_H
