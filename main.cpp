/**********************************************************
Author: 微信公众号(你才小学生)
WeChat public platform: nicaixiaoxuesheng
Email:  2088201923@qq.com
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
