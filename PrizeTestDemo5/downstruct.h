#ifndef DOWNSTRUCT_H
#define DOWNSTRUCT_H

#include <QString>
#include <QColor>
#include <QList>

/**
 * @brief 单个奖注信息（原始格式）
 */
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

/**
 * @brief 表格行数据（原始格式，主窗口使用）
 */
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
};

#endif // DOWNSTRUCT_H
