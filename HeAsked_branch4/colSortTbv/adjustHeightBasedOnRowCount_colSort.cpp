#include "colSortTbv.h"
#include <QHeaderView>
//原因未知,包含QHeaderView后"int rowHeight = this->verticalHeader()->defaultSectionSize();"语句才能生效

void ColSortTbv::adjustHeightBasedOnRowCount_withoutHeader(){
    //获取行数
    int rowCount = this->model()->rowCount();

    //获取行高
    //原因未知,包含QHeaderView后下列语句才能生效
    int rowHeight = this->verticalHeader()->defaultSectionSize();

    int height = rowCount < 20 ? (rowCount * rowHeight) : 20*rowHeight;

    //暂且设置成固定大小,不能手动拖拉改变表格大小
    //如果不设置成固定大小，也没有达到我想要的效果
    this->setFixedHeight(height);

    //例如下述两种方式，据无法达成理想效果
    //this->resize(this->width(), height);  // 初始高度设置，不锁定
    //this->setMinimumHeight(height);  // 初始最小高度

}
