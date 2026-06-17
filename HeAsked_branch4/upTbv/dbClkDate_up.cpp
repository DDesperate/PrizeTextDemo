#include "upTbv.h"
void UpTableView::dbClkDate(const QModelIndex &Index)
{
    //点击的不是日期不标记
    if(Index.column() != 0)
        return;

    //获取点击行的日期
    QString date = dataMap.keys().at(Index.row());

    QList<quint8> prizeList =dataMap[date].getPrizeList();

    emit insertToInputEdt(prizeList);

    //如果这期彩票已经被选中，那么将其
    //1.更改为未选中
    //2.从选中集合中移除
    //3.从下表中移除
    if(dataMap[date].isSelected)
    {
        dataMap[date].isSelected = false;
        selectedSet.remove(date);
        emit cancelInsert(date);
    }

    //如果这期彩票没有被选中
    //1.更改为已选中
    //2.加入选中集合
    //3.加入下表
    else
    {
        dataMap[date].isSelected = true;
        selectedSet.insert(date);
        emit insertToDownTbv(date,dataMap[date].getPrizeList());
    }

    refreshOneRow(Index.row());

}
