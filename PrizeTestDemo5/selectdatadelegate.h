#ifndef SELECTDATADELEGATE_H
#define SELECTDATADELEGATE_H

#include <QStyledItemDelegate>
#include <QVector>
#include "downstruct.h"

/**
 * @brief 主窗口代理类
 * 
 * 用于绘制原始格式的数据（slctTbRow）
 */
class SelectDataDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SelectDataDelegate(QObject *parent = nullptr);

    void setSelectData(QVector<slctTbRow> *data);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

private:
    QVector<slctTbRow> *delegateSelectDataVec = nullptr;
};

#endif // SELECTDATADELEGATE_H
