#pragma once

#include "przTbv/prizeTableView.h"
#include "colSortTbvDelegate.h"
#include "colSortTbvStruct.h"
#include "downTbv/downStruct.h"
class ColSortTbv: public PrizeTableView{
    Q_OBJECT
public:
    ColSortTbv(QWidget *parent = nullptr);
    ~ColSortTbv();

    //不实现任何功能
    void dbClkDate(QModelIndex const &Index);

    //根据传入的 "奖注数据" 计算出 "被标记的列" 及其 "被标记的类型" ( "绿色高亮" , "划掉" 等)
    //返回参数一是被标记的列
    //返回参数二是被划掉的列
    //用于被 “inputAndSortData” 调用
    QPair<QVector<int>, QVector<int>> calculateMarkedColumnTypes(const QVector<slctTbRow> &data);

    //根据传入的 "奖注数据" 排序后 得到新的数据结构 交给 "委托" 绘制表格
    //处理数据，交给委托，刷新并且显示图像
    void inputAndSortData(const QVector<slctTbRow> &data);

    //刷新表格
    void refreshTbv() {this->viewport()->update();}

    void markGreen(QVector<int> markGreenIndex){colSortDataTableD.markCol_Green = markGreenIndex;}

    void cancalMarkGreen() { colSortDataTableD.markCol_Green.clear(); this->refreshTbv(); }

    void showContextMenu_colSort(const QPoint &pos);

    void adjustHeightBasedOnRowCount_withoutHeader();

signals:
    void deleteRequested(ColSortTbv* table);  // 发出删除请求的信号
private:
    QVector<PrizeRowWithDate> dataVec;

    QVector<int> boundaries;    //用于存储分界线

    ColSortTbvDelegate colSortDataTableD;

    void printPrizeMatrixWithDate(const QVector<PrizeRowWithDate>& matrix);

    int countNonZero(const QVector<PrizeRowWithDate>& matrix, int colIndex);

    void sortByNonZeroCount(QVector<PrizeRowWithDate>& prizeMatrixWithDate, QVector<int>& boundaries);

    QVector<PrizeRowWithDate> convertToPrizeMatrix(const QVector<slctTbRow>& elements);
};
