#include "widget.h"

bool compare(const QList<quint8>& list1, const QList<quint8>& list2) {
    return list1.size() < list2.size();
}


QString Widget::dataStructureToText(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition)
{
    QString resString;
    for(const QList<quint8> &resList:res.keys())
    {
        if(condition){
            if (resList.size() != num)
                continue;
        }
        for(quint8 prize:resList)
        {
            resString += QString::number(prize).rightJustified(2,'0') + ' ';
        }
        resString += tr("出现次数:") + QString::number(res[resList].first) + '\n';
    }


    return resString;
}

