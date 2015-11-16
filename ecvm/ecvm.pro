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
    ural_cpu.cpp \
    printdevice.cpp \
    qural.cpp

HEADERS  += \
    AuxControlsWidget.hpp \
    controlregisterpanel.hpp \
    delegates.hpp \
    DrumWidget.hpp \
    PanelWidget.hpp \
    PultWIdget.hpp \
    ural_cpu.hpp \
    PowerPultWidget.hpp \
    printdevice.hpp \
    qural.hpp \
    intdelegate.hpp

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
    StopReasonsPanel.ui \
    printdevice.ui

RESOURCES += \
    images.qrc

unix {
LIBS += \
    -Wl,-rpath=../libural -L../libural/ -lural
}

win32 {
QMAKE_CXXFLAGS += -D__NO_INLINE__
win32-g++:LIBS += -Wl,-rpath=../libural/release/ -L../libural/release/ ../libural/release/ural.dll
}
