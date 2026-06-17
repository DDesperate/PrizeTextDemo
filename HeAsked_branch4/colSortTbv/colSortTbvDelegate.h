#ifndef COLSORTTBVDELEGATE_H
#define COLSORTTBVDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include "colSortTbvStruct.h"

class ColSortTbvDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
public:
    QVector<PrizeRowWithDate> *colSortData;

    QVector<int> *markCol; //用于存储被标记的列，列为分界点，列中非零元素从n到n+x的分界点

    QVector<int> markCol_Green; //用于存储被标记的列,整列涂成绿色

    QVector<int> markCol_Strike; //用于存储被标记的列,整列涂成绿色
private:
    //drawPrizeCircle要被paint函数调用，末尾必须用const修饰，称之为"常量成员函数"
    //因为paint也是"常量成员函数",常量成员函数不能调用非常量成员函数
    //void drawPrizeCircle(QPainter* painter, const QRect& rect, quint8 value,const QVector<int>& greenMarked) const ;

    void drawStrikePrize(QPainter* painter, const QRect& rect, quint8 value) const;

    void drawGreenCircle(QPainter* painter, const QRect& rect, quint8 value) const ;

    void drawBlueCircle(QPainter* painter, const QRect& rect, quint8 value) const ;
};


#endif // COLSORTTBVDELEGATE_H
