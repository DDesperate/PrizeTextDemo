#include"widget.h"
#include"cmn.hpp"

bool sort(const QPair<QString,QVector<QString>> &v1, const QPair<QString,QVector<QString>> &v2)
{
    return (v1.first.size() > v2.first.size()) || (v1.first.size() == v2.first.size() && v1.second < v2.second);
}
void Widget::analysisRes(QVector<QPair<QString,QVector<QString>>> *Res,QList<QPair<QString,QVector<QString>>> &Res6)
{
    int selectNum = group->checkedButton()->text().mid(1).toInt();

    QVector<QPair<QString,QVector<QString>>> Res1;
    for(int i = 0;i< Res->size() ; i++)
    {
        for(int j = i+1; j< Res->size(); j++)
        {
            QPair<QString,QVector<QString>> Res1_Row;
            Res1_Row.first = Res->at(i).first + "-" + Res->at(j).first;
            for(auto prize:Res->at(i).second)
            {
                if(Res->at(j).second.contains(prize))
                {
                    Res1_Row.second.append(prize);
                }
            }
            Res1.append(Res1_Row);
        }
    }

    QVector<QPair<QString,QVector<QString>>> Res2;
    QVector<QVector<QString>> group;
    for(auto iter_R:Res1)
    {
        group = Combine(iter_R.second,selectNum);
        for(auto iter_G:group)
        {
            QPair<QString,QVector<QString>> tempPair;
            tempPair.first = iter_R.first;
            tempPair.second = iter_G;
            Res2.append(tempPair);
        }
    }

    QVector<QVector<QString>> Res3;
    for(auto iter:Res2){
        Res3.append(iter.second);
    }
    QList<QVector<QString>> Res4 = Res3.toList().toSet().toList();

    QVector<QPair<QString,QVector<QString>>> Res5;
    for(auto iter_R4:Res4)
    {
        QPair<QString,QVector<QString>> tempPair;
        tempPair.second = iter_R4;
        for(auto iter_R:*Res)
        {
            bool contain = true;
            for(int i = 0;i<iter_R4.size();i++)
            {
                if(!iter_R.second.contains(iter_R4.at(i))){
                    contain = false;
                    break;
                }
            }
            if(contain == true)
            {
                tempPair.first += iter_R.first+" ";
            }
        }
        Res5.append(tempPair);
    }
    Res6 = Res5.toList();
    qSort(Res6.begin(),Res6.end(),sort);
}
