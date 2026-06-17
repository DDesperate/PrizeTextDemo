#include "downTbv.h"
void DownTableView::dbClkDate(const QModelIndex &Index)
{
    //点击的不是日期不标记
    if(Index.column() != 0)
        return;

    //获取点击行的日期
    QString date = selectDataVec[Index.row()].date;

    //加入选中集合
    selectedSet.insert(date);

    //如果下表中本行已被选中
    if(selectDataVec[Index.row()].isSelected)
    {
        //双击后该行状态改为未被选中
        selectDataVec[Index.row()].isSelected = false;
        selectNeighborDataVec[Index.row()].isSelected = false;
        selectMixDataVec[Index.row()].isSelected = false;
        //从选中集合中移除
        selectedSet.remove(date);
    }
    else
    {
        selectDataVec[Index.row()].isSelected = true;
        selectNeighborDataVec[Index.row()].isSelected = true;
        selectMixDataVec[Index.row()].isSelected = true;
        selectedSet.insert(date);
    }

    refreshOneRow(Index.row());


}
