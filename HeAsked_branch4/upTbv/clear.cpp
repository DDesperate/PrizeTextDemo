#include "upTbv.h"

//void UpTableView::clearModel(){
//    int rowCount = przModel.rowCount();

//    for(int i = rowCount - 1;i >= 0; i--)
//    {
//        przModel.removeRow(i);
//    }
//}

void UpTableView::clearSearchHighLight()
{
    for (QMap<QString, tbRow>::iterator itRow = dataMap.begin(); itRow != dataMap.end(); ++itRow) {
        tbRow& row = itRow.value();
        for (prizeInfo& prize : row.prizes) {
                prize.color = QColor(49,102,204);
        }
    }
}

void UpTableView::clearSelectedRowHighLight()
{
    for(QString date:selectedSet){
        dataMap[date].isSelected = false;
        refreshOneRowByDate(date);
        emit cancelInsert(date);
    }
    selectedSet.clear();
}
