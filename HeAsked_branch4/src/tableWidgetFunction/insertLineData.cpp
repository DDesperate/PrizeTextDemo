#include "widget.h"

int Widget::insertLineData(const QString &date, const QList<quint8> &prizes)
{
    int row = 0;

    for(row = 0;row < dataTable->rowCount();row++)
    {
        //一定是下述代码除了问题，但是我不知道

        //如果date 大于 当前行的日期，那么直接插入
        if(date > dataTable->item(row,0)->text().trimmed())
        {
            //向第0行插入新数据
            dataTable->insertRow(row);

            //设置第0行第0列的新数据
            dataTable->setItem(row, 0, new QTableWidgetItem(date));

            //设置第0行的第1列到第20列的新数据
            for(int col=1; col<= 20 ; col++)
            {
                QString number = QString::number(prizes.at(col-1)).rightJustified(2,'0');
                dataTable->setItem(0,col,new QTableWidgetItem(number));
                dataTable->item(0,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置居中
            }
            //插入成功
            return 1;
        }

        //如果date等于当前行的日期，那么更新当前行数据
        if(date == dataTable->item(row,0)->text().trimmed())
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr, "警告", "该期奖注已存在，是否覆盖?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                for(int col = 1;col <= 20;col ++)
                {
                    QString newText = QString::number(prizes.at(col-1)).rightJustified(2,'0');
                    dataTable->item(row,col)->setText(newText);
                }
                //覆盖成功
                return 0;
            }
            else {
                //取消插入
                return -1;
            }
        }
    }

    row = dataTable->rowCount();

    //此时应该向最后一行插入数据
    dataTable->insertRow(row);

    //设置第0行第0列的新数据
    dataTable->setItem(row, 0, new QTableWidgetItem(date));

    //设置第0行的第1列到第20列的新数据
    for(int col=1; col<= 20 ; col++)
    {
        QString number = QString::number(prizes.at(col-1)).rightJustified(2,'0');
        dataTable->setItem(row,col,new QTableWidgetItem(number));
        dataTable->item(row,col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//设置居中
    }
    //插入成功
    return 1;

}
