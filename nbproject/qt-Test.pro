# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Test
TARGET = Урал-1
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += test.cpp "Исходные тексты/DisplayPanel.cpp" "Исходные тексты/ural.cpp"
HEADERS += "Исходные тексты/DisplayPanel.hpp" "Исходные тексты/ural.hpp"
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Test/GNU-Linux-x86
MOC_DIR = Временные
RCC_DIR = Временные
UI_DIR = "Исходные тексты"
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += "Исходные тексты" 
LIBS += -lqwt  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
CXX_LDFLAGS += -static
