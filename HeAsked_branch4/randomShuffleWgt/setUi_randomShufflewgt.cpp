#include "randomshufflewgt.h"

void RandomShuffleWgt::setUi_randomShuffleWgt(QWidget *widget)
{
    // Set the size of the window
    this->resize(700, 600); // Adjust the size as needed

    // Get the screen geometry
    QRect screenGeometry = QApplication::desktop()->screenGeometry();

    // Calculate the x and y position for the window
    int x = screenGeometry.width() * 7 / 9 - this->width() / 2;
    int y = screenGeometry.height() / 2 - this->height() / 2;

    // Move the window to the calculated position
    this->move(x, y);

    vlay_randomshuffling = new QVBoxLayout(widget);
    hlay_getInfo_randomshuffling = new QHBoxLayout(widget);
    getInfo_randomshuffling = new QPushButton("获取信息",widget);
    hlay_shufflingitem_randomshuffling = new QHBoxLayout(widget);
    shufflingitem_randomshuffling = new QPushButton("乱序",widget);
    inputEdt_randomshuffling =  new NumLineEdit(widget);
    spinbox_randomshuffling = new QSpinBox(widget);
    spinbox_randomshuffling->setRange(0, 1000); // 设置范围
    btn_columnsSwap = new QPushButton("列交换",widget);
    dataTable_randomshuffling = new QTableWidget(widget);
    hlay_copybtn_randomshuffling = new QHBoxLayout(widget);
    btn_copyPrize_randomshuffling = new QPushButton("复制",widget);
    btn_copySelectedPrize_randomshuffling = new QPushButton("复制选中项",widget);
//    hlay_searchBtn = new QHBoxLayout(widget);
//    repeatSearchBtn = new QPushButton(tr("重号查询"),widget);
//    neighborSearchBtn = new QPushButton(tr("邻号查询"),widget);
//    mixSearchBtn = new QPushButton(tr("混合查询"),widget);


    //布局
    vlay_randomshuffling->addWidget(shufflingitem_randomshuffling);
    vlay_randomshuffling->addLayout(hlay_getInfo_randomshuffling);
    hlay_getInfo_randomshuffling->addWidget(spinbox_randomshuffling);
    hlay_getInfo_randomshuffling->addWidget(getInfo_randomshuffling);
    vlay_randomshuffling->addLayout(hlay_shufflingitem_randomshuffling);
    hlay_shufflingitem_randomshuffling->addWidget(inputEdt_randomshuffling);
    hlay_shufflingitem_randomshuffling->addWidget(shufflingitem_randomshuffling);
    vlay_randomshuffling->addWidget(btn_columnsSwap);
    vlay_randomshuffling->addWidget(dataTable_randomshuffling);
    vlay_randomshuffling->addLayout(hlay_copybtn_randomshuffling);
    hlay_copybtn_randomshuffling->addWidget(btn_copyPrize_randomshuffling);
    hlay_copybtn_randomshuffling->addWidget(btn_copySelectedPrize_randomshuffling);
//    vlay_randomshuffling->addLayout(hlay_searchBtn);
//    hlay_searchBtn->addWidget(repeatSearchBtn);
//    hlay_searchBtn->addWidget(neighborSearchBtn);
//    hlay_searchBtn->addWidget(mixSearchBtn);

    initTableWidget(dataTable_randomshuffling);

}
