#include "widget.h"
bool Widget::checkDataExistenceForDate(const QString &date)
{
    for(int row = 0;row < dataTable->rowCount();row++)
    {
        if( date == dataTable->item(row,0)->text())
            return false;
    }
    return  true;
}
