#ifndef DATAPROCESSDIALOG_H
#define DATAPROCESSDIALOG_H

#include <QDialog>
#include <QVector>
#include "prizetableview.h"
#include "selectdatadelegate.h"
#include "downstruct.h"

class DataProcessDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DataProcessDialog(QWidget *parent = nullptr);

signals:
    void requestDataSync();

public slots:
    void updateData(const QVector<slctTbRow> &sourceData);

private slots:
    void onClearAll();
    void onGroupByFreq();
    void onUngroupFreq();
    void onMoveSelectedToLeft();      // 选中项靠边
    void onRestoreSelectedOrder();    // 靠边项还原

private:
    void setupUI();
    void computeBlockMappingAndDividers(const QVector<const SparseRow *> &rows,
                                        QVector<int> &mapping, QVector<int> &dividers);

    // 在细分数据块内重排选中的数字
    void rearrangeSubBlock(QVector<int> &mapping, int start, int end,
                           const QSet<int> &selectedNumbers);

    // 获取某个数据块的所有选中数字
    QSet<int> getSelectedNumbersInBlock(const QVector<const SparseRow *> &rows);

    PrizeTableView *m_subTableView;
    SelectDataDelegate *m_delegate;

    QVector<SparseRow> m_sparseData;      // 稀疏数组数据

    bool m_isGroupedByFreq = false;
    QVector<QVector<int>> m_originalBlockMappings;  // 保存原始映射（用于还原）
    QVector<QVector<int>> m_blockDividers;          // 红竖线位置
};
#endif // DATAPROCESSDIALOG_H
