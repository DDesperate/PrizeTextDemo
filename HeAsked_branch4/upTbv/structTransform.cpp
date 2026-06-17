#include "upTbv.h"
//QList<quint8> UpTableView::vec80toList(QVector<prizeInfo>)
//{

//}

QVector<prizeInfo> UpTableView::listToVec80(QList<quint8> prizes)
{
    QVector<prizeInfo> prizeVec;
    prizeVec.resize(80);

    for(quint8 prize:prizes){
        prizeInfo tmpInfo;
        tmpInfo.num = prize;
        prizeVec[prize - 1] = tmpInfo;
    }
    return prizeVec;
}
