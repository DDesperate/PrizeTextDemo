#include "downTbv.h"
#include <QHeaderView>
DownTableView::DownTableView(QWidget *parent):PrizeTableView(parent){
    //隐藏列头
    horizontalHeader()->setVisible(false);

    // 设置右键菜单策略
    setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接右键菜单信号到槽函数
    connect(this, &DownTableView::customContextMenuRequested, this, &DownTableView::showContextMenu_down);


    //创建modeWidget
    //设置modeWidget宽高比1.3
    //设置到动画窗口中
    //modeWgt = new ModeWidget(this);
    //aModeWgt = new AnimationWidget(this,modeWgt);

    //使委托中的数据结构指向selectDataVec
    selectDataTableD.delegateSelectDataVec = &selectDataVec;

    //将委托应用到DownTableView中
    setItemDelegate(&selectDataTableD);

    //更改模式(不知为何使用lambda表达式失败)
    //connect(modeWgt->group,SIGNAL(buttonClicked(int)),this,SLOT(selectMode(int)));

    //双击一项选中(变为绿色)
    connect(this,&QTableView::doubleClicked,this,[=](QModelIndex const &Index){
        this->selectItem(Index);
    });

}

DownTableView::~DownTableView(){

}

void DownTableView::resizeEvent(QResizeEvent *event)
{
    PrizeTableView::resizeEvent(event);

    //改变"上下按钮"窗口位置  纵坐标改为0后导致卡顿，可能因为和列头重合？
    //aMoveWgt->setGeometry(totalWidth-aMoveWgtWidth,0,aMoveWgtWidth,2*aMoveWgtWidth);

    //获取modeWidget外的动画窗口的宽度
    //aModeWgtWidth  = aModeWgt->width();

    //totalWidth由继承获取，代表DownTableView当前宽度
    //2*aMoveWgtWidth代表"上下按钮"窗口高度，将aModeWgt纵坐标设置为2*aMoveWgtWidth
    //设置aModeWgtWidth(modeWidget外的动画窗口)的宽高比为1.3
    //aModeWgt->setGeometry(totalWidth-aModeWgtWidth,2*aMoveWgtWidth+10,aModeWgtWidth,aModeWgtWidth);


}





