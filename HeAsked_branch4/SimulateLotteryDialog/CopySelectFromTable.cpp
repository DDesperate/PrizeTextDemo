#include"simulatelotterydialog.h"
#include<QTableWidgetSelectionRange>
#include<QApplication>
#include<QClipboard>
void SimulateLotteryDialog::CopySelectFromTable(QTableWidget*tbwgt)
{
    //QTableWidgetSelectionRange 可以用于访问被选中的单元格范围信息(具体如何做的？)
    QList<QTableWidgetSelectionRange> sRangeList = tbwgt->selectedRanges();
    for(const auto &p : qAsConst(sRangeList)) { //qAsConst 用于确保容器的 const 安全性，表示返回一个 const 引用。保证循环可以在不修改容器元素的情况下，遍历 sRangeList 容器中的每个元素 p
        QString str;
        for (auto i = p.topRow(); i <= p.bottomRow(); i++) {
            QString rowStr;
            for (auto j = p.leftColumn(); j <= p.rightColumn(); j++) {
                QTableWidgetItem* item =  tbwgt->item(i, j);
                if(item != nullptr) {
                    if(j == p.leftColumn())
                        rowStr = item->text() + "\t";
                    else if (j == p.rightColumn())
                        rowStr = rowStr + item->text() + "\n";
                    else
                        rowStr = rowStr + item->text() + "\t";
                }
                else {
                    break;
                }
            }
            str += rowStr;
        }
        QApplication::clipboard()->setText(str.left(str.size() - 1));
//        clipboard= QApplication::clipboard();
//        clipboard->setText(str);
    }
}
