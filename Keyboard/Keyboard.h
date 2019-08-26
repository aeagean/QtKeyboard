/**********************************************************
Author: Qt君
微信公众号: Qt君(首发)
QQ群: 732271126
Email: 2088201923@qq.com
LICENSE: MIT
**********************************************************/

#ifndef AEA_KEYBOARD_H
#define AEA_KEYBOARD_H

#include "AbstractKeyboard.h"
#include "KeyButton.h"
#include <QLayout>

namespace AeaQt {

class Keyboard : public AbstractKeyboard
{
    Q_OBJECT
public:
    Keyboard(QWidget *parent = NULL);

protected:
    void resizeEvent(QResizeEvent *e);

private slots:
    void switchCapsLock();
    void switchSpecialChar();
    void switchEnOrCh();

private:
    KeyButton *createButton(QList<KeyButton::Mode> modes);
    QHBoxLayout *h1();
    QHBoxLayout *h2();
    QHBoxLayout *h3();
    QHBoxLayout *h4();
    QHBoxLayout *candidateList();

    void resizeButton();
};

}
#endif // AEA_KEYBOARD_H
