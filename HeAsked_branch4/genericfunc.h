#ifndef GENERICFUNC_H
#define GENERICFUNC_H

#include <QSet>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QClipboard>
#include <QApplication>
quint8 QStringToQuint8(const QString& str);
//取交集
QList<quint8> getCommonItems(const QList<quint8>& list1, const QList<quint8>& list2);
//取并集
QList<quint8> getUnion(const QList<quint8>& list1, const QList<quint8>& list2);
//去重
QVector<QList<quint8>> removeDuplicates(const QVector<QList<quint8>>& input);
//数据结构转文本
QString prizeListToString(const QList<quint8> &list);
//数据结构转文本(矩阵)
QString formatQVectorQListToString(const QVector<QList<quint8>>& data);
//数据结构转文本(矩阵) 每一行后跟该行元素个数
QString formatQVectorQListToStringWithCounts(const QVector<QList<quint8>>& data);
//文本转数据结构(矩阵)
QVector<QList<quint8>> parseStringToQVectorQList(const QString& str);
//初始化表格
void initTableWidget(QTableWidget* tbwgt);
//插入空行
void insertEmptyRow(QTableWidget *tbwgt, int rowPosition = -1);
//获取表中被选中的行或列
QList<int> getSelectedIndices(QTableWidget *tbwgt, bool selectColumns);
// 自定义排序规则
bool customSort(const QList<quint8>& a, const QList<quint8>& b);
//用于tab:剔除
QVector<QList<quint8>> excludeElements(const QVector<QList<quint8>>& dataStruct_originNum,const QVector<QList<quint8>>& dataStruct_numToBeExcluded);
//仅复制数据(不复制第一行。后面每行，在mark之后的部分不复制)
void copy_onlyPrize(const QString &text,QString mark);
//获取被选取区域的信息
bool getSelectedRectInfo(QTableView* tableView, int& startRow, int& startCol, int& rowCount, int& colCount) ;



#endif // GENERICFUNC_H
