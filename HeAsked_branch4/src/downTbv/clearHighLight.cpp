#include "downTbv.h"

void DownTableView::clearHighLight()
{
    clearHighLight_struct(&selectDataVec);
    clearHighLight_struct(&selectNeighborDataVec);
    clearHighLight_struct(&selectMixDataVec);
    this->viewport()->update();
}

void DownTableView::clearHighLight_struct(QVector<slctTbRow> *list)
{
    //注意这里不能用foreach
    for(auto row = (*list).begin();row != (*list).end();row++)
    {
        for(auto item = (*row).prizes.begin();item != (*row).prizes.end();item++)
        {
            if(item->isSelect)
                item->isSelect = false;
        }
    }
}
