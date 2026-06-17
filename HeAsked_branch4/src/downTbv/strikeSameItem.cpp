#include "downTbv.h"
void DownTableView::strikeSameItem()
{
    if(mode == repeat){
        strikeSameItem_struct(selectDataVec);
        getSamePrize(&selectDataVec);
        listSelectItem(&selectDataVec);
    }
    if(mode == mix)
    {
        strikeSameItem_struct(selectMixDataVec);
        getSamePrize(&selectMixDataVec);
        listSelectItem(&selectMixDataVec);
    }

    if(mode == neighbor)
    {
        strikeSameItem_struct(selectNeighborDataVec);
        getSamePrize(&selectNeighborDataVec);
        listSelectItem(&selectNeighborDataVec);
    }

    this->viewport()->update();
}

void DownTableView::strikeSameItem_struct(QVector<slctTbRow > &vec)
{
    QVector<QSet<int>> prizeSets;
    for (const auto &dataPair : vec) {
        QSet<int> prizeSet;
        for (const auto &info : dataPair.prizes) {
            prizeSet.insert(info.prize);
        }
        prizeSets.append(prizeSet);
    }

    QSet<int> intersection;
    if (!prizeSets.isEmpty()) {
        intersection = prizeSets[0];
        for (int i = 1; i < prizeSets.size(); i++) {
            intersection.intersect(prizeSets[i]);
        }
    }

    // 3. Update Info.isDeleted for intersecting rows
    for (auto &dataPair : vec) {
        for (auto &info : dataPair.prizes) {
            if (intersection.contains(info.prize)) {
                info.setDeleted(true);
            }
        }
    }
}
