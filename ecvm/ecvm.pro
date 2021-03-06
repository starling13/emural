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
    qural.cpp \
    punchdrives.cpp

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
    intdelegate.hpp \
    punchdrives.hpp

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
    printdevice.ui \
    punchtapewidget.ui

unix {
LIBS += \
    -Wl,-rpath=../libural -L../libural/ -lural
}

win32 {
message("Win32...")
QMAKE_CXXFLAGS += -D__NO_INLINE__
LIBS += -Wl,-rpath=../libural/release/ -L../libural/release/ ../libural/release/ural.dll
}
