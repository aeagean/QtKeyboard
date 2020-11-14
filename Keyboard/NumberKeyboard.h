/**********************************************************
 * Author: Qt君
 * 微信公众号: Qt君(首发)
 * QQ群: 732271126
 * Email: 2088201923@qq.com
 * LICENSE: MIT
**********************************************************/

#ifndef NUMBERKEYBOARD_H
#define NUMBERKEYBOARD_H

#include "AbstractKeyboard.h"
#include "KeyButton.h"
#include <QLayout>
#include <QString>

namespace AeaQt {

class NumberKeyboard : public AbstractKeyboard
{
    Q_OBJECT
public:
    NumberKeyboard(QWidget *parent = NULL);

    KeyButton *createButton(QList<KeyButton::Mode> modes);

private slots:
    void onButtonPressed(const int &code, const QString &text);
};

}

#endif // NUMBERKEYBOARD_H
