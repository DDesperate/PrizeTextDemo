#include "widget.h"
#include <QLineEdit>
#include <QApplication>
#include <QClipboard>

void Widget::searchRepeat(QTableWidget* tbwgt)
{
    //如果inputEdt->text()为空，那么prize仍然能获得值(""),但是后面的计算都是不必要的
    if(inputEdt->text().isEmpty())
        return;

    //输入框奖注装入StringList
    QStringList prize = inputEdt->text().split(" ");

    qDebug() << prize;

    //字符串(用于剪切板)
    QString copyStr;

    //遍历tablew'idget并高亮
    //如果analysisNum > tbwgt->rowCount()为真则返回tbwgt->rowCount()，否则返回analysisNum

    int analysisNum = analysisNumSpinBox->value();
    for(int row=0; row < (analysisNum > tbwgt->rowCount()?tbwgt->rowCount():analysisNum); row++)
    {
        for(int col=1; col < tbwgt->columnCount(); col++)
        {
            if(prize.contains(tbwgt->item(row,col)->text())){
                tbwgt->item(row,col)->setBackground(QColor(0,255,0));
                copyStr += tbwgt->item(row,col)->text()+" ";
            }
        }
        copyStr += "\n";
    }
    QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));
}


void Widget::searchNeighbor(QTableWidget* tbwgt)
{
    //如果inputEdt->text()为空，那么prize仍然能获得值(""),会算出其邻号为-1,1
    if(inputEdt->text().isEmpty())
        return;

    //输入框奖注装入StringList
    QStringList prize = inputEdt->text().split(" ");

    //将一期号码的所有邻号放到neighborPrize中
    QStringList neighborPrize;
    for(auto iter:prize){
        neighborPrize.append(QString("%1")
                             .arg(iter.toInt()+1,2,10,QLatin1Char('0')));
        neighborPrize.append(QString("%1")
                             .arg(iter.toInt()-1,2,10,QLatin1Char('0')));
    }

    //复制用字符串
    QString copyStr;

    //遍历tablewidget并高亮
    //如果analysisNum > tbwgt->rowCount()为真则返回tbwgt->rowCount()，否则返回analysisNum
    int analysisNum = analysisNumSpinBox->value();
    for(int row=0; row < (analysisNum>tbwgt->rowCount()?tbwgt->rowCount():analysisNum); row++)
    {
        //copyStr += tbwgt->item(row,0)->text();
        for(int col=1; col < tbwgt->columnCount(); col++)
        {
            if(neighborPrize.contains(tbwgt->item(row,col)->text())){
                tbwgt->item(row,col)->setBackground(QColor(255,0,0));
                copyStr += tbwgt->item(row,col)->text()+" ";
            }
        }
        copyStr += "\n";
    }
    QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));
}


//void Widget::searchMix(QTableWidget* tbwgt)
//{
//    //如果inputEdt->text()为空，那么prize仍然能获得值(""),会算出其邻号为-1,1
//    if(inputEdt->text().isEmpty())
//        return;

//    //输入框奖注装入StringList
//    QStringList prize = inputEdt->text().split(" ");

//    QStringList neighborPrize;
//    for(auto iter:prize){
//        neighborPrize.append(QString("%1")
//                             .arg(iter.toInt()+1,2,10,QLatin1Char('0')));
//        neighborPrize.append(QString("%1")
//                             .arg(iter.toInt()-1,2,10,QLatin1Char('0')));
//    }
//    neighborPrize= neighborPrize.toSet().toList();//去重

