#include "upTbv.h"
#include <QLineEdit>
#include <QApplication>
#include <QClipboard>

void UpTableView::searchRepeat(const QList<quint8> &numList,int row)
{
    //字符串(用于剪切板)
    QString copyStr;
    int rowCount =0;
    for (QMap<QString, tbRow>::iterator itRow = dataMap.begin(); itRow != dataMap.end(); ++itRow) {
        if(rowCount == row)
            break;
        tbRow& row = itRow.value();
        for (prizeInfo& prize : row.prizes) {
            if (numList.contains(prize.num)) {
                prize.color = QColor(Qt::green);
                copyStr += QString::number(prize.num).rightJustified(2,'0')+" ";
            }
        }
        rowCount++;
        copyStr += "\n";
    }

    QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));
}


void UpTableView::searchNeighbor(const QList<quint8> &numList,int row)
{
    if(numList.isEmpty()){
        return;
    }

    QList<quint8> neighborList;
    for(auto num:numList){
        neighborList.append(num+1);
        neighborList.append(num-1);
    }
    neighborList = neighborList.toSet().toList();
    neighborList.removeAll(0);
    neighborList.removeAll(81);

    //复制用字符串
    QString copyStr;
    int rowCount =0;
    for (QMap<QString, tbRow>::iterator itRow = dataMap.begin(); itRow != dataMap.end(); ++itRow) {
        if(rowCount == row)
            break;
        tbRow& row = itRow.value();
        for (prizeInfo& prize : row.prizes) {
            if (neighborList.contains(prize.num)) {
                prize.color = QColor(Qt::red);
                copyStr += QString::number(prize.num).rightJustified(2,'0')+" ";
            }
        }
        rowCount++;
        copyStr += "\n";
    }

    QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));

}

void UpTableView::searchMix(const QList<quint8> &numList,int row)
{
    if(numList.isEmpty()){
        return;
    }

    QList<quint8> neighborList;
    for(auto num:numList){
        neighborList.append(num+1);
        neighborList.append(num-1);
    }
    neighborList = neighborList.toSet().toList();
    neighborList.removeAll(0);
    neighborList.removeAll(81);

    //复制用字符串
    QString copyStr;
    int rowCount =0;
    for (QMap<QString, tbRow>::iterator itRow = dataMap.begin(); itRow != dataMap.end(); ++itRow) {
        if(rowCount == row)
            break;
        tbRow& row = itRow.value();
        for (prizeInfo& prize : row.prizes) {
            if ( numList.contains(prize.num) && !neighborList.contains(prize.num)) {
                prize.color = QColor(Qt::green);
                copyStr += QString::number(prize.num).rightJustified(2,'0')+" ";
            }
            if ( !numList.contains(prize.num) && neighborList.contains(prize.num)) {
                prize.color = QColor(Qt::red);
                copyStr += QString::number(prize.num).rightJustified(2,'0')+" ";
            }
            if ( numList.contains(prize.num) && neighborList.contains(prize.num)) {
                prize.color = QColor(Qt::black);
                copyStr += QString::number(prize.num).rightJustified(2,'0')+" ";
            }

        }
        rowCount++;
        copyStr += "\n";
    }
    QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));

    //第三，屎山代码要重新自己能够看懂

}

