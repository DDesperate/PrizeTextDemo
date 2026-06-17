#include "dataconverter.h"

// ========== 原始格式 → 稀疏数组 ==========

SparseRow DataConverter::toSparseRow(const slctTbRow &row)
{
    SparseRow sparseRow;
    sparseRow.isSelected = row.isSelected;
    sparseRow.date = row.date;
    
    // 将奖注映射到稀疏数组的对应位置
    // 例如：prizes=[{prize:2}, {prize:6}, {prize:9}] 
    //      -> prizes[2]=info, prizes[6]=info, prizes[9]=info
    for (const slcInfo &info : row.prizes) {
        int prizeNum = info.prize;
        if (prizeNum >= 1 && prizeNum <= 80) {
            SparsePrizeInfo sparseInfo = toSparsePrizeInfo(info);
            sparseRow.setPrize(prizeNum, sparseInfo);
        }
    }
    
    return sparseRow;
}

SparseTableData DataConverter::toSparseData(const QVector<slctTbRow> &data)
{
    SparseTableData sparseData;
    sparseData.reserve(data.size());
    
    for (const slctTbRow &row : data) {
        sparseData.append(toSparseRow(row));
    }
    
    return sparseData;
}

// ========== 稀疏数组 → 原始格式 ==========

slctTbRow DataConverter::fromSparseRow(const SparseRow &sparseRow)
{
    slctTbRow row;
    row.isSelected = sparseRow.isSelected;
    row.date = sparseRow.date;
    
    // 遍历稀疏数组，提取有效奖注
    for (int i = 1; i <= 80; ++i) {
        if (sparseRow.hasPrizeAt(i)) {
            slcInfo info = fromSparsePrizeInfo(sparseRow.getPrize(i));
            row.prizes.append(info);
        }
    }
    
    return row;
}

QVector<slctTbRow> DataConverter::fromSparseData(const SparseTableData &sparseData)
{
    QVector<slctTbRow> data;
    data.reserve(sparseData.size());
    
    for (const SparseRow &sparseRow : sparseData) {
        data.append(fromSparseRow(sparseRow));
    }
    
    return data;
}

// ========== 辅助方法 ==========

SparsePrizeInfo DataConverter::toSparsePrizeInfo(const slcInfo &info)
{
    SparsePrizeInfo sparseInfo;
    sparseInfo.color = info.color;
    sparseInfo.prize = info.prize;
    sparseInfo.isSelect = info.isSelect;
    sparseInfo.isDeleted = info.isDeleted;
    return sparseInfo;
}

slcInfo DataConverter::fromSparsePrizeInfo(const SparsePrizeInfo &sparseInfo)
{
    slcInfo info;
    info.color = sparseInfo.color;
    info.prize = sparseInfo.prize;
    info.isSelect = sparseInfo.isSelect;
    info.isDeleted = sparseInfo.isDeleted;
    return info;
}
