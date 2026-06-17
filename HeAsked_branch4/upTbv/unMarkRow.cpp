#include "upTbv.h"

void UpTableView::unMarkOneRow(const QString &date)
{
    if(selectedSet.contains(date)){
        dataMap[date].isSelected = false;
        refreshOneRowByDate(date);
        selectedSet.remove(date);
    }
}
