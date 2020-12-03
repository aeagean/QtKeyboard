/**********************************************************
#Author: Qtjun
#WeChat Official Accounts: qthub_com
#QQ Group: 732271126
#Email: 2088201923@qq.com
**********************************************************/

#ifndef AEA_KEY_BUTTON_H
#define AEA_KEY_BUTTON_H

#include <QPushButton>
#include <QVariant>

namespace AeaQt {

class KeyButton : public QPushButton
{
    Q_OBJECT
public:
    enum Type { Auto = 0, LowerCase, UpperCase, SpecialChar };

    struct Mode {
        Mode() { }
        Mode(int _key, QString _value, QVariant _display = QString(), Type _type = Auto)
        {
            key     = _key;
            value   = _value;
            display = _display;
            type    = _type;
        }

        int key;          /* Qt::Key */
        QString value;    /* text */
        QVariant display;  /* display text or icon */
        Type type;        /* default: Auto */
    };

    KeyButton(const QList<Mode> modes = QList<Mode>(), QWidget *parent = NULL);
    Mode mode();

    void onReponse(const QObject* receiverObj, const QString &receiver);

    void switchCapsLock();
    void switchSpecialChar();
    void switching(); /* Cycle switch. */

signals:
    void pressed(int key, QString value);

private slots:
    void onPressed();

private:
    Type find(const QString &value);
    Mode find(Type type);
    Mode findNext();
    void setDisplayContent(const QVariant &content);

private:
    Mode        m_preMode;
    Mode        m_mode;
    QList<Mode> m_modes;
};

}
#endif // AEA_KEY_BUTTON_H
