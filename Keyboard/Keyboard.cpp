/**********************************************************
Author: Qt君
微信公众号: Qt君(首发)
QQ群: 732271126
Email: 2088201923@qq.com
LICENSE: MIT
**********************************************************/

#include "Keyboard.h"
#include <QVBoxLayout>
#include <QApplication>
#include <QDebug>

using namespace AeaQt;

typedef QList<KeyButton::Mode> Modes;
typedef QList<Modes> ModesList;

const int NORMAL_BUTTON_WIDTH  = 55;
const int NORMAL_BUTTON_HEIGHT = 45;

const QString BACKSPACE_ICON = ":/Image/backspace.png";
const QString ENTER_ICON     = ":/Image/enter.png";
const QString SPACE_ICON     = ":/Image/space.png";
const QString CAPLOCK_ICON   = ":/Image/caplock.png";

const double BUTTON_SPACING_RATIO = 0.045;
const double BUTTON_WIDTH_RATIO   = 0.09;
const double BUTTON_HEIGHT_RATIO  = 0.2;

const QList<Modes> modeListBar1 = {
    {{Qt::Key_Q, "q"}, {Qt::Key_Q, "Q"}, {Qt::Key_1, "1"}},
    {{Qt::Key_W, "w"}, {Qt::Key_W, "W"}, {Qt::Key_2, "2"}},
    {{Qt::Key_E, "e"}, {Qt::Key_E, "E"}, {Qt::Key_3, "3"}},
    {{Qt::Key_R, "r"}, {Qt::Key_R, "R"}, {Qt::Key_4, "4"}},
    {{Qt::Key_T, "t"}, {Qt::Key_T, "T"}, {Qt::Key_5, "5"}},
    {{Qt::Key_Y, "y"}, {Qt::Key_Y, "Y"}, {Qt::Key_6, "6"}},
    {{Qt::Key_U, "u"}, {Qt::Key_U, "U"}, {Qt::Key_7, "7"}},
    {{Qt::Key_I, "i"}, {Qt::Key_I, "I"}, {Qt::Key_8, "8"}},
    {{Qt::Key_O, "o"}, {Qt::Key_O, "O"}, {Qt::Key_9, "9"}},
    {{Qt::Key_P, "p"}, {Qt::Key_P, "P"}, {Qt::Key_0, "0"}},
};

const QList<Modes> modeListBar2 = {
    {{Qt::Key_A, "a"}, {Qt::Key_A, "A"}, {Qt::Key_unknown, "~"}},
    {{Qt::Key_S, "s"}, {Qt::Key_S, "S"}, {Qt::Key_unknown, "!"}},
    {{Qt::Key_D, "d"}, {Qt::Key_D, "D"}, {Qt::Key_At,      "@"}},
    {{Qt::Key_F, "f"}, {Qt::Key_F, "F"}, {Qt::Key_NumberSign, "#"}},
    {{Qt::Key_G, "g"}, {Qt::Key_G, "G"}, {Qt::Key_Percent, "%"}},
    {{Qt::Key_H, "h"}, {Qt::Key_H, "H"}, {Qt::Key_unknown, "'"}},
    {{Qt::Key_J, "j"}, {Qt::Key_J, "J"}, {Qt::Key_unknown, "&", "&&"}},
    {{Qt::Key_K, "k"}, {Qt::Key_K, "K"}, {Qt::Key_unknown, "*"}},
    {{Qt::Key_L, "l"}, {Qt::Key_L, "L"}, {Qt::Key_unknown, "?"}},
};

const QList<Modes> modeListBar3 = {
    {{Qt::Key_CapsLock, "", ""/*大小写切换*/}},
    {{Qt::Key_Z, "z"}, {Qt::Key_Z, "Z"}, {Qt::Key_ParenLeft, "("}},
    {{Qt::Key_X, "x"}, {Qt::Key_X, "X"}, {Qt::Key_ParenLeft, ")"}},
    {{Qt::Key_C, "c"}, {Qt::Key_C, "C"}, {Qt::Key_Minus,     "-"}},
    {{Qt::Key_V, "v"}, {Qt::Key_V, "V"}, {Qt::Key_unknown,   "_"}},
    {{Qt::Key_B, "b"}, {Qt::Key_B, "B"}, {Qt::Key_unknown,   ":"}},
    {{Qt::Key_N, "n"}, {Qt::Key_N, "N"}, {Qt::Key_Semicolon, ";"}},
    {{Qt::Key_M, "m"}, {Qt::Key_M, "M"}, {Qt::Key_Slash,     "/"}},
    {{Qt::Key_Backspace, "", ""/*退格*/}}
};

const QList<Modes> modeListBar4 = {
    {{Qt::Key_Mode_switch, "",  "?123"}},
    {{Qt::Key_Context1,    "",  "中"},    {Qt::Key_Context1, "", "En"}},
    {{Qt::Key_Space,       " ", ""/*空格*/}},
    {{Qt::Key_Enter,       "",  ""/*换行*/}}
};

