#include "widget.h"
#include "cmn.hpp"
#include <QScrollBar>
void Widget::samePrizeCmn()
{
    samePrizeCmnText->clear();

    int selectNum = group->checkedButton()->text().mid(1).toInt();

    QVector<int> common_element_vec = sameNum.toVector();
    QVector<QVector<int>> all_common_element_vec = Combine(common_element_vec,selectNum);
    qDebug("test");
    samePrizeCmnText->append(QString::fromUtf8("输入数字:\n"));
//    for(auto iter:sameNum){
//        if(iter < 10 && iter > 0){
//            samePrizeCmnText->insertPlainText(QString("%1").arg(iter, 2, 10, QChar('0'))+" ");
//        }
//        else
//            samePrizeCmnText->insertPlainText(QString::number(iter)+" ");
//    }

    for(auto iter:sameNum){
        samePrizeCmnText->insertPlainText(QString::number(iter).rightJustified(2,'0')+" ");
    }

    samePrizeCmnText->append(QString::fromUtf8("%1选%2").arg(sameNum.length()).arg(selectNum));
    samePrizeCmnText->append(QString::fromUtf8("共%1条结果").arg(all_common_element_vec.count()));


    int count = 0;
    QString tempStr;
    QString tempStr1;
    QString tempStr2;

    for(auto list:all_common_element_vec)
    {
        for(auto iter:list)
        {
            count++;
            if(count < 100000)
                tempStr += QString("%1").arg(iter, 2, 10, QChar('0')) + " ";
            else if(count < 200000)
                tempStr1 += QString("%1").arg(iter, 2, 10, QChar('0')) + " ";
            else
                tempStr2 += QString("%1").arg(iter, 2, 10, QChar('0')) + " ";
        }
        if(count < 100000)
            tempStr += "\n";
        else if(count < 200000)
            tempStr1 += "\n";
        else
            tempStr2 += "\n";
    }
    samePrizeCmnText->append(tempStr);
    samePrizeCmnText->append(tempStr1);
    samePrizeCmnText->append(tempStr2);

    samePrizeCmnText->verticalScrollBar()->setValue(0);
}
