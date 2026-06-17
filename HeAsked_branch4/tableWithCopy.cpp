#include "tableWithCopy.h"
#include <QClipboard>
#include <QApplication>
#include <QDebug>

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
    // 创建上下文菜单
    QMenu contextMenu;

    // 创建“复制全部”操作
    QAction copyAllAction("复制全部", this);
    connect(&copyAllAction, &QAction::triggered, this, &TableWithCopy::copyAllData);

    // 添加“复制全部”操作到菜单
    contextMenu.addAction(&copyAllAction);

    // 创建“复制选中列”操作(下述2行不能放到if语句中，否则失效)
    QAction copySelectedColAction("复制选中列", this);
    connect(&copySelectedColAction, &QAction::triggered, this, &TableWithCopy::copySelectedCol);

    //如果"开关"打开,那么此功能才生效
    if(enableCopySelectedColumns == true){
        // 添加“创建“复制选中列”操作”操作到菜单
        contextMenu.addAction(&copySelectedColAction);
    }

    // 显示菜单
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
