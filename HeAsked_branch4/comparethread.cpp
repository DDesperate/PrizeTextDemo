#include "comparethread.h"

CompareThread::CompareThread(QThread *parent) : QThread(parent)
{

}

void CompareThread::calCompare(const QVector<QList<quint8>> &left,const QVector<QList<quint8>> &right)
{

    int TotalCount = left.size()*right.size();

    //左表遍历

    //左表计数(行数)
    int leftCount = 0;
    for(const QList<quint8> &leftRow:left){
        leftCount++;
        //右表遍历

        //右表计数(行数)
        int rightCount = 0;
        for(const QList<quint8> &rightRow:right){
            rightCount++;

            //如果左表某一行和右表某一行有相同的值
            if(!getCommonItems(leftRow,rightRow).isEmpty()){

                //打印相同的值
                //qDebug() << getCommonItems(leftRow,rightRow);

                //如果结果中已经有这一行，次数+1
                if(res_samePrizes.contains(getCommonItems(leftRow,rightRow))){

                    //map:res当中key值为getCommonItems(leftRow,rightRow)的value++
                    res_samePrizes[getCommonItems(leftRow,rightRow)].first++;

                    //打印次数
                    //qDebug() << res[getCommonItems(leftRow,rightRow)];

                    res_samePrizes[getCommonItems(leftRow,rightRow)].second +="左" + QString::number(leftCount) + ":" + prizeListToString(leftRow) + " " + "右" + QString::number(rightCount) + ":" + prizeListToString(rightRow) + "\n";

                }
                else{
                    QString str = "左" + QString::number(leftCount) + ":" + prizeListToString(leftRow) + " " + "右" + QString::number(rightCount) + ":" + prizeListToString(rightRow) + "\n";
                    QPair<int,QString> pair(1,str);
                    res_samePrizes.insert(getCommonItems(leftRow,rightRow),pair);
                }
            }

            emit sendProgressSignal(TotalCount,leftCount*right.size()+rightCount);
        }
    }
    qDebug() << "res_samePrizes" << res_samePrizes;
    emit sendResult(&res_samePrizes);
}
