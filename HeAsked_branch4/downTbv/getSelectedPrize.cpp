#include "downTbv/downTbv.h"

QList<QList<quint8>> DownTableView::getSelectedPrizeForTbv(QVector<slctTbRow>* list)
{
    QList<QList<quint8>> tableList;
    for(auto row = list->begin();row != list->end();row++)
    {
        QList<quint8> rowList;
        for(auto col = row->prizes.begin();col != row->prizes.end();col++)
        {
            if(col->isSelect)
                rowList.append(col->prize);
        }
        tableList.append(rowList);
    }
    return tableList;
}

QList<QList<quint8>> DownTableView::getSelectedPrize()
{
    QList<QList<quint8>> res;
    if(mode == repeat){
        //更改数据结构中对应的数据为selected
        return getSelectedPrizeForTbv(&selectDataVec);
        //return res;
    }
    if(mode == mix){
        return getSelectedPrizeForTbv(&selectMixDataVec);
    }
    if(mode == neighbor){
        return getSelectedPrizeForTbv(&selectNeighborDataVec);
    }
}
