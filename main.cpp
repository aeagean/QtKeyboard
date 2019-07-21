/**********************************************************
Author: Qt君
微信公众号: Qt君(首发)
QQ群: 732271126
Email: 2088201923@qq.com
LICENSE: MIT
**********************************************************/
#include "Keyboard.h"

#include <QApplication>
#include <QLineEdit>
#include <QDebug>

using namespace AeaQt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Keyboard keyboard;
    keyboard.show();

    QLineEdit *textInput = new QLineEdit();
    textInput->show();

    return a.exec();
}
