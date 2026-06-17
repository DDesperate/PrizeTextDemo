#include<QLineEdit>
#include<QScrollBar>
#include<QApplication>
#include<QClipboard>
#include"cmn.hpp"
#include"widget.h"

bool sortBySizeAndStr_Mix(const QPair<QString,QVector<QString>> &v1, const QPair<QString,QVector<QString>> &v2)
{
    return (v1.first.size() > v2.first.size()) || (v1.first.size() == v2.first.size() && v1.second < v2.second);
}

void Widget::mixAnalysis(QTableWidget *tbwgt, QLineEdit *le, QTextBrowser *tb)
{
    tb->clear();
    //清除高亮(多次查询时不会让上一次高亮影响这一次)

    initBackGround();

    //输入框奖注装入StringList
    QStringList prize = le->text().split(" ");
    if(le->text().isEmpty())
        return;
    QStringList neighborPrize;
    for(auto iter:prize){
        neighborPrize.append(QString("%1")
                             .arg(iter.toInt()+1,2,10,QLatin1Char('0')));
        neighborPrize.append(QString("%1")
                             .arg(iter.toInt()-1,2,10,QLatin1Char('0')));
    }
    neighborPrize= neighborPrize.toSet().toList();//去重

    QVector<QPair<QString,QVector<QString>>> Res;
    for(int row=0; row < (analysisNumSpinBox->value()>tbwgt->rowCount()?tbwgt->rowCount():analysisNumSpinBox->value()); row++)
    {
        QPair<QString,QVector<QString>> ResRow;
        ResRow.first = tbwgt->item(row,0)->text();
        for(int col=1; col < tbwgt->columnCount(); col++)
        {
            if(prize.contains(tbwgt->item(row,col)->text())&&(!neighborPrize.contains(tbwgt->item(row,col)->text()))){
                tbwgt->item(row,col)->setBackground(QColor(0,255,0));
                ResRow.second.append(tbwgt->item(row,col)->text());
            }
            if(neighborPrize.contains(tbwgt->item(row,col)->text())&&(!prize.contains(tbwgt->item(row,col)->text()))){
                tbwgt->item(row,col)->setBackground(QColor(255,0,0));
                ResRow.second.append(tbwgt->item(row,col)->text());
            }
            if(prize.contains(tbwgt->item(row,col)->text())&&neighborPrize.contains(tbwgt->item(row,col)->text())){
                tbwgt->item(row,col)->setBackground(QColor(22,119,210));
                ResRow.second.append(tbwgt->item(row,col)->text());
            }
        }
        Res.append(ResRow);
    }

    QList<QPair<QString,QVector<QString>>> Res6;
    analysisRes(&Res,Res6);

    QString strCopy;
    tb->append(QString::fromUtf8("统计数量:%1").arg(analysisNumSpinBox->value()));
    tb->append(QString::fromUtf8("选%1").arg(group->checkedButton()->text().mid(1)));
    tb->append(QString::fromUtf8("分析结果:"));
    tb->append(QString::fromUtf8("共%1条结果").arg(Res6.size()));
    for(auto iter:Res6){
        QString strRes;
        for(int i = 0;i<iter.second.size();i++)
        {
            strRes += iter.second.at(i)+" ";
            strCopy += iter.second.at(i)+" ";
        }
        tb->append(QString::fromUtf8("奖注:")+strRes);
        tb->append(QString::fromUtf8("期数:")+iter.first+"\n");
        strCopy += "\n";
    }
    QApplication::clipboard()->setText(strCopy.left(strCopy.size() - 1));
    tb->verticalScrollBar()->setValue(0);
}
