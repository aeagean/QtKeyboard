#**********************************************************
#Author: Qtjun
#Qt君公众号
#官网：www.qthub.com
#QQ群: 732271126
#Email: 2088201923@qq.com
#**********************************************************
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtKeyboard
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

CONFIG += c++11

win32: RC_ICONS += app.ico

INCLUDEPATH = Keyboard

SOURCES += main.cpp \
    Keyboard/KeyButton.cpp \
    Keyboard/Keyboard.cpp \
    Keyboard/NumberKeyboard.cpp

HEADERS  += \
    Keyboard/AbstractKeyboard.h \
    Keyboard/KeyButton.h \
    Keyboard/Keyboard.h \
    Keyboard/NumberKeyboard.h

RESOURCES += Resources/Image.qrc

# 可启用下列宏
# 启用汉字库
# ENABLED_CHINESE_LIB

# 启用词组汉字库
# ENABLED_CHINESE_PHRASE_LIB

# 启用谷歌汉字库(推荐使用)
# ENABLED_GOOGLE_CHINESE_LIB

# 启用文泉驿字体库
# ENABLED_WQY_FONT

DEFINES += ENABLED_GOOGLE_CHINESE_LIB

contains(DEFINES, ENABLED_CHINESE_LIB) {
    RESOURCES += Resources/ChineseLib.qrc
}

contains(DEFINES, ENABLED_CHINESE_PHRASE_LIB) {
    RESOURCES += Resources/ChinesePhraseLib.qrc
}

contains(DEFINES, ENABLED_GOOGLE_CHINESE_LIB) {
    RESOURCES += Resources/GoogleChineseLib.qrc
}

contains(DEFINES, ENABLED_WQY_FONT) {
    RESOURCES += Resources/Font.qrc
}
