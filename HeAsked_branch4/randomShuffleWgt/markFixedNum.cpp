#include "randomshufflewgt.h"
void RandomShuffleWgt::markFixedNum(QTableWidget* tbwgt,const QList<quint8> fixedNum)
{
    for(int row=0; row<tbwgt->rowCount(); row++)
    {
        for(int col=0; col< tbwgt->columnCount(); col++)
        {
            QTableWidgetItem* _item = tbwgt->item(row,col);
            quint8 value = QStringToQuint8(_item->text());
            if(fixedNum.contains(value))
                _item->setBackground(QColor(255,231,73));
        }
    }
    tbwgt->clearSelection();
}
