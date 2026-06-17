#include "downTbv/downTbv.h"

void DownTableView::import_D(const QVector<slctTbRow>& data)
{
    selectDataVec.append(data); // 插入数据
    reset();                    // 刷新表格
}
