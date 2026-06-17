#include "selectdatadelegate.h"
#include <QPainter>
#include <QFont>

SelectDataDelegate::SelectDataDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void SelectDataDelegate::setSelectData(QVector<slctTbRow> *data)
{
    delegateSelectDataVec = data;
}

void SelectDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    if (!delegateSelectDataVec || delegateSelectDataVec->isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    int row = index.row();
    if (row < 0 || row >= delegateSelectDataVec->size()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    const slctTbRow &rowData = (*delegateSelectDataVec)[row];
    QRect rect = option.rect;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    // ========== 第一列：日期列 ==========
    if (index.column() == 0) {
        QColor bgColor = rowData.isSelected ? QColor(234, 177, 255) : QColor(135, 206, 235);
        painter->setPen(Qt::NoPen);
        painter->setBrush(bgColor);
        painter->drawRect(rect);

        painter->setPen(QPen(Qt::black));
        int fontSize = qMin(rect.height(), rect.width()) * 0.4;
        QFont font("Arial", fontSize > 0 ? fontSize : 9);
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, rowData.date);

        painter->restore();
        return;
    }

    // ========== 其他列：奖注列 ==========
    if (rowData.isSelected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(234, 177, 255));
        painter->drawRect(rect);
    }

    int col = index.column();
    const slcInfo *prizeInfo = nullptr;
    for (const slcInfo &info : rowData.prizes) {
        if (info.prize == col) {
            prizeInfo = &info;
            break;
        }
    }

    if (prizeInfo) {
        int centerX = rect.x() + rect.width() / 2;
        int centerY = rect.y() + rect.height() / 2;
        int radius = qMin(rect.width(), rect.height()) * 0.4;
        int value = prizeInfo->prize;

        if (prizeInfo->isDeleted) {
            // 被划掉状态
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(Qt::transparent);
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(QPen(QColor(180, 0, 0), 2));
            painter->drawLine(QPoint(rect.left() + 2, rect.top() + 2),
                              QPoint(rect.right() - 2, rect.bottom() - 2));
            painter->setPen(QColor(100, 100, 100));
        }
        else if (prizeInfo->isSelect) {
            // 选中状态
            painter->setPen(QPen(QColor(0, 100, 0), 2));
            painter->setBrush(QColor(0, 200, 0));
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(Qt::white);
        }
        else {
            // 普通状态
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(prizeInfo->color);
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(Qt::white);
        }

        QFont font("Arial", radius * 1.0);
        font.setBold(true);
        painter->setFont(font);
        painter->drawText(rect, Qt::AlignCenter, QString::number(value).rightJustified(2, '0'));
    }

    painter->restore();
}