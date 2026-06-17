#include "table4selecthorizontalheader.h"
#include "genericfunc.h"

Table4SelectHorizontalHeader::Table4SelectHorizontalHeader(QWidget *widget)
{
    // 连接表头双击信号到槽函数
    connect(horizontalHeader(), &QHeaderView::sectionDoubleClicked,
            this, &Table4SelectHorizontalHeader::handleColumnDoubleClick);
}

// 改变表头颜色的函数
void Table4SelectHorizontalHeader::changeHeaderColor(int index, const QColor &color) {

}

// 处理表头双击事件
void Table4SelectHorizontalHeader::handleColumnDoubleClick(int index) {
    // 选中双击的列
    selectColumn(index);
    // 改变列头颜色
    changeHeaderColor(index, Qt::yellow); // 设置为黄色背景

    // 输出选中列的索引
    qDebug() << "Column" << index << "selected";
}
