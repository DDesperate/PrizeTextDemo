#include "downTbv.h"
#include <QRandomGenerator>
#include <QDateTime>
void DownTableView::randomClearOneRow()
{
    QByteArray seedData = QByteArray::number(QDateTime::currentMSecsSinceEpoch()); // 使用当前时间作为种子数据
    QRandomGenerator gen(seedData.toULongLong());
    int n = this->selectDataVec.size();

    if(n){
        int randomNumber = gen.bounded(n);

        //一定要先获取到日期，在删除，否则索引会出错
        QString date = this->selectDataVec.at(randomNumber).date;

        emit deleteOneRow(date);

        this->selectDataVec.removeAt(randomNumber);
        this->selectMixDataVec.removeAt(randomNumber);
        this->selectNeighborDataVec.removeAt(randomNumber);

        //删除下表一行
        this->removeOneModelRow();
    }
    this->viewport()->update();
}
