#include "downTbv.h"

void DownTableView::selectMode(int n)
{
    qDebug() << "selectMode";
    if(n == -2)
    {
        mode = repeat;
        selectDataTableD.delegateSelectDataVec = &selectDataVec;
        getSamePrize(&selectDataVec);
        listSelectItem(&selectDataVec);
    }
    if(n == -3)
    {
        mode = neighbor;
        selectDataTableD.delegateSelectDataVec = &selectNeighborDataVec;
        getSamePrize(&selectNeighborDataVec);
        listSelectItem(&selectNeighborDataVec);
    }
    if(n == -4)
    {
        mode = mix;
        selectDataTableD.delegateSelectDataVec = &selectMixDataVec;
        getSamePrize(&selectMixDataVec);
        listSelectItem(&selectMixDataVec);
    }
    this->viewport()->update();
}
