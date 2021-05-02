static void mySort()
{
    QList<QMap<QString, QStringList> > processingList;
    processingList << QMap<QString, QStringList>();
    processingList << QMap<QString, QStringList>();
    processingList << QMap<QString, QStringList>();
    processingList << QMap<QString, QStringList>();

    QFile file(":/GoogleChineseLib/rawdict_utf16_65105_freq.txt");
    if (! file.open(QIODevice::ReadOnly)) {
        qDebug() << "Open pinyin file failed!" << file.fileName();
        return;
    }

    QTextStream in(&file);
    in.setCodec("UTF-16"); // change the file codec to UTF-16.

    QStringList lines = in.readAll().split("\n");

    for (QString each : lines) {
        QRegExp re(R"RX((\S+).((?:-?\d+)(?:\.\d+)).((?:-?\d+)(?:\.\d+)?).(.*))RX");
        int pos = 0;

        bool isMatching = false;
        while ((pos = re.indexIn(each, pos)) != -1) {
            pos += re.matchedLength();
            if (re.captureCount() != 4)
                continue;

            isMatching = true;
            QString hanzi = re.cap(1); // 汉字
            QString weight = re.cap(2); // 权重
            QString tmp = re.cap(3); // 未知
            QString pinyin = re.cap(4); // 拼音(可能是词组)

            bool ok = false;
            double weightF = weight.toDouble(&ok);
            if (!ok) {
                qDebug() << each << "weight convert failed!";
            }

            QStringList pinyins = pinyin.split(" "); // 分隔词组
            QString abb;
            for (int i = 0; i < pinyins.count(); i++) {
                /* 获得拼音词组的首字母(用于缩写匹配) */
                abb += pinyins.at(i).left(1);
            }

            if (pinyins.count() >= 1 && pinyins.count() <= 4) {
                QMap<QString, QStringList> &needProcessingMap = processingList[pinyins.count() - 1];

                // 如果不存在则创建一个空的索引
                if (!needProcessingMap.contains(abb)) {
                    needProcessingMap[abb] = QStringList();
                }

                // 存放每一行字符串
                QStringList &tmp = needProcessingMap[abb];
                tmp.append(each);
            }
            else {
                qDebug() << "error in " << __LINE__ << "pinyins is empty.";
            }

        }

        if (!isMatching)
            qDebug() << each;
    }

    auto stringToDouble = [](QString string) -> double {
        QRegExp re(R"RX((\S+).((?:-?\d+)(?:\.\d+)).((?:-?\d+)(?:\.\d+)?).(.*))RX");
        int pos = 0;

        bool isMatching = false;
        while ((pos = re.indexIn(string, pos)) != -1) {
            pos += re.matchedLength();
            if (re.captureCount() != 4)
                continue;

            isMatching = true;
            QString hanzi = re.cap(1); // 汉字
            QString weight = re.cap(2); // 权重
            QString tmp = re.cap(3); // 未知
            QString pinyin = re.cap(4); // 拼音(可能是词组)

            bool ok = false;
            double weightF = weight.toDouble(&ok);
            if (!ok) {
                qDebug() << string << "weight convert failed!";
                return 0;
            }

            return weightF;

        }

        return 0;
    };

    const int checkCount = 65105;
    int count = 0;
    QFile outputFile("rawdict_utf16_65105_freq_sort.txt");
    if (!outputFile.open(QIODevice::WriteOnly)) {
        qDebug() << outputFile.fileName() << "open failed!";
        return;
    }

    QTextStream out(&outputFile);
    out.setGenerateByteOrderMark(true);
    out.setCodec("UTF-16");
    QString outString;

    for (auto needProcessingMap: processingList) {
        for (QStringList &iter : needProcessingMap) {
            count += iter.count();
            std::sort(iter.begin(), iter.end(), [&](QString l, QString r){
                return stringToDouble(l) > stringToDouble(r);
            });

            QString string = iter.join("\n");
            outString += string + "\n";
        }
    }

    out << outString;

    Q_ASSERT(count == checkCount);
    qDebug() << "count: " << count;

    file.close();

    return;
}