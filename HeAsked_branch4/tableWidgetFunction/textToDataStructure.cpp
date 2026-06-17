#include "widget.h"
#include <QRegularExpression>
//暂时没有检查每一行的数据是否符合格式
//没有检查数字是否可能超出80
//返回值为 0，代表空值
//返回值为 1，代表正常
//返回值为 -1,代表出现错误
QPair<int,QString> Widget::textToDataStructure(QVector<QList<quint8>> &data, const QString &text)
{

    if (text.isEmpty()) {
            return QPair<int,QString> (0,"输入值为空");
    }

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
        int col = 0;
        for (const QString& prize : prizeList)
        {
            col ++;

            if(!prize.isEmpty())
            {
                QRegularExpression regex("\\b\\d{4}-\\d{3}\\b");
                if(regex.match(prize).hasMatch())
                {
                    continue;
                }
                else if(prize.toInt()>80 || prize.toInt() <1){
                    QString errorInfo = "超出范围: \n行:" + QString::number(row) + "列:" + QString::number(col) + "\n值:" + prize;//一旦发现数据不对，直接返回空值。
                    return QPair<int,QString> (-1,errorInfo);
                }

                dataStructRow.append(static_cast<quint8>(prize.toInt()));
            }

        }

        data.append(dataStructRow);
    }

    return QPair<int,QString> (1,"");
}
