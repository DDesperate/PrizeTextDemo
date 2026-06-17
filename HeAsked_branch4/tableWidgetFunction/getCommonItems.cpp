#include "widget.h"

QList<quint8> Widget::getCommonItems(const QList<quint8>& list1, const QList<quint8>& list2)
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
