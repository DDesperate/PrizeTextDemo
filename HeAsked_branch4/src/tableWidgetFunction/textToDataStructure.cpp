#include "widget.h"
//暂时没有检查每一行的数据是否符合格式
//没有检查数字是否可能超出80
QVector<QList<quint8>> Widget::textToDataStructure(const QString &text)
{
    QVector<QList<quint8>> dataStruct;

    // 分割字符串并去除首尾空格
    QStringList strList = text.trimmed().split("\n");

    // 遍历导入的txt数据
    int row = 0;
    for (const QString& rowString : strList)
    {
        row++;

        // 跳过空行
        if (rowString.isEmpty())
            continue;

        QList<quint8> dataStructRow;

        // 分割并去除两端可能存在的空格
        QStringList prizeList = rowString.trimmed().split(" ");

        // 将字符串转换为quint8并添加到列表中
        for (const QString& prize : prizeList)
        {
            if(!prize.isEmpty())
            {
                if(prize.toInt()>80 || prize.toInt() <1)
                    QMessageBox::warning(nullptr,
                                         "out of range",
                                         tr("row:") + QString::number(row) + '\n' + QString::number(prize.toInt()));
                dataStructRow.append(static_cast<quint8>(prize.toInt()));
            }

        }

        dataStruct.append(dataStructRow);
    }

    return dataStruct;
}
