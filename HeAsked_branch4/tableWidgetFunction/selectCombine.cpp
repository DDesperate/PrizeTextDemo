#include "widget.h"
#include <QMessageBox>

bool compareQuint8(quint8 a, quint8 b) {
    return a < b;
}

QVector<QList<quint8>> Widget::selectCombine(int rowCount)
{

    QVector<QList<quint8>> res;

    //dataTable
    if (dataTable->rowCount() == 0 || dataTable->columnCount() == 0) {
        QMessageBox::warning(nullptr, tr("警告"), tr("表中无数据"));
    }

    QList<quint8> selectedColumns;
    QList<QTableWidgetItem *> selectedItems = dataTable->selectedItems();

    foreach(QTableWidgetItem *item, selectedItems) {
        int column = item->column();
        if (!selectedColumns.contains(column)) {
            selectedColumns.append(column);
        }
    }

    // 输出被选中的列索引
    foreach(quint8 column, selectedColumns) {
        qDebug() << "Column " << column << " is selected.";
    }

    qSort(selectedColumns.begin(), selectedColumns.end(), compareQuint8);

    //遍历表
    for(int row=0; row < (rowCount>dataTable->rowCount()?dataTable->rowCount():rowCount); row++)
    {
        QList<quint8> rowData;
        foreach(quint8 column, selectedColumns) {
            QTableWidgetItem *item = dataTable->item(row, column);
            if (item && item->backgroundColor() != QColor(0,255,0)) {
                rowData.append(item->text().toUInt());
            }
        }
        if(!rowData.isEmpty())
            res.append(rowData);
    }

    return res;
}
