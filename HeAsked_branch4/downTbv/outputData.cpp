#include "downTbv/downTbv.h"

QVector<slctTbRow> DownTableView::outputData()
{
    if(mode == repeat){
        return selectDataVec;
    }else if(mode == neighbor){
        return selectNeighborDataVec;
    }else if(mode == mix){
        return selectMixDataVec;
    }
}


void DownTableView::inputData(const QVector<slctTbRow> &newData)
{
    // 替换 selectDataVec 数据
    selectDataVec = newData;
    for(int count = 0;count < newData.count(); count ++){
        this->addOneModelRow();
    }
    this->viewport()->update();
}
