#include "widget.h"

void Widget::import(const QStringList &strList)
{
    if(strList.isEmpty())
        return;

    clearData(dataTable);

    //遍历strListData
    auto iter = strList.begin();
    for(int row=0; row< strList.length(); row++)
    {
        if(iter == strList.end())
            break;
        dataTable->insertRow(row);
        dataTable->setItem(row, 0, new QTableWidgetItem(iter->left(9)));
        QVector<QString> strVec_prize = iter->mid(9,iter->length()-9).trimmed().split(" ").toVector();
        for(int col=1; col<= 20 ; col++)
        {
            dataTable->setItem(row,col,new QTableWidgetItem(strVec_prize[col-1]));
            dataTable->item(row,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置居中
        }
        iter++;
    }
    dataTable->sortByColumn(0,Qt::DescendingOrder);//按照第0列的规则，倒序排列
}

void Widget::clearData(QTableWidget *tbwgt)
{
    //tbwgt->clear();//会把列头的文本clear掉

    //使用
    for(int i = tbwgt->rowCount() - 1;i >= 0; i--)
    {
        tbwgt->removeRow(i);
    }

    //或者
    //tbwgt->clear();
    //InitTableWidget(tbwgt);
}
