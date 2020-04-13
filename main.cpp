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
    window.setWindowTitle("QtKeyboard by Qt君");
    window.resize(850, 370);
    Keyboard keyboard;
    keyboard.show();
    QLineEdit textInput(&keyboard);
    textInput.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    textInput.setStyleSheet("                              \
                            QLineEdit {                    \
                                border-style: none;        \
                                padding: 3px;              \
                                border-radius: 5px;        \
                                border: 1px solid #dce5ec; \
                                font-size: 30px;           \
                            }                              \
                            ");

    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(&textInput, 1);
    v->addWidget(&keyboard, 5);

    window.setLayout(v);
    window.show();

    return a.exec();
}
