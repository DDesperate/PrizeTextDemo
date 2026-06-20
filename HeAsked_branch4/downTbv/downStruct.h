#ifndef DOWNSTRUCT_H
#define DOWNSTRUCT_H

#include<QString>
#include<QColor>
#include<QVector>

typedef struct {
    QColor color;
    quint8 prize;
    bool isSelect;
    bool isDeleted;

    void setSelected(){
        //只有该项没有被划掉时才能被选中
        if(isDeleted != true)
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

}slcInfo;

struct SparseRow {
    bool isSelected = false;
    bool isSeparator = false;
    QString date;
    QVector<slcInfo> prizes;

    SparseRow() { prizes.resize(81); }

    bool hasPrize(int col) const {
        return col >= 1 && col <= 80 && prizes[col].prize != 0;
    }
};

typedef struct{
    bool isSelected;
    QString date;
    QList<slcInfo> prizes;

    bool myContains(quint8 prizeToCheck) const {
        foreach(const slcInfo &info, prizes) {
            if (info.prize == prizeToCheck) { // 修正运算符
                return true;
            }
        }
        return false; // 添加缺失的 return 语句
    }

    int prizesSize() const {
        return prizes.size();
    }

    SparseRow toSparseRow() const {
        SparseRow sparse;
        sparse.isSelected = this->isSelected;
        sparse.date = this->date;
        for (const slcInfo &info : this->prizes) {
            int n = info.prize;
            if (n >= 1 && n <= 80) sparse.prizes[n] = info;
        }
        return sparse;
    }
}slctTbRow;

#endif
