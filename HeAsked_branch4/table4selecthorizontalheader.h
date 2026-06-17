#ifndef TABLE4SELECTHORIZONTALHEADER_H
#define TABLE4SELECTHORIZONTALHEADER_H

#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>
#include <QBrush>
#include "tableWithCopy.h"

class Table4SelectHorizontalHeader : public TableWithCopy
{
    Q_OBJECT
public:
    explicit Table4SelectHorizontalHeader(QWidget *parent = nullptr);
public slots:

    // 改变表头颜色的函数
    void changeHeaderColor(int index, const QColor &color);

    // 处理表头双击事件
    void handleColumnDoubleClick(int index);
};

#endif // TABLE4SELECTHORIZONTALHEADER_H
