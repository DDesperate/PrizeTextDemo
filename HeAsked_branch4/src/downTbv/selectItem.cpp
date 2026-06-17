#include "downTbv.h"
void DownTableView::selectItem(const QModelIndex &Index)
{

    if(mode == repeat){
        //更改数据结构中对应的数据为selected
        structSelectedSwitch(Index,&selectDataVec);
        //将当前表中被选中的数据放到lineEdit中
        listSelectItem(&selectDataVec);
    }
    if(mode == mix){
        structSelectedSwitch(Index,&selectMixDataVec);
        listSelectItem(&selectMixDataVec);
    }
    if(mode == neighbor){
        structSelectedSwitch(Index,&selectNeighborDataVec);
        listSelectItem(&selectNeighborDataVec);
    }

    int x = Index.row();

    int y = Index.column();

    //获取坐标为(x,y)的网格的形状信息
    QRect rowRect = this->visualRect(this->przModel.index(x,y));


    //一定不能用"60+格子宽度*列数"计算，可能因为网格线宽度还是什么原因，总是计算不准确

    //坐标计算错误
    this->viewport()->update(rowRect.x(),rowRect.y(),rowRect.width(),rowRect.height());
    //也许可以点哪里刷新哪里而不是全部刷新
}
