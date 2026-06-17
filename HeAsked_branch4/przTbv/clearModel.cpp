#include "prizeTableView.h"
void PrizeTableView::clearModel()
{
    int rowCount = przModel.rowCount();
    for(int i = rowCount - 1;i >= 0; i--)
    {
        przModel.removeRow(i);
    }
}
