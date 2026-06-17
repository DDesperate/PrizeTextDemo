#include "widget.h"
QList<int> Widget::getSelectedIndices(QTableWidget *tbwgt, bool selectColumns)
{
    //获取选择模型的指针
    QItemSelectionModel *selections =  tbwgt->selectionModel();
    //获取被选中的指针列表
    QModelIndexList selected = selections->selectedIndexes();

    QList<int> rowList;
    //qDebug() << "rowList" << rowList;
    foreach (QModelIndex index, selected) {
        if (selectColumns) {
            rowList.append(index.column());
        } else {
            rowList.append(index.row());
        }
    }
    //不知为何会获取到多个重复索引，故用QSet去重
   return rowList.toSet().toList();
}
