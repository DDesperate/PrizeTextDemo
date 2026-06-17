#include "upTbv.h"
int UpTableView::insertOneRow(const QString &date, const QList<quint8> &prizes)
{
    //定义prizeVec并转化为匹配uptable的数据结构
    QVector<prizeInfo> prizeVec = listToVec80(prizes);

    if(dataMap.contains(date)){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "警告", "该期奖注已存在，是否覆盖?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {

            dataMap.insert(date,tbRow{false,prizeVec});
            count();
        }
        else {
            return -1;
        }
    }
    else{
        dataMap.insert(date,tbRow{false,prizeVec});
        addOneModelRow();
        count();
        return 1;
    }
}
