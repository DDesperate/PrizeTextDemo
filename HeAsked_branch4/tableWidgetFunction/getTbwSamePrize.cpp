#include "widget.h"

bool mySort(const int &v1, const int &v2)
{
    return v1 < v2;
}

void Widget::getTbwSamePrize(QTableWidget *tbwgt)
{
    samePrizeText->clear();
    QList<int> selectRow = getSelectedIndices(tbwgt,false);
    if(selectRow.count() < 2)
        return;

    QSet<int> common_elements;
    for(auto row = selectRow.begin();row != selectRow.end();row++){
        QSet<int> RNprize;//R:repeat,N:Neighbor:重号和边号
        samePrizeText->append(tbwgt->item(*row,0)->text());
        samePrizeText->append("");
        for(auto col = 1;col < tbwgt->columnCount();col++){
            RNprize.insert(tbwgt->item(*row,col)->text().toInt());
            if(tbwgt->item(*row,col)->text().toInt()+1 <= 80)
                RNprize.insert(tbwgt->item(*row,col)->text().toInt()+1);
            if(tbwgt->item(*row,col)->text().toInt()-1 >= 1)
                RNprize.insert(tbwgt->item(*row,col)->text().toInt()-1);
        }
        QList<int> RNprizeList = RNprize.toList();
        qSort(RNprizeList.begin(),RNprizeList.end(),mySort);
        for(auto iter:RNprizeList){
            samePrizeText->insertPlainText(QString::number(iter).rightJustified(2,'0')+" ");
        }
        if(row == selectRow.begin())
            common_elements = RNprize;
        else
            common_elements.intersect(RNprize);
        samePrizeText->append("");

    }
    QList<int> common_elements_list = common_elements.toList();
    qSort(common_elements_list.begin(),common_elements_list.end(),mySort);
    samePrizeText->append("重复项:");
    samePrizeText->append(QString::fromUtf8("共%1条结果\n").arg(common_elements_list.size()));
    for(auto iter:common_elements_list){
        samePrizeText->insertPlainText(QString::number(iter).rightJustified(2,'0')+" ");
    }
    samePrizeText->append("");
    sameNum = common_elements_list;
    qDebug() << "test";
}
