#include "widget.h"

bool compare(const QList<quint8>& list1, const QList<quint8>& list2) {
    return list1.size() < list2.size();
}

//把计算线程计算出的数据根据需求打印成文本，显示计数信息,限定一组数当中的元素个数
QString Widget::dataStructureToText_withCount(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition)
{
    QString resString;
    int count = 0;
    for (auto it = res.constBegin(); it != res.constEnd(); ++it) {
        const QList<quint8>& keyList = it.key();
        const QPair<int, QString>& pairValue = it.value();
        if(condition){
            if (keyList.size() != num)
                continue;
        }
        for(quint8 prize:keyList)
        {
            resString += QString::number(prize).rightJustified(2,'0') + ' ';
        }
        resString += tr("出现次数:") + QString::number(res[keyList].first) + '\n';
        count++;
    }
    QString rowCount = "总行数:"+QString::number(count)+"\n";
    return rowCount+resString;
}

//把计算线程计算出的数据根据需求打印成文本，不显示计数信息，限定一组数的出现次数
QString Widget::dataStructureToText_withoutCount(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition)
{
    QString resString;
//    int count = 0;
    for (auto it = res.constBegin(); it != res.constEnd(); ++it) {
        const QList<quint8>& keyList = it.key();
        const QPair<int, QString>& pairValue = it.value();
        if(condition){
            if (pairValue.first != num)
                continue;
        }
        for(quint8 prize:keyList)
        {
            resString += QString::number(prize).rightJustified(2,'0') + ' ';
        }
        resString += '\n';
//        count++;
    }
//    QString rowCount = "总行数:"+QString::number(count)+"\n";
    return resString;
}




