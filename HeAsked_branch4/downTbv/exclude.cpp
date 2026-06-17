#include "downTbv/downTbv.h"

void DownTableView::excludeForTbv(const QList<quint8> &prizeListToBeExcluded,QVector<slctTbRow> *list)
{
    for(auto row = list->begin();row != list->end();row++)
    {
        for(auto col = row->prizes.begin();col != row->prizes.end();col++)
        {
            if(prizeListToBeExcluded.contains(col->prize))
                col->setDeleted(true);
        }
    }
}

void DownTableView::exclude(const QList<quint8> &prizeListToBeExclude)
{
    if(mode ==repeat){
        excludeForTbv(prizeListToBeExclude,&selectDataVec);
    }
    if(mode == mix){
        excludeForTbv(prizeListToBeExclude,&selectMixDataVec);
    }
    if(mode == neighbor){
        excludeForTbv(prizeListToBeExclude,&selectNeighborDataVec);
    }
    this->viewport()->update();
}
