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
SOURCES += "Исходные тексты/AuxControlsWidget.cpp" "Исходные тексты/DrumWidget.cpp" "Исходные тексты/PanelWidget.cpp" "Исходные тексты/PultWIdget.cpp" "Исходные тексты/controlregisterpanel.cpp" "Исходные тексты/controls.cpp" "Исходные тексты/intdelegate.cpp" "Исходные тексты/main.cpp" "Исходные тексты/test.cpp" "Исходные тексты/ural.cpp"
HEADERS += "Исходные тексты/AuxControlsWidget.hpp" "Исходные тексты/DrumWidget.hpp" "Исходные тексты/PanelWidget.hpp" "Исходные тексты/PultWIdget.hpp" "Исходные тексты/controlregisterpanel.hpp" "Исходные тексты/controls.hpp" "Исходные тексты/fixed_coding.hpp" "Исходные тексты/intdelegate.h" "Исходные тексты/ural.hpp"
FORMS += "Исходные тексты/AdderRegisterPanel.ui" "Исходные тексты/ArithmUnitRegisterPanel.ui" "Исходные тексты/AuxControlsWidget.ui" "Исходные тексты/CommandRegisterPanel.ui" "Исходные тексты/ControlRegisterPanel.ui" "Исходные тексты/DrumWidget.ui" "Исходные тексты/PCWIdget.ui" "Исходные тексты/PanelWidget.ui" "Исходные тексты/PultWIdget.ui"
RESOURCES += "Исходные тексты/изображения.qrc"
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
