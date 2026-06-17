#include <QTableWidget>
#include <QList>
#include <QRandomGenerator>
#include "widget.h"

// 生成一个随机的整数，范围为 [min, max]
int getRandomInt(int min, int max)
{
    return QRandomGenerator::global()->bounded(min, max + 1);
}

// 获取选中列的索引列表，并将这些列的数据随机调换
void Widget::shuffleSelectedColumns(QTableWidget *dataTable, const QList<int> &selectedColumns)
{
    int rowCount = dataTable->rowCount();

    // 创建一个临时列表存储被选中列的数据
    QList<QList<QTableWidgetItem*>> columnDataList;

    // 收集选中列的数据
    for (int col : selectedColumns) {
        QList<QTableWidgetItem*> columnData;

        // 收集选中列的所有单元格数据
        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *item = dataTable->takeItem(row, col);  // 移除该列的所有单元格数据
            if (item) {
                columnData.append(item);
            }
        }

        // 将该列的数据添加到列表中
        columnDataList.append(columnData);
    }

    // 将收集到的列数据进行随机打乱
    for (int i = columnDataList.size() - 1; i > 0; --i) {
        int j = getRandomInt(0, i); // 生成一个随机的索引 j，范围为 [0, i]

        // 交换列数据
        columnDataList.swap(i, j);
    }

    // 更新表格中的数据
    for (int col = 0; col < selectedColumns.size(); ++col) {
        for (int row = 0; row < rowCount; ++row) {
            QTableWidgetItem *item = columnDataList[col][row];
            if (item) {
                dataTable->setItem(row, selectedColumns[col], item);  // 设置该列的所有单元格数据
            }
        }
    }
}
