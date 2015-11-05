#-------------------------------------------------
#
# Project created by QtCreator 2015-11-03T19:14:47
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = emural
TEMPLATE = app

INCLUDEPATH += src

HEADERS += \
    src/ural.hpp \
    src/PultWIdget.hpp \
    src/PowerPultWidget.h \
    src/PanelWidget.hpp \
    src/intdelegate.h \
    src/fixed_coding.hpp \
    src/DrumWidget.hpp \
    src/controls.hpp \
    src/controlregisterpanel.hpp \
    src/AuxControlsWidget.hpp \
    src/delegates.hpp

SOURCES += \
    src/ural.cpp \
    src/PultWIdget.cpp \
    src/PowerPultWidget.cpp \
    src/PanelWidget.cpp \
    src/main.cpp \
    src/intdelegate.cpp \
    src/DrumWidget.cpp \
    src/controls.cpp \
    src/controlregisterpanel.cpp \
    src/AuxControlsWidget.cpp \
    src/delegates.cpp

FORMS += \
    src/PultWIdget.ui \
    src/PowerPultWidget.ui \
    src/PCWIdget.ui \
    src/PanelWidget.ui \
    src/DrumWidget.ui \
    src/ControlRegisterPanel.ui \
    src/CommandRegisterPanel.ui \
    src/CommandDecoderWidget.ui \
    src/AuxControlsWidget.ui \
    src/ArithmUnitRegisterPanel.ui \
    src/AdderRegisterPanel.ui \
    src/StatusRegisterPanel.ui

RESOURCES += \
    src/images.qrc
