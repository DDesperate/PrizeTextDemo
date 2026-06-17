#include"simulatelotterydialog.h"
#include"ui_simulatelotterydialog.h"
#include"Cmn.hpp"

bool sortByCount(const QPair<QVector<QString>,int> &v1, const QPair<QVector<QString>,int> &v2)
{
    return v1.second>v2.second||v1.second == v2.second && v1.first > v2.first;
}
void SimulateLotteryDialog::DrawTable()
{
    //detailTable存储详情表中的数据
    QVector<QPair<QVector<QString>,int>> detailTable;

    //从一注SelectPrizes(自选号码)中选SelectNum个数，得出其全部可能
    QVector<QVector<QString>> table =  Combine(selectPrize.trimmed().split(" ").toVector(),selectNum);//table:不带有中几的table

    //处理开奖号码
    QStringList prizeSplit = prize.split(" ");

    //遍历自选号码中选SelectNum个数得到的全部组合,获取每个组合中奖count个号码，存入detailTable
    for(auto row:table){
        int count = 0;
        QPair<QVector<QString>,int> pairTmp;
        for(auto item:row){
            if(prizeSplit.contains(item)){
                count ++;
            }
        }
        pairTmp.first = row;
        pairTmp.second = count;
        detailTable.append(pairTmp);
    }

    //QList<QPair<QVector<QString>,int>> detailTableList;

    //排序(中奖个数最多的排在前面，中奖个数相同，按中奖号码从大到小排序)
    qSort(detailTable.begin(),detailTable.end(),sortByCount);

    //数据放入表中
    for(int row = 0;row<detailTable.length();row++)
    {
        ui->detail->insertRow(row);
        int col = 0;
        for(auto iter:detailTable[row].first){
            ui->detail->setItem(row,col,new QTableWidgetItem(iter));
            ui->detail->item(row,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
            if(prizeSplit.contains(iter)){
                ui->detail->item(row,col)->setBackground(QColor(255,0,0));
            }
            col++;
        }
        ui->detail->setItem(row,col,new QTableWidgetItem(QString::number(detailTable[row].second)));
    }

}
