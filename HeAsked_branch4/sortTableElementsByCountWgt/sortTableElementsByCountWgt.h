#ifndef SORTTABLEELEMENTSBYCOUNTWGT_H
#define SORTTABLEELEMENTSBYCOUNTWGT_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QVector>
#include <QPainter>
#include <QPaintEvent>
#include <QStyledItemDelegate>
#include <QPushButton>
#include "przTbv/prizeTableView.h"
#include "downTbv/downStruct.h"

class SortPrizeTableView : public PrizeTableView
{
    Q_OBJECT
public:
    explicit SortPrizeTableView(QWidget *parent = nullptr) : PrizeTableView(parent) {}

    void setSelectData(QVector<slctTbRow> *data);
    void setSparseData(QVector<SparseRow> *data);
    void setBlockColumnDividers(const QVector<QVector<int>> &blockDividers);
    void refreshModel();

protected:
    void dbClkDate(const QModelIndex &Index) override {}
    void paintEvent(QPaintEvent *event) override;

private:
    void refreshModelFromOriginal();
    void refreshModelFromSparse();
    void drawRedDividers(QPainter *painter);

    QVector<slctTbRow> *prizeDataVec = nullptr;
    QVector<SparseRow> *sparseDataVec = nullptr;
    QVector<QVector<int>> m_blockDividers;
    bool useSparseData = false;
};

class SortDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SortDataDelegate(QObject *parent = nullptr);

    void setSelectData(QVector<slctTbRow> *data);
    void setSparseData(QVector<SparseRow> *data);
    void setColumnMapping(const QVector<int> &mapping);
    void setBlockColumnMappings(const QVector<QVector<int>> &blockMappings);
    void setBlockColumnDividers(const QVector<QVector<int>> &blockDividers);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    void paintSparse(QPainter *painter, const QStyleOptionViewItem &option,
                     const QModelIndex &index) const;
    void paintOriginal(QPainter *painter, const QStyleOptionViewItem &option,
                       const QModelIndex &index) const;

    QVector<slctTbRow> *delegateSelectDataVec = nullptr;
    QVector<SparseRow> *delegateSparseDataVec = nullptr;
    QVector<int> m_displayColToNumber;
    QVector<QVector<int>> m_blockMappings;
    QVector<QVector<int>> m_blockDividers;
    bool useSparseData = false;
};

class SortTableElementsByCountWgt : public QDialog
{
    Q_OBJECT

public:
    explicit SortTableElementsByCountWgt(QWidget *parent, const QRect& rect);
    ~SortTableElementsByCountWgt();

    void updateData(const QVector<slctTbRow>& data);

signals:
    void requestDataSync();

private slots:
    void onGroupByFreq();
    void onUngroupFreq();

private:
    void setupUI();
    void computeBlockMappingAndDividers(const QVector<const SparseRow *> &rows,
                                        QVector<int> &mapping, QVector<int> &dividers);

    SortPrizeTableView *m_tableView;
    SortDataDelegate *m_delegate;
    QPushButton *btnGroupByFreq;
    QPushButton *btnUngroupFreq;
    QVector<SparseRow> m_sparseData;
    bool m_isGroupedByFreq = false;
    QVector<QVector<int>> m_originalBlockMappings;
    QVector<QVector<int>> m_blockDividers;
};

#endif // SORTTABLEELEMENTSBYCOUNTWGT_H
