#ifndef SPARSEDATADELEGATE_H
#define SPARSEDATADELEGATE_H

#include <QStyledItemDelegate>
#include <QVector>
#include "sparsestruct.h"

/**
 * @brief 子窗口专用代理类
 * 
 * 专门用于绘制稀疏数组格式的数据
 */
class SparseDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit SparseDataDelegate(QObject *parent = nullptr);
    
    void setSparseData(SparseTableData *data);
    
    // 设置按列分块的边界列（逻辑列号，1-80），用于绘制红色竖线
    void setBlockBoundaries(const QVector<int> &columns);
    void clearBlockBoundaries();
    
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    void paintDateCell(QPainter *painter, const QRect &rect, 
                       const SparseRow &rowData) const;
    void paintPrizeCell(QPainter *painter, const QRect &rect, 
                        const SparseRow &rowData, int col) const;
    void paintNormalPrize(QPainter *painter, const QRect &rect, 
                          const SparsePrizeInfo &prizeInfo) const;
    void paintSelectedPrize(QPainter *painter, const QRect &rect, 
                            const SparsePrizeInfo &prizeInfo) const;
    void paintDeletedPrize(QPainter *painter, const QRect &rect, 
                           const SparsePrizeInfo &prizeInfo) const;

    SparseTableData *m_sparseData = nullptr;
    
    // m_blockBoundaryFlags[col] == true 表示该逻辑列右侧需要画红色竖线
    QVector<bool> m_blockBoundaryFlags;
};

#endif // SPARSEDATADELEGATE_H
