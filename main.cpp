/**********************************************************
Author: Qt君
微信公众号: Qt君(首发)
QQ群: 732271126
Email: 2088201923@qq.com
LICENSE: MIT
**********************************************************/

#include <QApplication>
#include "Keyboard.h"
#include <QDebug>

using namespace AeaQt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Keyboard keyboard;
    keyboard.show();

    return a.exec();
}
