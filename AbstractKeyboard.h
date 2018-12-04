/**********************************************************
Author: 微信公众号(你才小学生)
WeChat public platform: nicaixiaoxuesheng
Email:  2088201923@qq.com
**********************************************************/

#ifndef AEA_ABSTRACT_KEYBOARD_H
#define AEA_ABSTRACT_KEYBOARD_H
#include <QWidget>

namespace AeaQt {

class AbstractKeyboard : public QWidget
{
    Q_OBJECT
public:
    AbstractKeyboard(QWidget *parent = 0) : QWidget(parent) { }
    ~AbstractKeyboard() { }

    const QString name() { return m_name; }
    void setName(const QString &name) { m_name = name; }

public slots:
    virtual void update(const QString &text) { Q_UNUSED(text); }

signals:
    void keyPressed(int key, QString value);

private:
    QString m_name;
};

}
#endif // AEA_ABSTRACT_KEYBOARD_H
