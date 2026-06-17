#ifndef SPARSESTRUCT_H
#define SPARSESTRUCT_H

#include <QString>
#include <QColor>
#include <QVector>

/**
 * @brief 单个奖注信息（稀疏数组格式）
 */
struct SparsePrizeInfo {
    QColor color = Qt::transparent;
    quint8 prize = 0;          // 0 表示无奖注，非0表示有奖注
    bool isSelect = false;
    bool isDeleted = false;

    // 判断是否有奖注
    bool hasPrize() const { return prize != 0; }

    void setSelected() {
        if (!isDeleted)
            isSelect = true;
    }

    void switchSelect() {
        isSelect = !isSelect;
        if (isSelect) {
            isDeleted = false;
        }
    }

    void setDeleted(bool value) {
        isDeleted = value;
        if (isDeleted) {
            isSelect = false;
        }
    }
    
    // 清空奖注信息
    void clear() {
        color = Qt::transparent;
        prize = 0;
        isSelect = false;
        isDeleted = false;
    }
};

/**
 * @brief 稀疏数组行结构（固定81列，索引1-80对应奖注号）
 */
struct SparseRow {
    bool isSelected = false;
    QString date;
    QVector<SparsePrizeInfo> prizes;  // 固定81个元素，索引0不用
    
    // 构造函数：初始化81个元素
    SparseRow() {
        prizes.resize(81);
    }
    
    // 判断某个列位置是否有奖注
    bool hasPrizeAt(int col) const {
        if (col < 1 || col > 80) return false;
        return prizes[col].hasPrize();
    }
    
    // 获取某个位置的奖注信息（只读）
    const SparsePrizeInfo& getPrize(int col) const {
        static SparsePrizeInfo empty;
        if (col < 1 || col > 80) return empty;
        return prizes[col];
    }
    
    // 获取某个位置的奖注信息（可修改）
    SparsePrizeInfo& getPrize(int col) {
        static SparsePrizeInfo empty;
        if (col < 1 || col > 80) {
            empty.clear();
            return empty;
        }
        return prizes[col];
    }
    
    // 设置某个位置的奖注信息
    void setPrize(int col, const SparsePrizeInfo &info) {
        if (col >= 1 && col <= 80) {
            prizes[col] = info;
        }
    }
    
    // 清空某个位置的奖注
    void clearPrize(int col) {
        if (col >= 1 && col <= 80) {
            prizes[col].clear();
        }
    }
    
    // 统计有效奖注数量
    int prizeCount() const {
        int count = 0;
        for (int i = 1; i <= 80; ++i) {
            if (prizes[i].hasPrize()) {
                count++;
            }
        }
        return count;
    }
};

/**
 * @brief 稀疏数组表格数据类型
 */
using SparseTableData = QVector<SparseRow>;

#endif // SPARSESTRUCT_H
