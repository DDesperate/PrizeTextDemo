#include "sortTableElementsByCountWgt.h"

SortTableElementsByCountWgt::SortTableElementsByCountWgt(QWidget *parent, const QRect& rect) :
    QDialog(parent)
{
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
    setGeometry(rect);
    setWindowTitle(QStringLiteral("数据处理窗口"));
}

SortTableElementsByCountWgt::~SortTableElementsByCountWgt()
{
}
