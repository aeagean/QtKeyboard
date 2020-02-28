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
#include <QScroller>
#include <QRegExp>
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

const double BUTTON_SPACING_RATIO = 0.030;
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
    {{Qt::Key_Context1,    "",  "En"},    {Qt::Key_Context1, "", "中"}},
    {{Qt::Key_Space,       " ", ""/*空格*/}},
    {{Qt::Key_Enter,       "",  ""/*换行*/}}
};

Keyboard::Keyboard(QWidget *parent) :
    AbstractKeyboard(parent),
    m_isChinese(false)
{
    m_chineseWidget = new ChineseWidget(this);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    resize(850, 320);
    resizeButton();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSizeConstraint(QLayout::SetNoConstraint);
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addWidget(chineseBar(), 12);
    layout->addLayout(h1(), 15);
    layout->addLayout(h2(), 15);
    layout->addLayout(h3(), 15);
    layout->addLayout(h4(), 15);

    setLayout(layout);

    connect(m_chineseWidget, SIGNAL(pressedChanged(const int &, const QString &)),
            this, SLOT(onKeyPressed(const int &, const QString &)));

    connect(m_chineseWidget, SIGNAL(pressedChanged(const int &, const QString &)), this, SLOT(clearBufferText()));
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
    m_isChinese = !m_isChinese;
    QList<KeyButton *> buttons = findChildren<KeyButton *>();
    foreach(KeyButton *button, buttons) {
        if (button->mode().key == Qt::Key_Context1) {
            button->switching();
        }
    }
}

void Keyboard::onButtonPressed(const int &code, const QString &text)
{

    if (! m_isChinese) {
        onKeyPressed(code, text);
        m_bufferText.clear();
        return;
    }

    QRegExp rx("[a-zA-Z]");
    if (!rx.exactMatch(text) && m_bufferText.isEmpty()) {
        onKeyPressed(code, text);
        return;
    }

    if (code == Qt::Key_Backspace)
        m_bufferText.chop(1);
    else
        m_bufferText.append(text);
    m_chineseWidget->setText(m_bufferText);
}

void Keyboard::clearBufferText()
{
    m_bufferText.clear();
}

KeyButton *Keyboard::createButton(QList<KeyButton::Mode> modes)
{
    KeyButton *button = new KeyButton(modes, this);
    button->onReponse(this, SLOT(onButtonPressed(const int&, const QString&)));
    button->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return button;
}

QWidget *Keyboard::createBar(const QList<QList<KeyButton::Mode>> &modes)
{
    QWidget *widget = new QWidget;

    QHBoxLayout *h = new QHBoxLayout;
    for (int i = 0; i < modes.count(); i++) {
        KeyButton *button = createButton(modes.at(i));
        h->addWidget(button);
    }

    widget->setLayout(h);
    return widget;
}

QWidget *Keyboard::chineseBar()
{
    m_chineseWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    return m_chineseWidget;
}

QHBoxLayout *Keyboard::h1()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSizeConstraint(QLayout::SetNoConstraint);
    for (int i = 0; i < modeListBar1.count(); i++) {
        KeyButton *button = createButton(modeListBar1.at(i));
        h->addWidget(button);
    }

    return h;
}

QHBoxLayout *Keyboard::h2()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->addSpacing(20);
    for (int i = 0; i < modeListBar2.count(); i++) {
        KeyButton *button = createButton(modeListBar2.at(i));
        h->addWidget(button);
    }
    h->addSpacing(20);

    return h;
}

QHBoxLayout *Keyboard::h3()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(0);
    for (int i = 0; i < modeListBar3.count(); i++) {
        KeyButton *button = createButton(modeListBar3.at(i));
        if (i == 0 || i == (modeListBar3.count() - 1))
            h->addWidget(button, 70);
        else
            h->addWidget(button, 69);
    }

    return h;
}

QHBoxLayout *Keyboard::h4()
{
    QHBoxLayout *h = new QHBoxLayout;
    h->setSpacing(0);
    for (int i = 0; i < modeListBar4.count(); i++) {
        KeyButton *button = createButton(modeListBar4.at(i));
        if (i == 0)
            h->addWidget(button, 12);

        if (i == 1)
            h->addWidget(button, 10);

        if (i == 2)
            h->addWidget(button, 56);

        if (i == 3)
            h->addWidget(button, 22);
    }

    return h;
}

QWidget *Keyboard::candidateList()
{
    return m_chineseWidget;
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
            break;
        case Qt::Key_CapsLock:
            button->setIcon(QIcon(CAPLOCK_ICON));
            connect(button, SIGNAL(pressed()), this, SLOT(switchCapsLock()), Qt::UniqueConnection);
            break;
        case Qt::Key_Mode_switch:
            connect(button, SIGNAL(pressed()), this, SLOT(switchSpecialChar()), Qt::UniqueConnection);
            break;
        case Qt::Key_Context1:
            connect(button, SIGNAL(pressed()), this, SLOT(switchEnOrCh()), Qt::UniqueConnection);
            break;
        case Qt::Key_Enter:
            button->setIcon(QIcon(ENTER_ICON));
            break;
        case Qt::Key_Space:
            button->setIcon(QIcon(SPACE_ICON));
            break;
        default:
            break;
        }
    }
}

