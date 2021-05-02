/**********************************************************
#Author: Qtjun
#WeChat Official Accounts: qthub_com
#QQ Group: 732271126
#Email: 2088201923@qq.com
**********************************************************/

#include "KeyButton.h"
#include <QDebug>

using namespace AeaQt;

const QString DEFAULT_STYLE_SHEET = "AeaQt--KeyButton { background: #4395ff; border-radius: 5px;" \
                                  "margin: 5px;" \
                                  "font-size: 26px; color: white;}" \
                                  "AeaQt--KeyButton:pressed { background: #01ddfd }";

KeyButton::Type KeyButton::find(const QString &value)
{
    QRegExp rx("[a-z]");
    if (rx.exactMatch(value))
        return KeyButton::LowerCase;

    rx = QRegExp("[A-Z]");
    if (rx.exactMatch(value))
        return KeyButton::UpperCase;

    return KeyButton::SpecialChar;
}

KeyButton::Mode KeyButton::find(KeyButton::Type type)
{
    foreach (KeyButton::Mode mode, m_modes) {
        if (mode.type == type)
            return mode;
    }

    return m_modes.first();
}

KeyButton::Mode KeyButton::findNext()
{
    for(int i = 0; i < m_modes.count(); i++) {
        KeyButton::Mode mode = m_modes[i];
        if (mode.display == m_mode.display) {
            if (i+1 < m_modes.count())
                return m_modes.at(i+1);
            else
                return m_modes.first();
        }
    }

    return m_modes.first();
}

void KeyButton::setDisplayContent(const QVariant &content)
{
    if (content.type() == QVariant::String) {
        const QString &text = content.toString().toStdString().data();
        this->setText(text);
    }
    else if (content.type() == QVariant::Icon) {
        const QIcon &icon = content.value<QIcon>();
        this->setIcon(icon);
        this->setIconSize(QSize(1.2 * width(), 1.2 * height()));
    }
}

KeyButton::KeyButton(const QList<KeyButton::Mode> modes, QWidget *parent) :
    QPushButton(parent)
{
    Q_ASSERT(!modes.isEmpty());
    this->setFocusPolicy(Qt::NoFocus);
    this->setStyleSheet(DEFAULT_STYLE_SHEET);
    this->setAutoRepeat(true);

    foreach (Mode mode, modes) {
        if (mode.type == Auto) {
            mode.type = find(mode.value);
        }

        if (mode.display.isNull())
            mode.display = mode.value;

        m_modes.append(mode);
    }

    if (!modes.isEmpty()) {
        m_preMode = m_mode = m_modes.first();
        setDisplayContent(m_mode.display);
    }

    connect(this, SIGNAL(pressed()), this, SLOT(onPressed()));
}

KeyButton::Mode KeyButton::mode()
{
    return m_mode;
}

void KeyButton::onReponse(const QObject *receiverObj, const QString &receiver) {
    connect(this, SIGNAL(pressed(int,QString)), receiverObj, receiver.toStdString().c_str());
}

void KeyButton::switchCapsLock()
{
    if (m_mode.type == SpecialChar)
        return;

    m_preMode = m_mode;
    m_mode = find(m_mode.type == LowerCase ? UpperCase : LowerCase);
    setDisplayContent(m_mode.display);
}

void KeyButton::switchSpecialChar()
{
    if (m_mode.type == SpecialChar) {
        m_mode = m_preMode;
    }
    else {
        m_preMode = m_mode;
        m_mode = find(SpecialChar);
    }

    setDisplayContent(m_mode.display);
}

void KeyButton::switching()
{
    m_mode = findNext();
    setDisplayContent(m_mode.display);
}

void KeyButton::onPressed()
{
    emit pressed(m_mode.key, m_mode.value);
}
