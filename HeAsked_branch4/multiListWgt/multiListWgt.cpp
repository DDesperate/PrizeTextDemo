#include "multiListWgt.h"



//构造函数
MultiListWidget::MultiListWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::Window);
    setUi_multiListWgt(this);

    //从原表中获取数据
    //根据本页面中各个表被选中的列,将原表中被选中的列搬到本页面的各个表中
    connect(btn_getData,&QPushButton::clicked,[=]{

        //获取原表行数
        int originList_rowCount = p_originTable->rowCount();
        //根据规则将数据依次填入新表
        for (TableWithCopy* table : tableWidgets) {
            if (table != nullptr) {
                //清除数据后重置表格的行数并且保留之前被选中的列
                table->resetTable();

               //获取被选中的列
               QList<int> selectedCol = getSelectedIndices(table,true);

               //如果表中有被选中的列
               if(!selectedCol.isEmpty()){
                   //向被选中的列中插入数值
                   for(int row = 0;row < originList_rowCount; ++row){
                       for (int column = 0; column < p_originTable->columnCount(); ++column) {
                           QTableWidgetItem *item = p_originTable->item(row, column);
                           if(column == 0){
                               table->setItem(row, column, new QTableWidgetItem(item->text()));
                           }
                           else if(selectedCol.contains(column)){
                               table->setItem(row, column, new QTableWidgetItem(item->text()));
                           }
                           else{
                               table->setItem(row, column, new QTableWidgetItem(""));
                           }
                       }
                       //如果要插入的不是最后一行则向表的尾部插入一个空行(此表初始状态下有一个空行，表中如果没有空行则无法选中列操作)
                       if(row != originList_rowCount - 1){
                           insertEmptyRow(table);//此表初始状态下有一个空行，先填入一行数据，再往末尾插入空行
                           table->adjustHeightBasedOnRowCount();
                       }
                   }
               }
            }
            //rowIndex_selectedCol++;
        }
    });
}


MultiListWidget::~MultiListWidget()
{
}

//这个函数有适用条件(如果表格中有没有填入数据的格子而使用此函数就会报错，所以最好填入数据，即使填入的数据为" ")
void initBackGround(TableWithCopy* tbwgt)
{
    for(int row=0; row<tbwgt->rowCount(); row++)
    {
        for(int col=0; col< tbwgt->columnCount(); col++)
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


// 清除数据后重置表格的行数并且保留之前被选中的列
void TableWithCopy::resetTable() {

    // 获取被选中的列
    QList<int> selectedColumns = getSelectedIndices(this, true);

    // 清空数据
    clearContents();

    //设置表的总行数为1（只有为1才能选中一列）
    setRowCount(1);

    //自适应调节表的大小
    this->adjustHeightBasedOnRowCount();

    //清空数据并设置总行数为1时，选中的列会被取消。
    //所以这里需要重新选中前面被记录下来的列
    QItemSelectionModel* selectionModel = this->selectionModel();
    if (selectionModel) {
        QItemSelection selection;
        for (int col : selectedColumns) {
            QModelIndex topLeft = this->model()->index(0, col);
            QModelIndex bottomRight = this->model()->index(this->rowCount() - 1, col);
            QItemSelection columnSelection(topLeft, bottomRight);
            selection.merge(columnSelection, QItemSelectionModel::Select);
        }
        selectionModel->select(selection, QItemSelectionModel::Select);
    }
}