ChineseWidget::ChineseWidget(QWidget *parent) :
    QListWidget(parent)
{
    loadData();
    loadData2();

    setFocusPolicy(Qt::NoFocus);
    /* 设置为列表显示模式 */
    setViewMode(QListView::ListMode);

    /* 从左往右排列 */
    setFlow(QListView::LeftToRight);

    /* 屏蔽水平滑动条 */
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 屏蔽垂直滑动条 */
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 设置为像素滚动 */
    setHorizontalScrollMode(QListWidget::ScrollPerPixel);

    /* 设置鼠标左键拖动 */
    QScroller::grabGesture(this, QScroller::LeftMouseButtonGesture);

    /* 设置样式 */
    setStyleSheet(R"(
                    QListWidget { outline: none; border:1px solid #00000000; color: black; }
                    QListWidget::Item { width: 50px; height: 50px; }
                    QListWidget::Item:hover { background: #4395ff; color: white; }
                    QListWidget::item:selected { background: #4395ff; color: black; }
                    QListWidget::item:selected:!active { background: #00000000; color: black; }
                  )");

    connect(this, SIGNAL(itemClicked(QListWidgetItem *)), this, SLOT(onItemClicked(QListWidgetItem *)));
}

void ChineseWidget::setText(const QString &text)
{
    for (int i = 0; i < count(); i++) {
        QListWidgetItem *item = takeItem(i);
        delete item;
        item = NULL;
    }

    clear();

    addOneItem(text);

    if (! m_data.contains(text.left(1))) {
        return;
    }

    /* 通过获取首字母索引词库内容，用于加快匹配词(组)。 */
    const QList<QPair<QString, QString>> &tmp = m_data[text.left(1)];
    for (const QPair<QString, QString> &each : tmp) {
        /* 模糊匹配 */
        if (each.first.left(text.count()) != text)
            continue;

        /* 添加到候选栏 */
        addOneItem(each.second);
    }
}

void ChineseWidget::onItemClicked(QListWidgetItem *item)
{
    emit pressedChanged(-1, item->text());
    setText("");
}

void ChineseWidget::addOneItem(const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(text, this);
    QFont font;
    font.setPointSize(18);
    font.setBold(true);
    font.setWeight(50);
    item->setFont(font);

    /* 设置文字居中 */
    item->setTextAlignment(Qt::AlignCenter);
    bool isChinese = QRegExp("^[\u4E00-\u9FA5]+").indexIn(text.left(1)) != -1;

    int width = font.pointSize();
    if (isChinese)
        width += text.count()*font.pointSize()*1.5;
    else
        width += text.count()*font.pointSize()*2/3;

    item->setSizeHint(QSize(width, 50));
    addItem(item);
}

void ChineseWidget::loadData()
{
    QFile pinyin(":/ChineseLib/pinyin.txt");
    if (! pinyin.open(QIODevice::ReadOnly)) {
        qDebug() << "Open pinyin file failed!";
        return;
    }

    while (! pinyin.atEnd()) {
        QString buf = QString::fromUtf8(pinyin.readLine()).trimmed();
        QRegExp regExp("^[\u4E00-\u9FA5]+");

        int index = regExp.indexIn(buf);
        if (index == -1)
            continue;

        QString first = buf.right(buf.size() - regExp.matchedLength());
        QString second = buf.mid(index, regExp.matchedLength());

        QList<QPair<QString, QString>> &tmp = m_data[first.left(1)];
        tmp.append(qMakePair(first, second));
    }
}

void ChineseWidget::loadData2()
{
    /* 加载词组字库内容 */
    QFile pinyin(":/ChineseLib/pinyin_phrase.txt");
    if (! pinyin.open(QIODevice::ReadOnly)) {
        qDebug() << "Open pinyin file failed!";
        return;
    }

    /* 按行读取内容 */
    while (! pinyin.atEnd()) {
        QString buf = QString::fromUtf8(pinyin.readLine()).trimmed();
        if (buf.isEmpty())
            continue;

        /* 去除#号后的注释内容 */
        if (buf.left(1) == "#")
            continue;

        /* 正则匹配词组内容并通过组捕获获取'词组'和'拼音' */
        QRegExp regExp("(\\S+): ([\\S ]+)");
        int pos = 0;
        while ((pos = regExp.indexIn(buf, pos)) != -1) {
            pos += regExp.matchedLength();
            QString second = regExp.cap(1);  /* 词组 */
            QString first = regExp.cap(2); /* 拼音 */

            QStringList strList = first.split(" ");
            QString abb;
            for (int i = 0; i < strList.count(); i++) {
                /* 获得拼音词组的首字母(用于缩写匹配) */
                abb += strList.at(i).left(1);
            }
            QList<QPair<QString, QString>> &tmp = m_data[first.left(1)];
            /* 将'拼音(缩写)'和'词组'写入匹配容器 */
            tmp.append(qMakePair(abb, second));
            /* 将'拼音(全拼)'和'词组'写入匹配容器 */
            tmp.append(qMakePair(first.remove(" "), second));
        }
    }
}
