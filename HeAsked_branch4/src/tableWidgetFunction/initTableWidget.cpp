#include "widget.h"
#include<QHeaderView>
void Widget::initTableWidget(QTableWidget* tbwgt)
{
    //设置列头文本
    tbwgt->insertColumn(0);
    //期数:
    tbwgt->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromUtf8("期数")));
    //1-20:
    for(int i=1;i<=20;i++){
        tbwgt->insertColumn(i);
        tbwgt->setHorizontalHeaderItem(i,new QTableWidgetItem(QString::number(i)));
    }

    //设置第一列列头宽度自适应文本
    tbwgt->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //设置1到20列列头可拉伸(设置之前会有很大一部分在编辑框之外，拖动滚动条才能显示)
    for(int i=1;i<=20;i++){
            tbwgt->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    //美化:
    //列头(第一行)上色
    tbwgt->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color: black;}");

    //设置选中紫色
    tbwgt->setStyleSheet("selection-background-color: #aa00ff");

    //设置item不可编辑
    tbwgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
