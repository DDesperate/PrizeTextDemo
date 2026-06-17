#include "upTbv.h"
void UpTableView::count()
{
    //清空原坐标集
    countCoos.clear();

    ///通过数据结构计算坐标集(用于统计有多少期没有出现过某奖注)
    int maxCount = 0;
    //通过dataMap计算出计数坐标集
    for(int col = 0; col < 80; col++)
    {
        //计数，倒序遍历dataMap，得出有count期没有出现过某奖注
        int count = 0;
        for (auto iter = dataMap.end() - 1; iter != dataMap.begin() - 1; --iter) {
            if(iter.value().prizes.at(col).num != 0){
                break;
            }
            count ++;
        }
        maxCount = count>maxCount?count:maxCount;

        //得出计数单元格的坐标，放进countCoos
        if(count != 0){
            for(auto iter = dataMap.end() - 1; iter != dataMap.begin() - 1; --iter){
                if(count == 0)
                    break;
                int row = std::distance(dataMap.begin(), iter);
                coo coo{row,col+1,QString::number(count--)};
                countCoos.append(coo);
            }
        }
    }
//    for(auto coo:countCoos){
//        qDebug() << "coo.col" << coo.col;
//        qDebug() << "coo.row" << coo.row;
//    }

    ///将坐标集和数据结构应用到委托当中
    dataTableD.maxCount = maxCount;
    dataTableD.delegateCountCoos = &countCoos;
}
