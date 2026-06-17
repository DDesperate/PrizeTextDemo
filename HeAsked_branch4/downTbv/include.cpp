#include "downTbv/downTbv.h"

void DownTableView::includeForTbv(const QList<quint8> &prizeListToBeIncluded, QVector<slctTbRow> *list)
{
    for(auto row = list->begin();row != list->end();row++)
    {
        for(auto col = row->prizes.begin();col != row->prizes.end();col++)
        {
            if(!prizeListToBeIncluded.contains(col->prize))
                col->setDeleted(true);
        }
    }
}

void DownTableView::include(const QList<quint8> &prizeListToBeInclude)
{
    if(mode ==repeat){
        includeForTbv(prizeListToBeInclude,&selectDataVec);
    }
    if(mode == mix){
        includeForTbv(prizeListToBeInclude,&selectMixDataVec);
    }
    if(mode == neighbor){
        includeForTbv(prizeListToBeInclude,&selectNeighborDataVec);
    }
    this->viewport()->update();
}
