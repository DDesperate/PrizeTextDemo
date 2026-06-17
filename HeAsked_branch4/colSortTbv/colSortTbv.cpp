#include "colSortTbv.h"
#include <QHeaderView>
ColSortTbv::ColSortTbv(QWidget *parent):PrizeTableView(parent){

    // 设置右键菜单策略
    setContextMenuPolicy(Qt::CustomContextMenu);

    // 连接右键菜单信号到槽函数
    connect(this, &ColSortTbv::customContextMenuRequested, this, &ColSortTbv::showContextMenu_colSort);

    //委托ColSortTbvDelegate中的数据结构colSortData与表格ColSortTbv中的数据结构绑定
    //指向同一块地址，后面修改dataVec的地址中的数据，就可以使得表格中的显示予以变化
    colSortDataTableD.colSortData = &dataVec;

    //用于将计算好的分界线数组传给colSortDataTableD
    colSortDataTableD.markCol = &boundaries;

    //将委托应用到DownTableView中
    setItemDelegate(&colSortDataTableD);
}

ColSortTbv::~ColSortTbv(){

}

// 函数用于打印prizeMatrixWithDate的内容
void ColSortTbv::printPrizeMatrixWithDate(const QVector<PrizeRowWithDate>& matrix) {
    for (const auto& row : matrix) {
        qDebug() << row.date << ": " << row.prizes;
    }
}


QVector<PrizeRowWithDate> ColSortTbv::convertToPrizeMatrix(const QVector<slctTbRow>& elements) {
    QVector<PrizeRowWithDate> prizeMatrixWithDate;
    const int targetSize = 80; // 目标大小为80

    for (const auto& row : elements) {
        PrizeRowWithDate prizeRowWithDate;
        prizeRowWithDate.date = row.date; // 设置日期

        // 初始化奖品向量为80个0
        prizeRowWithDate.prizes.fill(0, targetSize);

        // 按顺序设置奖品，保持原有数字的位置
        for (const auto& prizeInfo : row.prizes) {
            if (prizeInfo.prize > 0 && prizeInfo.prize <= targetSize) {
                // 确保奖品数字在1-80之间
                prizeRowWithDate.prizes[prizeInfo.prize - 1] = prizeInfo.prize;
            }
        }

        prizeMatrixWithDate.append(prizeRowWithDate); // 添加到结果向量
    }

    return prizeMatrixWithDate;
}

// 辅助函数，用于计算给定列的非零元素数量
int ColSortTbv::countNonZero(const QVector<PrizeRowWithDate>& matrix, int colIndex) {
    int count = 0;
    for (const auto& row : matrix) {
        if (colIndex < row.prizes.size() && row.prizes[colIndex] != 0) {
            ++count;
        }
    }
    return count;
}

//根据每一列中奖次数的多少，对整个奖品矩阵的列进行重新排序，并记录下不同中奖次数的列之间的分界点
void ColSortTbv::sortByNonZeroCount(QVector<PrizeRowWithDate>& prizeMatrixWithDate, QVector<int>& boundaries) {
    boundaries.clear(); // 清空分界点数组

    // 各列索引
    int cols = prizeMatrixWithDate.isEmpty() ? 0 : prizeMatrixWithDate.first().prizes.size();
    QVector<int> colIndices(cols);
    for (int i = 0; i < cols; ++i) {
        colIndices[i] = i;
    }

    // 预计算每列的非零元素数量和元素值
    QVector<int> nonZeroCounts(cols, 0);
    QVector<int> colValues(cols, 0);

    for (int col = 0; col < cols; ++col) {
        int count = 0;
        int value = 0;
        bool foundValue = false;

        for (const auto& row : prizeMatrixWithDate) {
            if (col < row.prizes.size() && row.prizes[col] != 0) {
                count++;
                if (!foundValue) {
                    value = row.prizes[col];
                    foundValue = true;
                }
            }
        }

        nonZeroCounts[col] = count;
        colValues[col] = value;
    }

    // 按非零元素数量升序排列，数量相同时按元素值降序排列
    std::sort(colIndices.begin(), colIndices.end(), [&](int a, int b) {
        if (nonZeroCounts[a] != nonZeroCounts[b]) {
            return nonZeroCounts[a] < nonZeroCounts[b];
        } else {
            return colValues[a] < colValues[b];
        }
    });

    // 找出所有分界点
    for (int i = 0; i < cols - 1; ++i) {
        int currentCol = colIndices[i];
        int nextCol = colIndices[i + 1];
        if (nonZeroCounts[currentCol] != nonZeroCounts[nextCol]) {
            boundaries.append(i); // 记录分界点索引
        }
    }

    // 重新排列每行的奖品向量
    for (auto& row : prizeMatrixWithDate) {
        QVector<quint8> sortedPrizes(cols);
        for (int i = 0; i < cols; ++i) {
            int colIndex = colIndices[i];
            if (colIndex < row.prizes.size()) {
                sortedPrizes[i] = row.prizes[colIndex];
            } else {
                sortedPrizes[i] = 0;
            }
        }
        row.prizes = sortedPrizes;
    }
}



