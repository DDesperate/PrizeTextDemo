#ifndef DATATABLEDELEGATE_H
#define DATATABLEDELEGATE_H


#include <QStyledItemDelegate>
#include <QPainter>
#include <QMessageBox>
#include <QDebug>
#include <iostream>
#include "UpStruct.h"


class DataTableDelegate : public QStyledItemDelegate
{
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
public:
    QMap<QString,tbRow> *delegateDataMap;
    QList<coo> *delegateCountCoos;
    int maxCount;
};
#endif // DATATABLEDELEGATE_H