//    QString copyStr;
//    //如果analysisNum > tbwgt->rowCount()为真则返回tbwgt->rowCount()，否则返回analysisNum
//    int analysisNum = analysisNumSpinBox->value();
//    for(int row=0; row < (analysisNum>tbwgt->rowCount()?tbwgt->rowCount():analysisNum); row++)
//    {
//        for(int col=1; col < tbwgt->columnCount(); col++)
//        {
//            //重号包含邻号不包含设置为绿色
//            if(prize.contains(tbwgt->item(row,col)->text())&&(!neighborPrize.contains(dataTable->item(row,col)->text()))){
//                tbwgt->item(row,col)->setBackground(QColor(0,255,0));
//                copyStr += tbwgt->item(row,col)->text()+" ";
//            }
//            //邻号包含重号不包含设置为红色
//            if(neighborPrize.contains(tbwgt->item(row,col)->text())&&(!prize.contains(dataTable->item(row,col)->text()))){
//                tbwgt->item(row,col)->setBackground(QColor(255,0,0));
//                copyStr += tbwgt->item(row,col)->text()+" ";
//            }
//            //重号邻号都包含设置为深蓝色
//            if(prize.contains(tbwgt->item(row,col)->text())&&neighborPrize.contains(dataTable->item(row,col)->text())){
//                tbwgt->item(row,col)->setBackground(QColor(22,119,210));
//                copyStr += tbwgt->item(row,col)->text()+" ";
//            }
//        }
//        copyStr += "\n";
//    }
//    QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));
//    // 显示消息框通知用户复制成功
//    QMessageBox::information(this, tr("Copy Successful"), tr("The selected text has been copied to the clipboard."));
//}


void Widget::searchMix(QTableWidget* tbwgt)
{
    // 如果inputEdt->text()为空，那么prize仍然能获得值(""),会算出其邻号为-1,1
    if(inputEdt->text().isEmpty()) {
        qDebug() << "Input is empty, returning early.";
        return;
    }

    // 输入框奖注装入StringList
    QStringList prize = inputEdt->text().split(" ");
    qDebug() << "Prize numbers:" << prize;

    QStringList neighborPrize;
    for(auto iter: prize) {
        neighborPrize.append(QString("%1").arg(iter.toInt() + 1, 2, 10, QLatin1Char('0')));
        neighborPrize.append(QString("%1").arg(iter.toInt() - 1, 2, 10, QLatin1Char('0')));
    }
    neighborPrize = neighborPrize.toSet().toList(); // 去重
    qDebug() << "Neighbor prize numbers:" << neighborPrize;

    QString copyStr;
    // 如果analysisNum > tbwgt->rowCount()为真则返回tbwgt->rowCount()，否则返回analysisNum
    int analysisNum = analysisNumSpinBox->value();
    qDebug() << "Analysis number:" << analysisNum;

    for(int row = 0; row < (analysisNum > tbwgt->rowCount() ? tbwgt->rowCount() : analysisNum); row++) {
        for(int col = 1; col < tbwgt->columnCount(); col++) {
            QString cellText = tbwgt->item(row, col)->text();
            // 重号包含邻号不包含设置为绿色
            if(prize.contains(cellText) && (!neighborPrize.contains(cellText))) {
                tbwgt->item(row, col)->setBackground(QColor(0, 255, 0));
                copyStr += cellText + " ";
                qDebug() << "Green cell:" << cellText;
            }
            // 邻号包含重号不包含设置为红色
            if(neighborPrize.contains(cellText) && (!prize.contains(cellText))) {
                tbwgt->item(row, col)->setBackground(QColor(255, 0, 0));
                copyStr += cellText + " ";
                qDebug() << "Red cell:" << cellText;
            }
            // 重号邻号都包含设置为深蓝色
            if(prize.contains(cellText) && neighborPrize.contains(cellText)) {
                tbwgt->item(row, col)->setBackground(QColor(22, 119, 210));
                copyStr += cellText + " ";
                qDebug() << "Dark blue cell:" << cellText;
            }
        }
        copyStr += "\n";
    }
    //QApplication::clipboard()->setText(copyStr.left(copyStr.size() - 1));
    //qDebug() << "Copied to clipboard:" << copyStr.left(copyStr.size() - 1);
    mixAnalysis_data2Bcopy = copyStr.left(copyStr.size() - 1);


    // 显示消息框通知用户复制成功
    //QMessageBox::information(this, tr("复制成功"), tr("选中文本已复制到剪切板"));
}
