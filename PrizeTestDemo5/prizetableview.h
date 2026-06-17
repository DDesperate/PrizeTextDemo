#ifndef PRIZETABLEVIEW_H
#define PRIZETABLEVIEW_H

#include <QTableView>
#include <QStandardItemModel>
#include <QVector>
#include "downstruct.h"
#include "sparsestruct.h"

/**
 * @brief 自定义表格视图
 * 
 * 支持两种数据源：
 * - 原始格式：主窗口使用
 * - 稀疏数组格式：子窗口使用
 */
class PrizeTableView : public QTableView
{
    Q_OBJECT

public:
    explicit PrizeTableView(QWidget *parent = nullptr);
    ~PrizeTableView();

    // 设置原始数据（主窗口使用）
    void setPrizeData(QVector<slctTbRow> *data);
    
    // 设置稀疏数组数据（子窗口使用）
    void setSparseData(SparseTableData *data);

    int getCurrentRow() const { return currentRow; }
    int getCurrentCol() const { return currentCol; }

    void refreshModel();
    void setColumnCount(int count);

protected:
    void resizeEvent(QResizeEvent *event) override;

signals:
    void cellClicked(int row, int col);

private slots:
    void onClicked(const QModelIndex &index);

private:
    void setupStyle();
    void updateColumnWidths();
    void refreshModelFromOriginal();
    void refreshModelFromSparse();

    QStandardItemModel przModel;
    QVector<slctTbRow> *prizeDataVec = nullptr;
    SparseTableData *sparseDataVec = nullptr;
    
    int totalWidth = 0;
    int currentRow = -1;
    int currentCol = -1;
    int columnCount = 81;
    
    bool useSparseData = false;
};

#endif // PRIZETABLEVIEW_H
