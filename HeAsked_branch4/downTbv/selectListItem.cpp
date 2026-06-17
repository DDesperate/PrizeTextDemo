#include "downTbv.h"

void DownTableView::selectListItem(const QList<quint8> &list)
{
    if(mode == repeat){
        selectListItem_struct(list,selectDataVec);
    }
    if(mode == mix)
    {
        selectListItem_struct(list,selectMixDataVec);
    }

    if(mode == neighbor)
    {
        selectListItem_struct(list,selectNeighborDataVec);
    }
}

void DownTableView::selectListItem_struct(const QList<quint8> &list, QVector<slctTbRow> &vec)
{
    for (int i = 0; i < vec.size(); i++) {
        slctTbRow &row = vec[i];
        QList<slcInfo> &rowList = row.prizes;
        for (int j = 0; j < rowList.size(); j++) {
            if(list.contains(rowList[j].prize)){
                rowList[j].setSelected();
                //刷新(x,y)处的网格
                int x = i;
                int y = rowList.at(j).prize;
                refreshItem(x,y);
            }
        }
    }
}
