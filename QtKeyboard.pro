#/**********************************************************
#Author: Qt君
#微信公众号: Qt君
#QQ群: 732271126
#Email: 2088201923@qq.com
#LICENSE: MIT
#**********************************************************/

#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T12:37:32
#
#-------------------------------------------------

QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtKeyboard
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

win32: RC_ICONS += app.ico

INCLUDEPATH = Keyboard

SOURCES += main.cpp \
    Keyboard/KeyButton.cpp \
    Keyboard/Keyboard.cpp

HEADERS  += \
    Keyboard/AbstractKeyboard.h \
    Keyboard/KeyButton.h \
    Keyboard/Keyboard.h

RESOURCES += \
    Resources/Resources.qrc
