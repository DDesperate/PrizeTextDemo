#ifndef GENERICFUNC_HPP
#define GENERICFUNC_HPP
#include <QSet>
QList<quint8> getCommonItems(const QList<quint8>& list1, const QList<quint8>& list2)
{
    QSet<quint8> set;
    QList<quint8> commonItems;

    // 将 list1 中的元素添加到 set
    for (const quint8& item : list1)
    {
        set.insert(item);
    }

    // 遍历 list2，将存在于 set 中的元素添加到 commonItems
    for (const quint8& item : list2)
    {
        if (set.contains(item))
        {
            commonItems.append(item);
        }
    }

    return commonItems;
}

QString prizeListToString(const QList<quint8> &list)
{
    QStringList stringList;
    for (quint8 value : list) {
        stringList.append(QString::number(value).rightJustified(2,'0'));
    }
    QString result = stringList.join(" ");
    return result;
}


#endif // GENERICFUNC_HPP
