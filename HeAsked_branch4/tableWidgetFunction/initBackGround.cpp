#include "widget.h"
void Widget::initBackGround(QTableWidget* tbwgt)
{
    for(int row=0; row<tbwgt->rowCount(); row++)
    {
        for(int col=1; col< tbwgt->columnCount(); col++)
        {
            QTableWidgetItem* _item = tbwgt->item(row,col);
            if(row%2 == 0)
                _item->setBackground(QColor(229,232,237));
            else
                _item->setBackground(QColor(234,246,246));
        }
    }
    tbwgt->clearSelection();
}
