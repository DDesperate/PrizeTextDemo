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
    useSparseData = false;
}

void SelectDataDelegate::setSparseData(QVector<SparseRow> *data)
{
    delegateSparseDataVec = data;
    useSparseData = true;
}

void SelectDataDelegate::setColumnMapping(const QVector<int> &mapping)
{
    m_displayColToNumber = mapping;
    m_blockMappings.clear();
    m_blockDividers.clear();
}

void SelectDataDelegate::setBlockColumnMappings(const QVector<QVector<int>> &blockMappings)
{
    m_blockMappings = blockMappings;
    m_displayColToNumber.clear();
}

void SelectDataDelegate::setBlockColumnDividers(const QVector<QVector<int>> &blockDividers)
{
    m_blockDividers = blockDividers;
}

void SelectDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    // 根据数据源类型选择不同的绘制逻辑
    if (useSparseData) {
        paintSparse(painter, option, index);
    } else {
        paintOriginal(painter, option, index);
    }
}

// ========== 稀疏数组绘制方法 ==========
void SelectDataDelegate::paintSparse(QPainter *painter, const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (!delegateSparseDataVec || delegateSparseDataVec->isEmpty()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    int row = index.row();
    if (row < 0 || row >= delegateSparseDataVec->size()) {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }

    const SparseRow &rowData = (*delegateSparseDataVec)[row];
    QRect rect = option.rect;

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing, true);

    // 分隔行：绘制红色横线
    if (rowData.isSeparator) {
        painter->setPen(QPen(Qt::red, 2));
        painter->drawLine(rect.left(), rect.center().y(), rect.right(), rect.center().y());
        painter->restore();
        return;
    }

    // 第一列：日期列绘制
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

    // 其他列：通过列映射查找显示的数字（支持按块独立映射）
    int displayCol = index.column();

    if (displayCol < 1 || displayCol > 80) {
        painter->restore();
        return;
    }

    int numberToShow = displayCol;
    if (!m_blockMappings.isEmpty()) {
        int blockIndex = 0;
        for (int i = 0; i < row; ++i) {
            if ((*delegateSparseDataVec)[i].isSeparator) blockIndex++;
        }
        if (blockIndex < m_blockMappings.size()) {
            const QVector<int> &mapping = m_blockMappings[blockIndex];
            if (mapping.size() >= 80 && displayCol >= 1 && displayCol <= 80)
                numberToShow = mapping[displayCol - 1];
        }
    } else if (m_displayColToNumber.size() >= 80 && displayCol >= 1 && displayCol <= 80) {
        numberToShow = m_displayColToNumber[displayCol - 1];
    }

    if (numberToShow < 1 || numberToShow > 80) {
        painter->restore();
        return;
    }

    // ========== 修改1：先绘制背景（如果整行选中）==========
    if (rowData.isSelected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(234, 177, 255));
        painter->drawRect(rect);
    }

    // ========== 修改2：再绘制红竖线，并增加线宽 ==========
    if (!m_blockDividers.isEmpty()) {
        int blockIndex = 0;
        for (int i = 0; i < row; ++i) {
            if ((*delegateSparseDataVec)[i].isSeparator) blockIndex++;
        }
        if (blockIndex < m_blockDividers.size() && m_blockDividers[blockIndex].contains(displayCol)) {
            painter->setPen(QPen(Qt::red, 4));  // 线宽从2改为4
            painter->drawLine(rect.left(), rect.top(), rect.left(), rect.bottom());
        }
    }

    // 按 numberToShow 访问稀疏数组
    const slcInfo &prizeInfo = rowData.prizes[numberToShow];

    // 如果有奖注（prize != 0），执行绘制
    if (prizeInfo.prize != 0) {
        int centerX = rect.x() + rect.width() / 2;
        int centerY = rect.y() + rect.height() / 2;
        int radius = qMin(rect.width(), rect.height()) * 0.4;
        int value = prizeInfo.prize;

        if (prizeInfo.isDeleted) {
            // 被划掉状态
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(Qt::transparent);
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(QPen(QColor(180, 0, 0), 2));
            painter->drawLine(QPoint(rect.left() + 2, rect.top() + 2),
                              QPoint(rect.right() - 2, rect.bottom() - 2));
            painter->setPen(QColor(100, 100, 100));
        }
        else if (prizeInfo.isSelect) {
            // 选中状态
            painter->setPen(QPen(QColor(0, 100, 0), 2));
            painter->setBrush(QColor(0, 200, 0));
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(Qt::white);
        }
        else {
            // 普通状态
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(prizeInfo.color);
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


// ========== 原始数据绘制方法 ==========
void SelectDataDelegate::paintOriginal(QPainter *painter, const QStyleOptionViewItem &option,
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

    // 第一列：日期列
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

    // 其他列：原有逻辑（循环查找）
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
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(Qt::transparent);
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(QPen(QColor(180, 0, 0), 2));
            painter->drawLine(QPoint(rect.left() + 2, rect.top() + 2),
                              QPoint(rect.right() - 2, rect.bottom() - 2));
            painter->setPen(QColor(100, 100, 100));
        }
        else if (prizeInfo->isSelect) {
            painter->setPen(QPen(QColor(0, 100, 0), 2));
            painter->setBrush(QColor(0, 200, 0));
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(Qt::white);
        }
        else {
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
