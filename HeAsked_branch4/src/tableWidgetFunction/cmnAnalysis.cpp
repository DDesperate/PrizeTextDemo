#include<QLineEdit>
#include<QScrollBar>
#include<QApplication>
#include<QClipboard>
#include"widget.h"
#include"cmn.hpp"

void Widget::cmnAnalysis(QLineEdit *le, QTextBrowser *tb)
{
    int selectNum = group->checkedButton()->text().mid(1).toInt();
    tb->clear();
    QStringList selectPrize = le->text().split(" ");
    selectPrize = selectPrize.toSet().toList();
    selectPrize.sort();
    //把排好序后的数列去掉两边的" ","\r\n"后放到LineEdit中
    QString strLe;
    for(auto iter:selectPrize){
        if(iter.toInt() >0 && iter.toInt()<=80)
            strLe += iter + " ";
    }
    le->setText(strLe.trimmed());

    int count = 0;
    tb->append(QString::fromUtf8("输入数字:"));
    QVector<QString> selectPrizeVec = strLe.trimmed().split(" ").toVector();
    for(auto iter:selectPrizeVec){
        tb->insertPlainText(iter + " ");
    }

    QVector<QVector<QString>> table = Combine(selectPrizeVec,selectNum);
    QString tempStr;
    for(auto list:table)
    {
        for(auto iter:list)
        {
            tempStr += iter + " ";
        }
        tempStr += "\n";
        count++;
    }
    tb->append(QString::fromUtf8("%1选%2").arg(selectPrizeVec.length()).arg(selectNum));
    tb->append(QString::fromUtf8("共%1条结果").arg(count));
    tb->append(tempStr);
    QApplication::clipboard()->setText(tempStr.left(tempStr.size() - 1));
    tb->verticalScrollBar()->setValue(0);
}
