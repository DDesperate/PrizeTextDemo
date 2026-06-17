#include "upTbv.h"
void UpTableView::deleteSelectedRow()
{
    for(QString date:selectedSet)
    {
        dataMap.remove(date);
        emit cancelInsert(date);
        removeOneModelRow();
    }
    selectedSet.clear();
    count();
}
