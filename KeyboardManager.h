/**********************************************************
Author: 微信公众号(你才小学生)
WeChat public platform: nicaixiaoxuesheng
Email:  2088201923@qq.com
**********************************************************/

#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include "AbstractKeyboard.h"

namespace AeaQt {

class KeyboardManager : QObject
{
public:
    KeyboardManager();
    void addOneKeyboard(const QString &keyboardName, AbstractKeyboard *keyboard);
    void selected(const QString &keyboardName);

private slots:
    void keyPressed(int key, QString value);

signals:
    void update(const QString &text);

private:
    QList<AbstractKeyboard *> m_keyboards;
    AbstractKeyboard         *m_curKeyboard;
};

}
#endif // KEYBOARDMANAGER_H
