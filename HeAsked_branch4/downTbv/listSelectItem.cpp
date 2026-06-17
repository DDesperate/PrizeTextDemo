#include "downTbv.h"
void DownTableView::listSelectItem(QVector<slctTbRow> *list)
{
    QList<quint8> selfSelectedList;
    foreach (auto pair, *list) {
        foreach(auto item,pair.prizes){
            if(item.isSelect){
                selfSelectedList.append(item.prize);
            }
        }
    }
    selfSelectedList = selfSelectedList.toSet().toList();
    qSort(selfSelectedList.begin(),selfSelectedList.end());

    return;
}
