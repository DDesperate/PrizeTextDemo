#include "upTbv.h"

void UpTableView::refreshOneRowByDate(const QString &date)
{
    //获取date在dataMap中的行数
    QList<QString> keysList = dataMap.keys();
    int row = keysList.indexOf(date);
    refreshOneRow(row);
}
