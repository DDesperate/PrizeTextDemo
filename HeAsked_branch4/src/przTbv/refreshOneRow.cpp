#include "prizeTableView.h"

void PrizeTableView::refreshOneRow(int row)
{
    //获取第row行第一列的单元格形状信息(因为第0列宽固定为60，第一列的宽和后面的单元格的宽相同)
    QRect rowRect = this->visualRect(this->przModel.index(row,1));   //这里有点问题了

    //获取UpTableView整行宽度
    int rowWidth = this->viewport()->width();

    //单独对这一行刷新
    this->viewport()->update(0,rowRect.y(),rowWidth,rowRect.height());
}
