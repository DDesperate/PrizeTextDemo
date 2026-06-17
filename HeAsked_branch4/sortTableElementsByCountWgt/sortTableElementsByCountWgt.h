#ifndef SORTTABLEELEMENTSBYCOUNTWGT_H
#define SORTTABLEELEMENTSBYCOUNTWGT_H

#include <QDialog>
#include <QTableView>
#include <QStandardItemModel>
#include <QVector>
#include "przTbv/prizeTableView.h"
#include "downTbv/selectDataDelegate.h"
#include "downTbv/downStruct.h"

class SortPrizeTableView : public PrizeTableView
{
    Q_OBJECT
public:
    explicit SortPrizeTableView(QWidget *parent = nullptr) : PrizeTableView(parent) {}

    void setSelectData(QVector<slctTbRow> *data)
    {
        selectDataVec = data;
    }

    QVector<slctTbRow> *getSelectData() { return selectDataVec; }

    void refreshModel();

protected:
    void dbClkDate(const QModelIndex &Index) override {}

private:
    QVector<slctTbRow> *selectDataVec = nullptr;
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

private:
    void setupUI();
    void refreshModel();

    SortPrizeTableView *m_tableView;
    SelectDataDelegate *m_delegate;
    QVector<slctTbRow> m_data;
};

#endif // SORTTABLEELEMENTSBYCOUNTWGT_H
