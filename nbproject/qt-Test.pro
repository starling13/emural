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
SOURCES += "Исходные тексты/controlregisterpanel.cpp" "Исходные тексты/test.cpp" "Исходные тексты/ural.cpp"
HEADERS += "Исходные тексты/controlregisterpanel.hpp" "Исходные тексты/fixed_coding.hpp" "Исходные тексты/ural.hpp"
FORMS += "Исходные тексты/AdderRegisterPanel.ui" "Исходные тексты/ArithmUnitRegisterPanel.ui" "Исходные тексты/ControlRegisterPanel.ui" "Исходные тексты/PCWIdget.ui"
RESOURCES += "Исходные тексты/изображения.qrc"
TRANSLATIONS +=
OBJECTS_DIR = build/Test/GNU-Linux-x86
MOC_DIR = Временные
RCC_DIR = Временные
UI_DIR = "Исходные тексты"
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += "Исходные тексты" /usr/include/qwt 
LIBS += -lqwt  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
