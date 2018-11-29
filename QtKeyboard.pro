#/**********************************************************
#Author: 微信公众号(你才小学生)
#Email:  2088201923@qq.com
#**********************************************************/

#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T12:37:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtKeyboard
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp \
    KeyButton.cpp \
    Keyboard.cpp

HEADERS  += \
    AbstractKeyboard.h \
    KeyButton.h \
    Keyboard.h
