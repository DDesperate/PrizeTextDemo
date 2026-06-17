#include "upTbv.h"

UpTableView::UpTableView(QWidget *parent):PrizeTableView(parent){

    // 设置右键菜单策略
    setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接右键菜单信号到槽函数
    connect(this, &UpTableView::customContextMenuRequested, this, &UpTableView::showContextMenu_upTbv);

    dataTableD.delegateDataMap = &dataMap;
    setItemDelegate(&dataTableD);
}

UpTableView::~UpTableView(){

}
