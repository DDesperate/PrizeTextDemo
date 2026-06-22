#ifndef TABLEWITHCOPY_H
#define TABLEWITHCOPY_H

#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QItemSelection>
#include <QItemSelectionModel>
#include <QModelIndex>

#include "genericfunc.h"

class TableWithCopy : public QTableWidget {
    Q_OBJECT
public slots:
    void adjustHeightBasedOnRowCount(); // 新增槽函数以调整表格高度
public:
    explicit TableWithCopy(QWidget *parent = nullptr);

    // 设置"双击单元格变色"开关
    void setEnableItemColorChange(bool enable) { enableItemColorChange = enable; }

    // 设置"复制选中项"开关
    void setEnableCopySelectedColumns(bool enable) { enableCopySelectedColumns = enable; }

    // 调整表格高度
    void setRowCount(int count);

    // 清空表中数据，行数设置为1
    void resetTable();
private slots:
    void showContextMenu(const QPoint &pos);
    void copyAllData();  // 复制全部数据
    void copySelectedCol();     //复制选中列数据
    void copySelectedItems();   //复制选中项数据
    void getItemValueYellow(QTableWidgetItem* tbwgtit);


private:
    bool enableItemColorChange = true;  // 默认启用变色功能
    bool enableCopySelectedColumns = true; //默认启用"复制选中项"选项
};

#endif // TABLEWITHCOPY_H
