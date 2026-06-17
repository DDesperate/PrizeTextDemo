#include "downTbv.h"
void DownTableView::deleteOneRow_passive(const QString &date)
{
    deleteVecByDate(selectDataVec,date);
    deleteVecByDate(selectNeighborDataVec,date);
    deleteVecByDate(selectMixDataVec,date);

    if(mode == mix)
    {
        getSamePrize(&selectMixDataVec);
    }
    if(mode == repeat)
    {
        getSamePrize(&selectDataVec);
    }
    if(mode == neighbor)
    {
        getSamePrize(&selectNeighborDataVec);
    }
    removeOneModelRow();
}
