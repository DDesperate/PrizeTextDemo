#include "genericfunc.h"


quint8 QStringToQuint8(const QString& str) {
    bool ok;
    quint8 value = str.toUInt(&ok, 10); // 使用基数为10来确保正确解析
    if (!ok || value > 255) {
        // 如果转换失败或值超出范围，处理错误情况
        //QMessageBox::warning(nullptr,"warning","String conversion to quint8 failed or out of range:" << str);
        return 0; // 或者你可以根据需要返回一个错误标志
    }
    return value;
}

QList<quint8> getCommonItems(const QList<quint8>& list1, const QList<quint8>& list2)
{
    QSet<quint8> set;
    QList<quint8> commonItems;

    // 将 list1 中的元素添加到 set
    for (const quint8& item : list1)
    {
        set.insert(item);
    }

    // 遍历 list2，将存在于 set 中的元素添加到 commonItems
    for (const quint8& item : list2)
    {
        if (set.contains(item))
        {
            commonItems.append(item);
        }
    }

    return commonItems;
}

QList<quint8> getUnion(const QList<quint8>& list1, const QList<quint8>& list2)
{
    QSet<quint8> set;

    // 将 list1 中的元素添加到 set
    for (const quint8& item : list1)
    {
        set.insert(item);
    }

    // 将 list2 中的元素添加到 set
    for (const quint8& item : list2)
    {
        set.insert(item);
    }

    // 将 set 转换为 QList 并返回
    return set.toList();
}

//除去一个矩阵中的两个相同数列
//举例:
//去重前:
//1,2,3,4
//1,2,3,4
//1,2,3,4,5,6
//去重后:
//1,2,3,4
//1,2,3,4,5,6
QVector<QList<quint8>> removeDuplicates(const QVector<QList<quint8>>& input) {
    QVector<QList<quint8>> result;
    QSet<QString> seen; // 用于记录已经见过的列表

    for (const QList<quint8>& list : input) {
        // 将QList<quint8>转换为一个可以哈希的形式，例如一个QString
        QString key;
        for (quint8 item : list) {
            key.append(QString::number(item) + ",");
        }

        // 检查这个转换后的key是否已经出现过
        if (!seen.contains(key)) {
            seen.insert(key);
            result.append(list);
        }
    }

    return result;
}


QString prizeListToString(const QList<quint8> &list)
{
    QStringList stringList;
    for (quint8 value : list) {
        stringList.append(QString::number(value).rightJustified(2,'0'));
    }
    QString result = stringList.join(" ");
    return result;
}

QString formatQVectorQListToString(const QVector<QList<quint8>>& data) {
    QString resultText;
    for (const QList<quint8>& row : data) {
        for (quint8 value : row) {
            resultText += QString::number(value).rightJustified(2, '0') + " ";
        }
        resultText += "\n";
    }
    return resultText;
}

QString formatQVectorQListToStringWithCounts(const QVector<QList<quint8>>& data) {
    QString resultText;
    for (const QList<quint8>& row : data) {
        for (quint8 value : row) {
            resultText += QString::number(value).rightJustified(2, '0') + " ";
        }
        // 添加该行的元素个数
        resultText += "元素个数:" + QString::number(row.size()) + "\n";
    }
    return resultText;
}


QVector<QList<quint8>> parseStringToQVectorQList(const QString& str) {
    QVector<QList<quint8>> resultData;

    QStringList lines = str.split("\n", QString::SkipEmptyParts);
    for (const QString& line : lines) {
        QStringList values = line.trimmed().split(" ", QString::SkipEmptyParts);
        QList<quint8> row;
        for (const QString& value : values) {
            bool ok;
            quint8 num = value.toUInt(&ok);
            if (ok)
                row.append(num);
            else
                //qDebug() << "Error converting value to quint8";
                ;
        }
        resultData.append(row);
    }

    return resultData;
}

//初始化表格
void initTableWidget(QTableWidget* tbwgt)
{
    //设置列头文本
    tbwgt->insertColumn(0);
    //期数:
    tbwgt->setHorizontalHeaderItem(0,new QTableWidgetItem(QString::fromUtf8("期数")));
    //1-20:
    for(int i=1;i<=20;i++){
        tbwgt->insertColumn(i);
        tbwgt->setHorizontalHeaderItem(i,new QTableWidgetItem(QString::number(i)));
    }

    //设置第一列列头宽度自适应文本
    tbwgt->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
    //设置1到20列列头可拉伸(设置之前会有很大一部分在编辑框之外，拖动滚动条才能显示)
    for(int i=1;i<=20;i++){
            tbwgt->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Stretch);
    }

    //美化:
    //列头(第一行)上色
    tbwgt->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;color: black;}");

    //设置选中紫色
    tbwgt->setStyleSheet("selection-background-color: #aa00ff");

    //设置item不可编辑
    tbwgt->setEditTriggers(QAbstractItemView::NoEditTriggers);
}


// 插入一个空行到QTableWidget中
void insertEmptyRow(QTableWidget *tbwgt, int rowPosition) {
    // 如果rowPosition是-1，则新行将被添加到表格的末尾
    // 否则，它将在指定的行位置插入新行
    int newRowPosition = (rowPosition == -1) ? tbwgt->rowCount() : rowPosition;

    // 插入新行
    tbwgt->insertRow(newRowPosition);

    // 获取列数
    int columnCount = tbwgt->columnCount();

    // 设置新行的每个单元格为空
    for (int column = 0; column < columnCount; ++column) {
        QTableWidgetItem *emptyItem = new QTableWidgetItem();
        tbwgt->setItem(newRowPosition, column, emptyItem);
    }
}

