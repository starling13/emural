#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T14:20:26
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emural
TEMPLATE = app

INCLUDEPATH += ../libural

SOURCES += main.cpp \
    AuxControlsWidget.cpp \
    controlregisterpanel.cpp \
    delegates.cpp \
    DrumWidget.cpp \
    intdelegate.cpp \
    PanelWidget.cpp \
    PowerPultWidget.cpp \
    PultWIdget.cpp \
    ural_cpu.cpp

HEADERS  += \
    AuxControlsWidget.hpp \
    controlregisterpanel.hpp \
    delegates.hpp \
    DrumWidget.hpp \
    intdelegate.h \
    PanelWidget.hpp \
    PultWIdget.hpp \
    ural_cpu.hpp \
    PowerPultWidget.hpp

FORMS    += \
    AdderRegisterPanel.ui \
    ArithmUnitRegisterPanel.ui \
    AuxControlsWidget.ui \
    CommandDecoderWidget.ui \
    CommandRegisterPanel.ui \
    ControlRegisterPanel.ui \
    DebugPanel.ui \
    DrumWidget.ui \
    ModesPanel.ui \
    PanelWidget.ui \
    PCWIdget.ui \
    PowerPultWidget.ui \
    PultWIdget.ui \
    StatusRegisterPanel.ui \
    StopReasonsPanel.ui

RESOURCES += \
    images.qrc

LIBS += \
    -Wl,-rpath=../libural -L../libural/ -lural
