#include "downTbv.h"

void DownTableView::selectMode(int n)
{
    if(n == -2)
    {
        selectDataTableD.delegateSelectDataVec = &selectDataVec;
        getSamePrize(&selectDataVec);
        listSelectItem(&selectDataVec);
    }
    if(n == -3)
    {
        selectDataTableD.delegateSelectDataVec = &selectNeighborDataVec;
        getSamePrize(&selectNeighborDataVec);
        listSelectItem(&selectNeighborDataVec);
    }
    if(n == -4)
    {
        selectDataTableD.delegateSelectDataVec = &selectMixDataVec;
        getSamePrize(&selectMixDataVec);
        listSelectItem(&selectMixDataVec);
    }
    this->viewport()->update();
}
