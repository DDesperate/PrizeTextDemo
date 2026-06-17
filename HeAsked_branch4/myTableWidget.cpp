#include "myTableWidget.h"
#include <QClipboard>
#include <QApplication>

// 构造函数：设置右键菜单策略并连接信号槽
MyTableWidget::MyTableWidget(QWidget *parent) : QTableWidget(parent) {
    // 设置右键菜单策略
    setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接右键菜单信号到槽函数
    connect(this, &QTableWidget::customContextMenuRequested, this, &MyTableWidget::showContextMenu);
}

// 显示右键菜单
void MyTableWidget::showContextMenu(const QPoint &pos) {
    // 创建上下文菜单
    QMenu contextMenu;

    // 创建“复制全部”操作
    QAction copyAllAction("复制全部", this);
    connect(&copyAllAction, &QAction::triggered, this, &MyTableWidget::copyAllData);

    // 添加“复制全部”操作到菜单
    contextMenu.addAction(&copyAllAction);

    // 显示菜单
    contextMenu.exec(mapToGlobal(pos));
}

// 复制整个表格的所有数据到剪贴板
void MyTableWidget::copyAllData() {
    QString copiedText;

    // 遍历表格的所有行和列
    for (int row = 0; row < rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < columnCount(); ++col) {
            QTableWidgetItem *item = this->item(row, col);
            if (item) {
                rowData << item->text();
            } else {
                rowData << "";  // 空单元格
            }
        }
        copiedText += rowData.join("\t") + "\n";  // 以 tab 分隔每个单元格，并换行分隔每行
    }

    // 将整个表格内容复制到剪贴板
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(copiedText);
}
