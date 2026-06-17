#include "upTbv.h"

QList<quint8> UpTableView::getLastRow()
{
    QList<quint8> lastRow;

    if (!dataMap.isEmpty()) {
        // 获取最后一行的数据
        QString lastKey = dataMap.lastKey();  // 使用行号作为键
        tbRow lastRowData = dataMap[lastKey];

        // 调用结构体tbRow的成员函数getPrizeList()获取奖励列表
        lastRow = lastRowData.getPrizeList();
    }

    return lastRow;
}
