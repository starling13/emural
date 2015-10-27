# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = emural
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets
SOURCES += "Исходные тексты/DrumWidget.cpp" "Исходные тексты/intdelegate.cpp" "Исходные тексты/main.cpp" "Исходные тексты/test.cpp" "Исходные тексты/ural.cpp"
HEADERS += "Исходные тексты/DrumWidget.hpp" "Исходные тексты/fixed_coding.hpp" "Исходные тексты/intdelegate.h" "Исходные тексты/ural.hpp"
FORMS += "Исходные тексты/DrumWidget.ui"
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += . 
LIBS += 
