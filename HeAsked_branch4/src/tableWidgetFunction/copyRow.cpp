#include "widget.h"
#include<QApplication>
#include<QClipboard>
void Widget::copyRow(QTableWidget *tbwgt, QLineEdit *le, QLineEdit *lePrize, QLineEdit *lePurple)
{
    int row = tbwgt->currentRow();
    QString RowData;
    for(int i=0;i<=20;i++)
    {
        RowData += tbwgt->item(row,i)->text()+" ";
    }
    if (!RowData.isEmpty())
    {
        //调用剪切板复制
        QApplication::clipboard()->setText(RowData.left(RowData.size()));
    }
    //数据弹出到搜索栏
    le->setText(RowData.mid(10,RowData.length()-10).trimmed());//trimmed:移除字符串最左最右边的空格/r/n等
    //中将检验窗口活跃时，将数据弹出到其中的lineedit
    if(!winningTest->isHidden())
        lePrize->setText(RowData.mid(10,RowData.length()-10).trimmed());
    //排列组合窗口活跃时，将数据弹出到其中的lineedit
    if(!cmn->isHidden())
        lePurple->setText(RowData.mid(10,RowData.length()-10).trimmed());
}
