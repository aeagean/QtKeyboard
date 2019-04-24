/**********************************************************
Author: 微信公众号(你才小学生)
WeChat public platform: nicaixiaoxuesheng
Email:  2088201923@qq.com
**********************************************************/

#ifndef AEA_ABSTRACT_KEYBOARD_H
#define AEA_ABSTRACT_KEYBOARD_H

#include <QApplication>
#include <QWidget>
#include <QDebug>
#include <QKeyEvent>

namespace AeaQt {

class AbstractKeyboard : public QWidget
{
    Q_OBJECT
public:
    AbstractKeyboard(QWidget *parent = 0) : QWidget(parent) {

    }
    ~AbstractKeyboard() { }

    const QString name() { return m_name; }
    void setName(const QString &name) { m_name = name; }

public slots:
    virtual void update(const QString &text) { Q_UNUSED(text); }
    void onKeyPressed(int key, QString value) {
qDebug()<<"key: "<<key<<"value: "<<value;
QWidget *receiver = QApplication::focusWidget();
if (!receiver)
    return;

qDebug()<<"Send key event "<<key<<" to focus widget "<<receiver->objectName();

QKeyEvent keyPress(QEvent::KeyPress,     key, Qt::NoModifier, value);
QKeyEvent keyRelease(QEvent::KeyRelease, key, Qt::NoModifier, value);

QApplication::sendEvent(receiver, &keyPress);
QApplication::sendEvent(receiver, &keyRelease);
    }

signals:
    void keyPressed(int key, QString value);

private:
    QString m_name;
};

}
#endif // AEA_ABSTRACT_KEYBOARD_H
