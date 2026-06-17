#include "widget.h"
#include <QDebug>

void Widget::copySelectedItem(QTableWidget *tbwgt)
{
    QList<int> selectCol = getSelectedIndices(tbwgt,true);
    QList<int> selectRow = getSelectedIndices(tbwgt,false);
    qSort(selectCol.begin(),selectCol.end());
    qSort(selectRow.begin(),selectRow.end());

    //qDebug() << "col" << selectCol;
    //qDebug() << "row" << selectRow;


    if(selectRow.isEmpty() || selectCol.isEmpty())
        return;

    QString clipboardText;

    // 遍历选中的行和列
    for(int row : selectRow) {
        QStringList rowText;
        for(int col : selectCol) {
            QTableWidgetItem* item = tbwgt->item(row, col);
            rowText << (item ? item->text() : "");
        }
        clipboardText += rowText.join("\t") + "\n";
    }

    // 将文本放入剪贴板
    QApplication::clipboard()->setText(clipboardText.trimmed());
}
