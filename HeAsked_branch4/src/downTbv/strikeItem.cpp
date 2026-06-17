#include "downTbv.h"
void DownTableView::strikeItem()
{
    if(mode == repeat){
        strikeItem_struct(selectDataVec);
        getSamePrize(&selectDataVec);
        listSelectItem(&selectDataVec);
    }
    if(mode == mix)
    {
        strikeItem_struct(selectMixDataVec);
        getSamePrize(&selectMixDataVec);
        listSelectItem(&selectMixDataVec);
    }

    if(mode == neighbor)
    {
        strikeItem_struct(selectNeighborDataVec);
        getSamePrize(&selectNeighborDataVec);
        listSelectItem(&selectNeighborDataVec);
    }
    //只用刷新单个点就可以了。
    //ui->selectDataTable->viewport()->update();
    //this->viewport()->update();
}


void DownTableView::strikeItem_struct(QVector<slctTbRow> &vec)
{
    for (int i = 0; i < vec.size(); i++) {
        slctTbRow &row = vec[i];
        QList<slcInfo> &list = row.prizes;
        for (int j = 0; j < list.size(); j++) {
            if (list[j].isSelect) {
                list[j].setDeleted(true);

                //刷新(x,y)处的网格
                int x = i;
                int y = list.at(j).prize;
                refreshItem(x,y);
            }
        }
    }

}
