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

using namespace AeaQt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    Keyboard keyboard;
    QLineEdit textInput;

    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(&textInput);
    v->addWidget(&keyboard);

    window.setLayout(v);
    window.show();

    return a.exec();
}
