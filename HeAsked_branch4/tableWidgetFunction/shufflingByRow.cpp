#include "widget.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QVector>
#include <QPair>
#include <QSet>
#include <QRandomGenerator>
#include <QFile>
#include <QTextStream>
#include <algorithm>



//判断二维数组中的任意一行有无重复元素
bool containsDuplicateRows(const QVector<QVector<quint8>>& array) {
    for (const auto& row : array) {
        // 先对每行进行排序
        QVector<quint8> sortedRow = row;
        std::sort(sortedRow.begin(), sortedRow.end());

        // 检查排序后的行是否有相邻的重复元素
        for (int i = 1; i < sortedRow.size(); ++i) {
            if (sortedRow[i] == sortedRow[i - 1]) {
                return true; // 找到重复元素，返回true
            }
        }
    }
    return false; // 没有找到重复元素，返回false
}

//返回一个数组中的重复元素
QVector<quint8> findDuplicates(const QVector<quint8>& vector) {
    QSet<quint8> set;
    QVector<quint8> duplicates;
    for (quint8 value : vector) {
        if (set.contains(value)) {
            // 如果集合中已经存在该元素，则添加到重复元素的列表中
            duplicates.append(value);
        } else {
            set.insert(value);
        }
    }
    return duplicates;
}

//判断二维数组中的指定两行是否有重复元素
bool haveCommonElements(const QVector<QVector<quint8>>& array, const QPair<int, int>& rows, const QString& logFilePath) {
    QFile logFile(logFilePath);
    if (!logFile.open(QIODevice::Append | QIODevice::Text)) {
        qWarning() << "Cannot open log file for writing.";
        return false;
    }

    QTextStream logStream(&logFile);

    // 日志输出：函数被调用
    logStream << "Checking for common elements between row " << rows.first << " and row " << rows.second << ".\n";


    // 获取指定行
    const QVector<quint8>& firstRow = array[rows.first];
    const QVector<quint8>& secondRow = array[rows.second];

    //分别获取两行中的重复元素
    QVector<quint8> firstDuplicates = findDuplicates(firstRow);
    QVector<quint8> secondDuplicates = findDuplicates(secondRow);

    // 打印被选出的两行,以及其中的重复元素
    QString firstRowString,secondRowString;
    for (quint8 elem : firstRow) {
        firstRowString += QString::number(elem) + " "; // 将每个元素转换为字符串并拼接
    }
    for (quint8 elem : secondRow) {
        secondRowString += QString::number(elem) + " "; // 将每个元素转换为字符串并拼接
    }

    //打印行1,判断其中有无重复元素,如果有则列出
    logStream << "Row: " << rows.first << "\n" << "elements:" << firstRowString  << "\n";
    if(firstDuplicates.isEmpty()){
        logStream << "There is no common elements" << "\n";
    }
    else{
        QString firstDuplicateString;
        for(quint8 elem : firstDuplicates){
            firstDuplicateString += QString::number(elem) + " "; // 将每个元素转换为字符串并拼接
        }
        logStream << "common elements:" << firstDuplicateString << "\n";
    }

    //打印行2,判断其中有无重复元素,如果有则列出
    logStream << "Row: " << rows.second << "\n" << "elements:" << secondRowString << "\n";
    if(secondDuplicates.isEmpty()){
        logStream << "There is no common elements" << "\n";
    }
    else{
        QString secondDuplicateString;
        for(quint8 elem : secondDuplicates){
            secondDuplicateString += QString::number(elem) + " "; // 将每个元素转换为字符串并拼接
        }
        logStream << "common elements:" << secondDuplicateString << "\n";
    }

    //结束一次检测空出一行
    logStream << "check end" <<"\n\n";

    logFile.close();

    //只有两行中都没有重复元素返回值为真
    bool result = firstDuplicates.empty() && secondDuplicates.empty();

    return !result;
}

//对二维数组中的每一行排序
void sortAllRows(QVector<QVector<quint8>>& array) {
    // 遍历二维数组中的每一行
    for (QVector<quint8>& row : array) {
        // 使用Qt的qSort函数对每一行进行排序
        qSort(row.begin(), row.end());
    }
}

//从lowerBound-upperBound之间随机生成minCount-maxCount个数,返回这些数组成的容器
template<typename T>
QVector<T> generateRandomIndices(T lowerBound, T upperBound, int minCount, int maxCount) {
    // 创建一个空的QVector
    QVector<T> selectedColIndices;

    // 生成minCount到maxCount个随机数
    int count = QRandomGenerator::global()->bounded(minCount, maxCount + 1);

    for (int i = 0; i < count; ++i) {
        // 生成lowerBound到upperBound之间的随机数
        T randomNumber = static_cast<T>(QRandomGenerator::global()->generateDouble() * (upperBound - lowerBound) + lowerBound);
        // 将随机数添加到QVector中
        selectedColIndices.append(randomNumber);
    }

    return selectedColIndices;
}

