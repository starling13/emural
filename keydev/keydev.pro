#-------------------------------------------------
#
# Project created by QtCreator 2015-11-11T10:35:30
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keydev
TEMPLATE = app

INCLUDEPATH += ../libural

SOURCES += main.cpp\
        mainwindow.cpp \
    controlreaddevice.cpp

HEADERS  += mainwindow.hpp \
    controlreaddevice.hpp

FORMS    += mainwindow.ui \
    controlreaddevice.ui

unix {
LIBS += \
    -Wl,-rpath=../libural -L../libural/ -lural
}

win32 {
QMAKE_CXXFLAGS += -D__NO_INLINE__
win32-g++:LIBS += -Wl,-rpath=../libural/release/ -L../libural/release/ ../libural/release/ural.dll
}
