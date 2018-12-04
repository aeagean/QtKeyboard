/**********************************************************
Author: 微信公众号(你才小学生)
WeChat public platform: nicaixiaoxuesheng
Email:  2088201923@qq.com
**********************************************************/

#ifndef AEA_KEY_BUTTON_H
#define AEA_KEY_BUTTON_H

#include <QPushButton>

namespace AeaQt {

class KeyButton : public QPushButton
{
    Q_OBJECT
public:
    enum Type { Auto = 0, LowerCase, UpperCase, SpecialChar };

    struct Mode {
        int key; /* Qt::Key */
        QString value; /* text */
        QString display; /* display text */
        Type type;/* default: Auto */
    };

    KeyButton(const QList<Mode> modes = QList<Mode>(), QWidget *parent = NULL);
    Mode mode();

    void onReponse(const QObject* receiverObj, const QString &receiver);

    void switchCapsLock();
    void switchSpecialChar();

signals:
    void pressed(int key, QString value);

private slots:
    void onPressed();

private:
    Type find(const QString &value);
    Mode find(Type type);

private:
    Mode        m_preMode;
    Mode        m_mode;
    QList<Mode> m_modes;
};

}
#endif // AEA_KEY_BUTTON_H
