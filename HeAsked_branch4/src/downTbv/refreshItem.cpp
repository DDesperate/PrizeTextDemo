#include "downTbv.h"
void DownTableView::refreshItem(int x, int y)
{
    QRect rowRect = this->visualRect(this->przModel.index(x,y));
    this->viewport()->update(rowRect.x(),rowRect.y(),rowRect.width(),rowRect.height());
}
