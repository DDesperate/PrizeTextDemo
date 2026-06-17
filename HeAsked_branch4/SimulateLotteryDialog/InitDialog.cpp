#include"simulatelotterydialog.h"
#include"ui_simulatelotterydialog.h"

void SimulateLotteryDialog::InitDialog(){
    this->setWindowTitle(QString::fromUtf8("中奖检验"));

    //设置表的列数和列头标题(horizentalHeader是行头，verticalHeader是列头)
    for(int i=0;i<selectNum;i++){
        ui->detail->insertColumn(i);

        //第0列标题为1，第一列标题为2...
        ui->detail->setHorizontalHeaderItem(i,new QTableWidgetItem(QString::number(i+1)));

        //列头可拉伸
        ui->detail->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    //最后一列为计数列
    ui->detail->insertColumn(selectNum);
    ui->detail->setHorizontalHeaderItem(selectNum,new QTableWidgetItem(QString::fromUtf8("中奖数")));

    //美化:
    //列头(第一行)上色
    ui->detail->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color: black;}");
}
