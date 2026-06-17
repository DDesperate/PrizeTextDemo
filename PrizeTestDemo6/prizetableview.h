#ifndef PRIZETABLEVIEW_H
#define PRIZETABLEVIEW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QVector>
#include "downstruct.h"

class PrizeTableView : public QTableView
{
    Q_OBJECT

public:
    explicit PrizeTableView(QWidget *parent = nullptr);
    ~PrizeTableView();

    // 设置原始数据（主窗口使用）
    void setPrizeData(QVector<slctTbRow> *data);

    // 设置稀疏数组数据（子窗口使用）
    void setSparseData(QVector<SparseRow> *data);

    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }

    void refreshModel();
    void setColumnCount(int count);

    // 列映射：用于按频率分组，mapping[i]=第i+1列显示的数字
    void setColumnMapping(const QVector<int> &mapping);

    // 新增：设置按块的红竖线分隔列
    void setBlockColumnDividers(const QVector<QVector<int>> &blockDividers);

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;  // 新增

signals:
    void cellClicked(int row, int col);

private slots:
    void onClicked(const QModelIndex &index);

private:
    void setupStyle();
    void updateColumnWidths();
    void updateColumnHeaders();
    void refreshModelFromOriginal();
    void refreshModelFromSparse();
    void drawRedDividers(QPainter *painter);  // 新增：绘制红竖线

    QStandardItemModel przModel;
    QVector<slctTbRow> *prizeDataVec = nullptr;
    QVector<SparseRow> *sparseDataVec = nullptr;

    int totalWidth = 0;
    int currentRow = -1;
    int currentCol = -1;
    int columnCount = 81;
    QVector<int> m_columnMapping;
    QVector<QVector<int>> m_blockDividers;  // 新增：每块的红竖线列

    bool useSparseData = false;
};

#endif // PRIZETABLEVIEW_H
