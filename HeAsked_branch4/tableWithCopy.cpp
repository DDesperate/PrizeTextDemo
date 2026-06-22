#include "tableWithCopy.h"
#include <QClipboard>
#include <QApplication>
#include <QDebug>
#include <QSet>
#include <climits>

// 构造函数：设置右键菜单策略并连接信号槽
TableWithCopy::TableWithCopy(QWidget *parent) : QTableWidget(parent) {
    // 设置右键菜单策略
    setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接右键菜单信号到槽函数
    connect(this, &QTableWidget::customContextMenuRequested, this, &TableWithCopy::showContextMenu);

    // 点击单元格变色
    connect(this,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(getItemValueYellow(QTableWidgetItem*)));

    // 调整表格高度
    //adjustHeightBasedOnRowCount();
}

// 显示右键菜单
void TableWithCopy::showContextMenu(const QPoint &pos) {
    QMenu contextMenu;

    QAction copySelectedItemsAction("复制选中项", this);
    connect(&copySelectedItemsAction, &QAction::triggered, this, &TableWithCopy::copySelectedItems);
    contextMenu.addAction(&copySelectedItemsAction);

    contextMenu.exec(mapToGlobal(pos));
}

// 复制整个表格的所有数据到剪贴板
void TableWithCopy::copyAllData() {
    QString copiedText;

    // 遍历表格的所有行和列
    for (int row = 0; row < rowCount(); ++row) {
        QStringList rowData;
        //注意:这里是从第一列开始复制,不是第0列.故日期被省略了(雇主的需求)
        for (int col = 1; col < columnCount(); ++col) {
            QTableWidgetItem *item = this->item(row, col);
            if (item) {
                rowData << item->text();
            } else {
                rowData << "";  // 空单元格
            }
        }
        copiedText += rowData.join(" ") + "\n";  // 以 " " 分隔每个单元格，并换行分隔每行
    }

    // 将整个表格内容复制到剪贴板
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copiedText);
}

void TableWithCopy::copySelectedCol()  {
    QList<int> colList =  getSelectedIndices(this,true);
    std::sort(colList.begin(), colList.end());

    QString copiedText;

    // 遍历表格的所有行和被选中的列
    for (int row = 0; row < rowCount(); ++row) {
        QStringList rowData;
        //注意:这里是从第一列开始复制,不是第0列.故日期被省略了(雇主的需求)
        for (int col : colList) {
            QTableWidgetItem *item = this->item(row, col);
            if (item) {
                rowData << item->text();
            } else {
                rowData << "";  // 空单元格
            }
        }
        copiedText += rowData.join(" ") + "\n";  // 以 tab 分隔每个单元格，并换行分隔每行
    }

    // 将整个表格内容复制到剪贴板
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copiedText);
}

void TableWithCopy::copySelectedItems() {
    QItemSelectionModel *selection = selectionModel();
    if (!selection || !selection->hasSelection()) return;

    QModelIndexList selected = selection->selectedIndexes();
    if (selected.isEmpty()) return;

    // 找出选中区域的行列范围
    int minRow = INT_MAX, maxRow = INT_MIN;
    int minCol = INT_MAX, maxCol = INT_MIN;
    for (const QModelIndex &idx : selected) {
        minRow = qMin(minRow, idx.row());
        maxRow = qMax(maxRow, idx.row());
        minCol = qMin(minCol, idx.column());
        maxCol = qMax(maxCol, idx.column());
    }

    // 构建 (row, col) -> QModelIndex 的映射
    QSet<QPair<int,int>> selectedSet;
    for (const QModelIndex &idx : selected) {
        selectedSet.insert({idx.row(), idx.column()});
    }

    QString copiedText;
    for (int row = minRow; row <= maxRow; ++row) {
        QStringList rowData;
        for (int col = minCol; col <= maxCol; ++col) {
            if (selectedSet.contains({row, col})) {
                QTableWidgetItem *item = this->item(row, col);
                rowData << (item ? item->text() : "");
            } else {
                rowData << "";
            }
        }
        copiedText += rowData.join(" ") + "\n";
    }

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copiedText);
}


void TableWithCopy::getItemValueYellow(QTableWidgetItem* tbwgtit)
{
    // 检查标志，如果禁用就直接返回
    if (!enableItemColorChange) {
        return;
    }

    if(tbwgtit->column() != 0){
        tbwgtit->setBackground(QColor(255,231,73));
    }
}

// 调整表格高度的槽函数
void TableWithCopy::adjustHeightBasedOnRowCount() {
    int rowCount = this->rowCount();
    int rowHeight = this->verticalHeader()->defaultSectionSize();
    int headerHeight = this->horizontalHeader()->height(); // 获取表头的高度
    int height = rowCount < 5 ? (rowCount * rowHeight) + headerHeight : 200 + headerHeight;
    this->setFixedHeight(height);
}

// 设置行数并调整高度
void TableWithCopy::setRowCount(int count) {
    QTableWidget::setRowCount(count);
    adjustHeightBasedOnRowCount();
}
