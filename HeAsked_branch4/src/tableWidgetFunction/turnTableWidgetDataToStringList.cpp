#include "widget.h"
QStringList Widget::turnTableWidgetDataToStrList()
{
    QStringList strList;

    for (int row = 0; row < dataTable->rowCount(); ++row) {
        QString str;
        for (int column = 0; column < dataTable->columnCount(); ++column) {
            QTableWidgetItem* item = dataTable->item(row, column);
            if (item) {
                str += item->text().trimmed()+" ";
            }
        }
        str = str.trimmed() + '\n';
        strList.append(str);
    }

    return strList;
}