//根据行数m返回一个多对数据(从一列数据中随机取m / 4 + 1 对数据,m>2)
QList<QPair<int, int>> getRandomUniquePairs(int m) {
    QList<QPair<int, int>> pairs;
    int n = m / 4 + 1; // 根据你的要求计算n的值

    // 确保m大于等于2
    if (m < 2) {
        qWarning("m must be greater than or equal to 2.");
        return pairs;
    }

    for (int i = 0; i < n; ++i) {
        int first = QRandomGenerator::global()->generate() % m;
        int second;
        do {
            second = QRandomGenerator::global()->generate() % m;
        } while (first == second); // 确保两个数不相同
        pairs.append(QPair<int, int>(first, second));
    }
    return pairs;
}

//交换并且检查,交换之后两行中有怨妇重复,则撤销交换操作
void swap_check(QVector<QVector<quint8>> &array,int columnIndex,QPair<int,int> p)
{
    //设置haveCommonElements函数日志路径
    QString haveCommonElements_logFilePath = "logHaveCommonElements.txt";

    // 保存原始值以备撤销交换
    quint8 temp = array[p.first][columnIndex];

    // 执行交换操作
    array[p.first][columnIndex] = array[p.second][columnIndex];
    array[p.second][columnIndex] = temp;

    // 检查是否有重复元素
    if (haveCommonElements(array, p,haveCommonElements_logFilePath)) {
        // 如果有重复元素，撤销交换操作
        array[p.second][columnIndex] = array[p.first][columnIndex];
        array[p.first][columnIndex] = temp;
    }
}

//对二维数组array的第columnIndex列洗牌
void shuffleColumn(QVector<QVector<quint8>> &array, int columnIndex) {
    if (columnIndex < 0 || columnIndex >= array.first().size()) {
        // 如果列索引超出范围，则不执行任何操作
        return;
    }

    // 获取数组的行数
    int rowCount = array.size();

    // 根据行数rowCount随机取m / 4 + 1 对数据
    QList<QPair<int, int>> pairs = getRandomUniquePairs(rowCount);

    // 根据随机出来的pairs对多个元素交换
    for(QPair<int,int> p:pairs){
        //交换后可能有两行重复,若重复则撤销此操作,故可能交换失败
        swap_check(array,columnIndex,p); //swp为真则交换成功
    }
}

//去重
QVector<quint8> removeDuplicates(const QVector<quint8>& vectorWithDuplicates) {
    QSet<quint8> uniqueSet(vectorWithDuplicates.begin(), vectorWithDuplicates.end());
    return QVector<quint8>(uniqueSet.begin(), uniqueSet.end());
}



//对二维数组洗牌(每一列中的各个元素随机调换)
void shuffling2DArrayByCol(QVector<QVector<quint8>>& prize2DArray) {
    //二维数组为空或者一列都没有则直接返回
    if (prize2DArray.isEmpty() || prize2DArray[0].isEmpty()) {
        return;
    }

    //从0-20之间随机生成5-15个数，放到randomIndices中
    QVector<quint8> randomIndices = generateRandomIndices<quint8>(0, 20, 5, 15);

    //对随机选出的这些列洗牌
    for(quint8 columnIndex : randomIndices){
        shuffleColumn(prize2DArray,columnIndex);
    }
}



////合并期数与奖注形成的二维数组并转换为QStringList返回
QStringList combineIssueNumAndPrizes(const QVector<QString>& issue_num, const QVector<QVector<quint8>>& prize2DArray) {
    QStringList result;

    for (int i = 0; i < issue_num.size(); ++i) {
        QString row = issue_num[i];

        //去重
        //QVector<quint8> vectorAfterRemoveDuplicates = removeDuplicates(prize2DArray[i]);
        for (quint8 prize : prize2DArray[i]) {
            row += " " + QString::number(prize).rightJustified(2,'0');
        }

        result.append(row);
    }

    return result;
}

//遍历表中前rowCount行数据转化为一个一维数组(期数)和一个二维数组(奖注数据)
void TraversalTable(QVector<QString> &issue_num,QVector<QVector<quint8>> &prize2DArray,QTableWidget *dataTable) {

    for(int row = 0; row <dataTable->rowCount(); row++)
    {
        issue_num << dataTable->item(row, 0)->text();
        QVector<quint8> rowData;
        for(int col = 1; col <= 20; col++)
        {
            rowData.append(dataTable->item(row,col)->text().toUInt());
        }
        prize2DArray << rowData;
    }
}

void sortPrize2DArray(QVector<QVector<quint8>>& prize2DArray) {
    for (QVector<quint8>& row : prize2DArray) {
        qSort(row.begin(), row.end());
    }
}

void Widget::shufflingByCol(QVector<QString> &issue_num,QVector<QVector<quint8>> &prize2DArray)
{

    //遍历表中数据转化为一个一维数组(期数)和一个二维数组(奖注数据)
    TraversalTable(issue_num,prize2DArray,dataTable_randomshuffling);

    //对二维数组洗牌(每一列中的各个元素随机调换)
    shuffling2DArrayByCol(prize2DArray);

    //对二维数组每一行进行排序
    sortPrize2DArray(prize2DArray);
}
