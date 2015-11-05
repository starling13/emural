# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/DebugKeyDevice/GNU-Linux-x86
TARGET = emural
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += src/AuxControlsWidget.cpp src/DrumWidget.cpp src/PanelWidget.cpp src/PowerPultWidget.cpp src/PultWIdget.cpp src/controlregisterpanel.cpp src/controls.cpp src/intdelegate.cpp src/main.cpp src/test.cpp src/ural.cpp
HEADERS += src/AuxControlsWidget.hpp src/DrumWidget.hpp src/PanelWidget.hpp src/PowerPultWidget.h src/PultWIdget.hpp src/controlregisterpanel.hpp src/controls.hpp src/fixed_coding.hpp src/intdelegate.h src/ural.hpp
FORMS += src/AdderRegisterPanel.ui src/ArithmUnitRegisterPanel.ui src/AuxControlsWidget.ui src/CommandDecoderWidget.ui src/CommandRegisterPanel.ui src/ControlRegisterPanel.ui src/DrumWidget.ui src/PCWIdget.ui src/PanelWidget.ui src/PowerPultWidget.ui src/PultWIdget.ui src/StatusRegisterPanel.ui
RESOURCES += src/images.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/DebugKeyDevice/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
