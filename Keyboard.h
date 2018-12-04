/**********************************************************
Author: 微信公众号(你才小学生)
WeChat public platform: nicaixiaoxuesheng
Email:  2088201923@qq.com
**********************************************************/

#ifndef AEA_KEYBOARD_H
#define AEA_KEYBOARD_H

#include "AbstractKeyboard.h"
#include "KeyButton.h"

namespace AeaQt {

class Keyboard : public AbstractKeyboard
{
    Q_OBJECT
public:
    Keyboard(QWidget *parent = NULL);


public slots:
    void update(const QString &text);
    void onKeyPressed(const int &key, const QString &value);

private slots:
    void switchCapsLock();
    void switchSpecialChar();
    void switchEnOrCh();

private:
    KeyButton *createButton(QList<KeyButton::Mode> modes);
};

}
#endif // AEA_KEYBOARD_H
