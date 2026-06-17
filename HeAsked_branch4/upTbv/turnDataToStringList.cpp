#include "upTbv.h"

QStringList UpTableView::turnDataToStringList()
{
    QStringList strList;
    QList<QString> keyList = dataMap.keys();
    for(auto key:keyList){
        QString str = key;
        for(auto prize:dataMap[key].getPrizeList()){
            str += " "+QString::number(prize).rightJustified(2,'0');
        }
        str += '\n';
        strList.append(str);
    }
    return strList;
}
