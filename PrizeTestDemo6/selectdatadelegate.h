#ifndef SELECTDATADELEGATE_H
#define SELECTDATADELEGATE_H

#include <QStyledItemDelegate>
#include <QVector>
#include "downstruct.h"

class SelectDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SelectDataDelegate(QObject *parent = nullptr);

    // 原有方法（主窗口使用）
    void setSelectData(QVector<slctTbRow> *data);
    
    // 新增：设置稀疏数组数据（子窗口使用）
    void setSparseData(QVector<SparseRow> *data);

    // 列映射：displayColToNumber[col]=该列显示的数字(1-80)，空表示恒等映射
    void setColumnMapping(const QVector<int> &mapping);

    // 按块映射：每块独立，blockMappings[blockIndex][slot]=该列显示的数字
    void setBlockColumnMappings(const QVector<QVector<int>> &blockMappings);

    // 按块列分隔：每块需画红竖线的列索引（在该列左侧）
    void setBlockColumnDividers(const QVector<QVector<int>> &blockDividers);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    // 稀疏数组绘制方法
    void paintSparse(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;
    
    // 原始数据绘制方法
    void paintOriginal(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;

    QVector<slctTbRow> *delegateSelectDataVec = nullptr;  // 原始数据
    QVector<SparseRow> *delegateSparseDataVec = nullptr;  // 稀疏数组数据
    QVector<int> m_displayColToNumber;      // 单块/恒等映射
    QVector<QVector<int>> m_blockMappings;  // 每块独立映射，空表示用恒等
    QVector<QVector<int>> m_blockDividers;  // 每块的红竖线列（在该列左侧绘制）

    // 标识当前使用哪种数据源
    bool useSparseData = false;
};

#endif // SELECTDATADELEGATE_H
