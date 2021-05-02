/**********************************************************
Author: Qt君
微信公众号: Qt君(首发)
QQ群: 732271126
Email: 2088201923@qq.com
**********************************************************/
#include "Keyboard.h"
#include "NumberKeyboard.h"

#include <QApplication>
#include <QLineEdit>
#include <QFontDatabase>

using namespace AeaQt;

static const QString qss = "                               \
                            QLineEdit {                    \
                                border-style: none;        \
                                padding: 3px;              \
                                border-radius: 5px;        \
                                border: 1px solid #dce5ec; \
                                font-size: 30px;           \
                            }                              \
                            ";

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#ifdef ENABLED_WQY_FONT
    int fontId = QFontDatabase::addApplicationFont(":/Font/wqy-microhei.ttc");
    QStringList stringList = QFontDatabase::applicationFontFamilies(fontId);
    QFont font(stringList.first());
    a.setFont(font);
#endif

    QWidget window;

    window.setWindowTitle(QStringLiteral("QtKeyboard by Qt君"));
    window.resize(850, 370);

    Keyboard keyboard;
    keyboard.show();

    QLineEdit textInput(&keyboard);
    textInput.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    textInput.setStyleSheet(qss);

    QVBoxLayout *v = new QVBoxLayout;
    v->addWidget(&textInput, 1);
    v->addWidget(&keyboard, 5);

    window.setLayout(v);
    window.show();

    ///////////////////////////////
    QWidget window2;
    window2.setWindowTitle(QStringLiteral("数字键盘 by Qt君"));
    window2.resize(450, 370);

    NumberKeyboard keyboard2;
    keyboard2.show();

    QLineEdit textInput2(&keyboard2);
    textInput2.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    textInput2.setStyleSheet(qss);

    QVBoxLayout *v2 = new QVBoxLayout;
    v2->addWidget(&textInput2, 1);
    v2->addWidget(&keyboard2, 5);

    window2.setLayout(v2);
    window2.show();

    return a.exec();
}
