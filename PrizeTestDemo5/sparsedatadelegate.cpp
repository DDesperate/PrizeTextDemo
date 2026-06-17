#include "sparsedatadelegate.h"
#include <QPainter>
#include <QFont>

SparseDataDelegate::SparseDataDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
    m_blockBoundaryFlags.resize(81);
    m_blockBoundaryFlags.fill(false);
}

void SparseDataDelegate::setSparseData(SparseTableData *data)
{
    m_sparseData = data;
}

void SparseDataDelegate::setBlockBoundaries(const QVector<int> &columns)
{
    if (m_blockBoundaryFlags.size() != 81) {
        m_blockBoundaryFlags.resize(81);
    }
    m_blockBoundaryFlags.fill(false);
    
    for (int col : columns) {
        if (col >= 1 && col <= 80) {
            m_blockBoundaryFlags[col] = true;
        }
    }
}

void SparseDataDelegate::clearBlockBoundaries()
{
    if (m_blockBoundaryFlags.isEmpty()) {
        return;
    }
    m_blockBoundaryFlags.fill(false);
}

void SparseDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    // 基础检查
    if (!m_sparseData || m_sparseData->isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    int row = index.row();
    if (row < 0 || row >= m_sparseData->size()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    const SparseRow &rowData = (*m_sparseData)[row];
    QRect rect = option.rect;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    int col = index.column();
    
    if (col == 0) {
        // 日期列
        paintDateCell(painter, rect, rowData);
    } 
    else if (col >= 1 && col <= 80) {
        // 奖注列
        paintPrizeCell(painter, rect, rowData, col);
    }

    painter->restore();
}

void SparseDataDelegate::paintDateCell(QPainter *painter, const QRect &rect, 
                                       const SparseRow &rowData) const
{
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
}

void SparseDataDelegate::paintPrizeCell(QPainter *painter, const QRect &rect, 
                                        const SparseRow &rowData, int col) const
{
    // 绘制整行选中背景
    if (rowData.isSelected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(234, 177, 255));
        painter->drawRect(rect);
    }
    
    // 获取该列的奖注信息
    const SparsePrizeInfo &prizeInfo = rowData.getPrize(col);
    
    // 如果没有奖注，直接返回
    if (!prizeInfo.hasPrize()) {
        return;
    }

    // 根据状态分发绘制
    if (prizeInfo.isDeleted) {
        paintDeletedPrize(painter, rect, prizeInfo);
    } 
    else if (prizeInfo.isSelect) {
        paintSelectedPrize(painter, rect, prizeInfo);
    } 
    else {
        paintNormalPrize(painter, rect, prizeInfo);
    }
    
    // 绘制按频率分块的红色竖线（画在单元格右边界）
    if (!m_blockBoundaryFlags.isEmpty() &&
        col >= 1 && col < m_blockBoundaryFlags.size() &&
        m_blockBoundaryFlags[col]) {
        QPen pen(QColor(200, 0, 0));
        pen.setWidth(2);
        painter->setPen(pen);
        const int x = rect.right();
        painter->drawLine(QPoint(x, rect.top()), QPoint(x, rect.bottom()));
    }
}

void SparseDataDelegate::paintNormalPrize(QPainter *painter, const QRect &rect, 
                                          const SparsePrizeInfo &prizeInfo) const
{
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;
    int radius = qMin(rect.width(), rect.height()) * 0.4;

    // 彩底白字
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(prizeInfo.color);
    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    painter->setPen(Qt::white);
    QFont font("Arial", radius * 1.0);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, 
                      QString::number(prizeInfo.prize).rightJustified(2, '0'));
}

void SparseDataDelegate::paintSelectedPrize(QPainter *painter, const QRect &rect, 
                                            const SparsePrizeInfo &prizeInfo) const
{
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;
    int radius = qMin(rect.width(), rect.height()) * 0.4;

    // 绿底白字
    painter->setPen(QPen(QColor(0, 100, 0), 2));
    painter->setBrush(QColor(0, 200, 0));
    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    painter->setPen(Qt::white);
    QFont font("Arial", radius * 1.0);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, 
                      QString::number(prizeInfo.prize).rightJustified(2, '0'));
}

void SparseDataDelegate::paintDeletedPrize(QPainter *painter, const QRect &rect, 
                                           const SparsePrizeInfo &prizeInfo) const
{
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;
    int radius = qMin(rect.width(), rect.height()) * 0.4;

    // 白底/无底 + 红斜线
    painter->setPen(QPen(Qt::black, 2));
    painter->setBrush(Qt::transparent);
    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // 红色斜线
    painter->setPen(QPen(QColor(180, 0, 0), 2));
    painter->drawLine(QPoint(rect.left() + 2, rect.top() + 2),
                      QPoint(rect.right() - 2, rect.bottom() - 2));

    // 绘制灰色数字
    painter->setPen(QColor(100, 100, 100));
    QFont font("Arial", radius * 1.0);
    font.setBold(true);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, 
                      QString::number(prizeInfo.prize).rightJustified(2, '0'));
}