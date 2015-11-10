#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T13:55:52
#
#-------------------------------------------------

QT       += core gui
QMAKE_CXXFLAGS += -std=c++11

TARGET = ural
TEMPLATE = lib

DEFINES += LIBURAL_LIBRARY

SOURCES += \
    ural.cpp \
    controls.cpp \
    analogclock.cpp

HEADERS += \
    fixed_coding.hpp \
    ural.hpp \
    controls.hpp \
    analogclock.h

UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs

unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32 {
    CONFIG += dll
}
