/**********************************************************
#Author: Qtjun
#WeChat Official Accounts: qthub_com
#QQ Group: 732271126
#Email: 2088201923@qq.com
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