//获取被选中的索引
QList<int> getSelectedIndices(QTableWidget *tbwgt, bool selectColumns)
{
    //获取选择模型的指针
    QItemSelectionModel *selections =  tbwgt->selectionModel();
    //获取被选中的指针列表
    QModelIndexList selected = selections->selectedIndexes();

    QList<int> rowList;
    //qDebug() << "rowList" << rowList;
    foreach (QModelIndex index, selected) {
        if (selectColumns) {
            rowList.append(index.column());
        } else {
            rowList.append(index.row());
        }
    }
    //不知为何会获取到多个重复索引，故用QSet去重
   return rowList.toSet().toList();
}


// 自定义排序规则
// 用于给多个数组排序
/*
排序前
[2, 6, 22, 26, 33, 37, 46, 50, 62, 67],
[7, 9, 22, 32, 33, 37, 49, 58, 69, 73],
[3, 5, 22, 33, 35, 37, 53, 58, 69, 80],
[4, 8, 22, 32, 33, 37, 46, 60, 72, 77],
[1, 7, 22, 33, 37, 56, 62, 74, 78],
[5, 11, 22, 25, 33, 37, 39, 46, 69, 80],
[4, 7, 22, 28, 33, 37, 46, 53, 66, 75]
*/

/*
排序后
[1, 7, 22, 33, 37, 56, 62, 74, 78]
[2, 6, 22, 26, 33, 37, 46, 50, 62, 67]
[3, 5, 22, 33, 35, 37, 53, 58, 69, 80]
[4, 7, 22, 28, 33, 37, 46, 53, 66, 75]
[4, 8, 22, 32, 33, 37, 46, 60, 72, 77]
[5, 11, 22, 25, 33, 37, 39, 46, 69, 80]
[7, 9, 22, 32, 33, 37, 49, 58, 69, 73]
*/
bool customSort(const QList<quint8>& a, const QList<quint8>& b) {
    // 比较最小值
    auto minA = *std::min_element(a.begin(), a.end());
    auto minB = *std::min_element(b.begin(), b.end());
    if (minA != minB) {
        return minA < minB;
    }
    // 最小值相同，按字典序比较
    return a < b; // QList 支持字典序比较
}

//用于tab:剔除
QVector<QList<quint8>> excludeElements(
    const QVector<QList<quint8>>& dataStruct_originNum,
    const QVector<QList<quint8>>& dataStruct_numToBeExcluded) {

    QVector<QList<quint8>> dataStruct_result;

    // 遍历原始数据结构中的每个列表
    for (const auto& originList : dataStruct_originNum) {
        QList<quint8> resultList;

        // 遍历原始列表中的每个元素
        for (quint8 element : originList) {
            bool shouldExclude = false;

            // 检查元素是否在任何一个待排除的列表中
            for (const auto& excludeList : dataStruct_numToBeExcluded) {
                if (std::find(excludeList.begin(), excludeList.end(), element) != excludeList.end()) {
                    shouldExclude = true;
                    break; // 找到元素，标记为排除，并跳出循环
                }
            }

            // 如果元素不在排除列表中，则添加到结果列表
            if (!shouldExclude) {
                resultList.append(element);
            }
        }

        // 只有当结果列表非空时，才将其添加到结果数据结构中
        if (!resultList.isEmpty()) {
            dataStruct_result.append(resultList);
        }
    }

    return dataStruct_result;
}

//仅复制数据(不复制第一行。后面每行，在mark之后的部分不复制)
void copy_onlyPrize(const QString &text,QString mark)
{
    //分行装入数据结构QStringList lines;
    QStringList lines = text.split('\n');

    //移除首行字符串
    lines.removeFirst();

    //移除mark之后的部分
    for (int i = 0; i < lines.size(); ++i) {
        QString trimmedLine = lines[i].trimmed();
        int position = trimmedLine.indexOf(mark);
        if (position != -1) {
            QString truncatedLine = trimmedLine.left(position);
            lines[i] = truncatedLine;
        } else {
            // 如果没有找到" 出现次数"字符，则保持原字符串不变或按需处理
        }
    }

    QString modifiedString = lines.join('\n');
    QApplication::clipboard()->setText(modifiedString);
}

/**
 * @brief 获取当前选中的矩形区域信息
 * @param tableView 目标 QTableView
 * @param[out] startRow 起始行（-1 表示无选中）
 * @param[out] startCol 起始列（-1 表示无选中）
 * @param[out] rowCount 行数（高度）
 * @param[out] colCount 列数（宽度）
 * @return 是否成功获取选中区域
 */
bool getSelectedRectInfo(QTableView* tableView, int& startRow, int& startCol, int& rowCount, int& colCount) {
    if (!tableView || !tableView->selectionModel()) {
        startRow = -1;
        startCol = -1;
        rowCount = 0;
        colCount = 0;
        return false;
    }

    QItemSelectionModel* selectionModel = tableView->selectionModel();
    QModelIndexList selectedIndexes = selectionModel->selectedIndexes();

    if (selectedIndexes.isEmpty()) {
        startRow = -1;
        startCol = -1;
        rowCount = 0;
        colCount = 0;
        return false;
    }

    // 获取选中的范围（可能多个，这里取第一个）
    QItemSelectionRange range = selectionModel->selection().first();

    startRow = range.top()+1;     // 起始行    //根据实际情况最后决定+1
    startCol = range.left();    // 起始列
    rowCount = range.height();  // 行数（高度）
    colCount = range.width();   // 列数（宽度）

    return true;
}