void ColSortTbv::dbClkDate(QModelIndex const &Index) {
    // 不实现任何功能
}

//根据传入的 "奖注数据" 计算出 "被标记的列" 及其 "被标记的类型" ( "绿色高亮" , "划掉" 等)
//返回参数一是被标记的列
//返回参数二是被划掉的列
QPair<QVector<int>, QVector<int>> ColSortTbv::calculateMarkedColumnTypes(const QVector<slctTbRow>& data) {
    QSet<int> selectedSet;  // 自动去重的集合
    QSet<int> deletedSet;

    for(const auto& row : data) {
        for(const auto& item : row.prizes) {
            if(item.isSelect) selectedSet.insert(item.prize);
            if(item.isDeleted) deletedSet.insert(item.prize);
        }
    }

    // 转换为QVector返回
    return qMakePair(
        selectedSet.values().toVector(),
        deletedSet.values().toVector()
        );
}


// 打印qMakePair检验函数
void printQMakePair(const QPair<QVector<int>, QVector<int>>& pair) {
    qDebug() << "==== Selected Columns ====";
    for (int col : pair.first) {
        qDebug() << "Column" << col << "is selected";
    }

    qDebug() << "\n==== Deleted Columns ====";
    for (int col : pair.second) {
        qDebug() << "Column" << col << "has deleted items";
    }
}


//从外部输入数据 并在此函数中进行处理
void ColSortTbv::inputAndSortData(const QVector<slctTbRow> &data)
{
    //获取被标记的列,及其被标记的类型
    QPair<QVector<int>, QVector<int>> markedCol = calculateMarkedColumnTypes(data);

    //用于测试的函数
    //printQMakePair(markedCol);

    //把被 标记/被划掉的列 数据送给colSortDataTableD(委托) 委托会在作图时标记
    colSortDataTableD.markCol_Green = markedCol.first;
    colSortDataTableD.markCol_Strike = markedCol.second;

    ///处理数据

    //elements 补0 获得 prizeMatrixWithDate
    //整理数据，方便被sortByNonZeroCount处理
    QVector<PrizeRowWithDate> prizeMatrixWithDate = convertToPrizeMatrix(data);

    //根据每一列中奖次数的多少，对整个奖品矩阵的列进行重新排序，并记录下不同中奖次数的列之间的分界点
    sortByNonZeroCount(prizeMatrixWithDate,boundaries);

    //详情见构造函数
    //委托ColSortTbvDelegate中的数据结构colSortData与表格ColSortTbv中的数据结构绑定
    //指向同一块地址，后面修改dataVec的地址中的数据，就可以使得表格中的显示予以变化.
    dataVec = prizeMatrixWithDate;

    ///处理数据

    //行数清零
    this->clearModel();

    //为表格添加空行数,后面才可以填入数据
    for(int count = 0;count < prizeMatrixWithDate.count(); count ++){
        this->addOneModelRow();
    }

    //刷新
    refreshTbv();
}


