#include "prizeTableView.h"
#include <QHeaderView>
PrizeTableView::PrizeTableView(QWidget *parent) : QTableView(parent){

    //设置为81列(并设置列头为期数和1,2,3,...80)
    przModel.setColumnCount(81);
    przModel.setHeaderData(0, Qt::Horizontal, "期数");
    for(int i=1; i <= 80; i++)
    {
        przModel.setHeaderData(i,Qt::Horizontal,QString::number(i));
    }

    //把model设置的行列数应用到tableView上
    this->setModel(&przModel);

    //滚动条不用时消失
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //不可编辑
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //设置列宽自适应
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //设置行高自适应
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //设置列宽最小为1px
    this->verticalHeader()->setMinimumSectionSize(1);

    //设置行高最小为1px
    this->horizontalHeader()->setMinimumSectionSize(1);

    //设置第一列列宽固定为60
    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    this->setColumnWidth(0, 60);

    //设置列头样式表
    this->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color: black;}");

    //设置行头不可见
    this->verticalHeader()->setVisible(false);

    //topBottomWgt = new TopBottomWidget();

    //aMoveWgt = new AnimationWidget(this,topBottomWgt);

    //设置"划到顶部"和"滑到底部"的信号与槽
    //connect(topBottomWgt->btnUp,&QPushButton::clicked,this,[=]{this->scrollToTop();});

    //connect(topBottomWgt->btnDown,&QPushButton::clicked,this,[=]{this->scrollToBottom();});
}

PrizeTableView::~PrizeTableView()
{

}


void PrizeTableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);

    //tableView全长
    totalWidth = this->viewport()->width();

    //获取表格列数
    int columnCount = this->przModel.columnCount();

    //通过列数计算表格列宽
    int columnWidth = (totalWidth - 60) / (columnCount - 1);

    // 设置第一列的宽度为60
    this->setColumnWidth(0, 60);

    // 设置其他列的宽度为平均值
    for (int i = 1; i < columnCount; i++) {
        this->setColumnWidth(i, columnWidth);
    }

    // 设置行高等于列宽
    int rowHeight = columnWidth;

    // 设置行头高度为rowHeight(间接设置行高)
    this->verticalHeader()->setDefaultSectionSize(rowHeight);   //注意需要包含#include <QHeaderView>

    //设置动画窗口的宽
    //根据表的大小自适应调整topBottomWidget宽(宽度为表的总宽度的1/35,最小为50px)
    //aMoveWgtWidth = 50>(totalWidth/35)?50:(totalWidth/35);

    //aMoveWgt->setGeometry(totalWidth-aMoveWgtWidth,20,aMoveWgtWidth,2*aMoveWgtWidth);
}
