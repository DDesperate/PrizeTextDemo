#include "widget.h"
void Widget::initBackGround()
{
    for(int row=0; row<dataTable->rowCount(); row++)
    {
        for(int col=0; col< dataTable->columnCount(); col++)
        {
            QTableWidgetItem* _item = dataTable->item(row,col);
            if(row%2 == 0)
                _item->setBackground(QColor(229,232,237));
            else
                _item->setBackground(QColor(234,246,246));
        }
    }
    dataTable->clearSelection();
}
