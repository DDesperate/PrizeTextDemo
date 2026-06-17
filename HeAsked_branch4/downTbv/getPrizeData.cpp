#include "downTbv/downTbv.h"

QVector<slctTbRow> DownTableView::getPrizeDate(const QString& mode)
{
    if(mode == repeat){
        return selectDataVec;
    }
    else if(mode == neighbor){
        return selectNeighborDataVec;
    }
    else if(mode == mix){
        return selectMixDataVec;
    }
}
