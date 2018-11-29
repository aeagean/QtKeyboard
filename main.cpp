#include <QApplication>
#include "Keyboard.h"

using namespace AeaQt;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Keyboard keyboard;
    keyboard.show();

    return a.exec();
}