Keyboard::Keyboard(QWidget *parent) :
    AbstractKeyboard(parent)
{
    setFixedSize(850, 320);
    resizeButton();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(BUTTON_SPACING_RATIO*height());
    layout->addLayout(h1());
    layout->addLayout(h2());
    layout->addLayout(h3());
    layout->addLayout(h4());

    mainLayout->addStretch();
    mainLayout->addLayout(layout);
    mainLayout->addStretch();

    setLayout(mainLayout);
}

void Keyboard::resizeEvent(QResizeEvent *e)
{
    resizeButton();
}

void Keyboard::switchCapsLock()
{
    QList<KeyButton *> buttons = findChildren<KeyButton *>();
    foreach(KeyButton *button, buttons)
        button->switchCapsLock();
}

void Keyboard::switchSpecialChar()
{
    QList<KeyButton *> buttons = findChildren<KeyButton *>();
    foreach(KeyButton *button, buttons)
        button->switchSpecialChar();
}

void Keyboard::switchEnOrCh()
{
    QList<KeyButton *> buttons = findChildren<KeyButton *>();
    foreach(KeyButton *button, buttons) {
        if (button->mode().key == Qt::Key_Context1) {
            button->switching();
            // todo
        }
    }
}

KeyButton *Keyboard::createButton(QList<KeyButton::Mode> modes)
{
    KeyButton *button = new KeyButton(modes, this);
    button->onReponse(this, SLOT(onKeyPressed(const int&, const QString&)));
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    return button;
}

QHBoxLayout *Keyboard::h1()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(BUTTON_SPACING_RATIO*height());
    for (int i = 0; i < modeListBar1.count(); i++) {
        KeyButton *button = createButton(modeListBar1.at(i));
        h->addWidget(button);
    }

    return h;
}

QHBoxLayout *Keyboard::h2()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(BUTTON_SPACING_RATIO*height());
    for (int i = 0; i < modeListBar2.count(); i++) {
        KeyButton *button = createButton(modeListBar2.at(i));
        h->addWidget(button);
    }

    return h;
}

QHBoxLayout *Keyboard::h3()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(BUTTON_SPACING_RATIO*height());
    for (int i = 0; i < modeListBar3.count(); i++) {
        KeyButton *button = createButton(modeListBar3.at(i));
        h->addWidget(button);
    }

    return h;
}

QHBoxLayout *Keyboard::h4()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(BUTTON_SPACING_RATIO*height());
    for (int i = 0; i < modeListBar4.count(); i++) {
        KeyButton *button = createButton(modeListBar4.at(i));
        h->addWidget(button);
    }

    return h;
}

void Keyboard::resizeButton()
{
    foreach (KeyButton *button, findChildren<KeyButton *>()) {
        int fixedWidth = width()*BUTTON_WIDTH_RATIO;
        int fixedHeight = height()*BUTTON_HEIGHT_RATIO;
        button->setIconSize(QSize(2*fixedWidth/3, 2*fixedHeight/3));

        switch (button->mode().key) {
        case Qt::Key_Backspace:
            button->setIcon(QIcon(BACKSPACE_ICON));
            fixedWidth = width()*BUTTON_WIDTH_RATIO*1.1 + height()*BUTTON_SPACING_RATIO/2;
            break;
        case Qt::Key_CapsLock:
            button->setIcon(QIcon(CAPLOCK_ICON));
            fixedWidth = width()*BUTTON_WIDTH_RATIO*1.1 + height()*BUTTON_SPACING_RATIO/2;
            connect(button, SIGNAL(pressed()), this, SLOT(switchCapsLock()), Qt::UniqueConnection);
            break;
        case Qt::Key_Mode_switch:
            fixedWidth = width()*BUTTON_WIDTH_RATIO*1.5 + height()*BUTTON_SPACING_RATIO/2;
            connect(button, SIGNAL(pressed()), this, SLOT(switchSpecialChar()), Qt::UniqueConnection);
            break;
        case Qt::Key_Context1:
            connect(button, SIGNAL(pressed()), this, SLOT(switchEnOrCh()), Qt::UniqueConnection);
            break;
        case Qt::Key_Enter:
            button->setIcon(QIcon(ENTER_ICON));
            fixedWidth = width()*BUTTON_WIDTH_RATIO*2.6 + height()*BUTTON_SPACING_RATIO/2;
            break;
        case Qt::Key_Space:
            button->setIcon(QIcon(SPACE_ICON));
            fixedWidth = width()*BUTTON_WIDTH_RATIO*5;
            break;
        default:
            break;
        }

        button->setFixedSize(fixedWidth, fixedHeight);
    }
}
