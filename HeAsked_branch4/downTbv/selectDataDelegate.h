#ifndef SELECTDATADELEGATE_H
#define SELECTDATADELEGATE_H


#include <QStyledItemDelegate>
#include <QPainter>
#include "downStruct.h"
#include <QMessageBox>
#include <QDebug>


class SelectDataDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
public:
    QVector<slctTbRow> *delegateSelectDataVec;
};

#endif // SELECTDATADELEGATE_H
