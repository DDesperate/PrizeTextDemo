#ifndef DOWNSTRUCT_H
#define DOWNSTRUCT_H

#include <QString>
#include <QColor>
#include <QList>
#include <QVector>

struct slcInfo {
    QColor color;
    quint8 prize;
    bool isSelect = false;
    bool isDeleted = false;

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
};

// ========== 新增：稀疏数组行结构 ==========
struct SparseRow {
    bool isSelected = false;
    bool isSeparator = false;  // 红色横线分隔行
    QString date;
    QVector<slcInfo> prizes;  // 固定81个元素，索引0不用，索引1-80对应奖注号
    
    SparseRow() {
        prizes.resize(81);  // 初始化81个元素
    }
    
    // 判断某个位置是否有奖注
    bool hasPrize(int col) const {
        if (col < 1 || col > 80) return false;
        return prizes[col].prize != 0;
    }
};

// ========== 原有结构保持不变 ==========
struct slctTbRow {
    bool isSelected = false;
    QString date;
    QList<slcInfo> prizes;

    bool myContains(quint8 prizeToCheck) const {
        for (const slcInfo &info : prizes) {
            if (info.prize == prizeToCheck) {
                return true;
            }
        }
        return false;
    }

    int prizesSize() const {
        return prizes.size();
    }
    
    // ========== 新增：转换为稀疏数组 ==========
    SparseRow toSparseRow() const {
        SparseRow sparse;
        sparse.isSelected = this->isSelected;
        sparse.date = this->date;
        
        // 将列表中的奖注映射到稀疏数组对应位置
        for (const slcInfo &info : this->prizes) {
            int prizeNum = info.prize;
            if (prizeNum >= 1 && prizeNum <= 80) {
                sparse.prizes[prizeNum] = info;
            }
        }
        
        return sparse;
    }
};

#endif // DOWNSTRUCT_H
