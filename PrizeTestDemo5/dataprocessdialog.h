#ifndef DATAPROCESSDIALOG_H
#define DATAPROCESSDIALOG_H

#include <QDialog>
#include <QVector>
#include "prizetableview.h"
#include "sparsedatadelegate.h"
#include "sparsestruct.h"
#include "dataconverter.h"
#include "downstruct.h"

/**
 * @brief 子窗口数据处理对话框
 * 
 * 接收主窗口的原始数据，转换为稀疏数组格式后显示
 */
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
    // 功能1：按列数字出现频率分块，并用红色竖线标出块之间的边界
    void onAction1Clicked();

private:
    void setupUI();
    
    PrizeTableView *m_subTableView;
    SparseDataDelegate *m_sparseDelegate;
    
    SparseTableData m_sparseData;
};

#endif // DATAPROCESSDIALOG_H
