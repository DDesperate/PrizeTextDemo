#include "downTbv.h"

void DownTableView::getSamePrize(QVector<slctTbRow> *list)
{
    if((*list).isEmpty() || (*list).size() == 1)
    {
        QList<quint8> nullList;
        emit sendSamePrizeList(nullList);
        return;
    }

    QList<QList<quint8>> prizeList; // initialize an empty list of lists

    for (slctTbRow infoPair : *(list)) {
        QList<quint8> prizeInnerList; // initialize an empty list to store prize values for each infoPair
        for (slcInfo info : infoPair.prizes) {
            if(info.isDeleted == false){
                prizeInnerList.append(info.prize); // append each prize value to the prizeInnerList
            }
        }
        prizeList.append(prizeInnerList); // append the inner list to the prizeList
    }

    QSet<quint8> intersection;
    if (prizeList.size()) {  // 初始交集为 prizeList 的第一个元素
        for (quint8 i : prizeList[0]) {
            intersection.insert(i);
        }
    }

    for (int i = 1; i < prizeList.size() && !intersection.isEmpty(); ++i) {
        QSet<quint8> set;
        for (quint8 j : prizeList[i]) {
            set.insert(j);
        }
        intersection.intersect(set); // 使用 QSet 的 intersect() 方法计算交集
    }

    QList<quint8> resultList = intersection.values(); // 将交集转成 QList 形式

    qSort(resultList.begin(),resultList.end());

    emit sendSamePrizeList(resultList);
}
