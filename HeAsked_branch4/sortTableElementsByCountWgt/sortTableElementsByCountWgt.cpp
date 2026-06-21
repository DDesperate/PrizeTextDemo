#include "sortTableElementsByCountWgt.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QSet>
#include <algorithm>

// ========== SortPrizeTableView ==========

void SortPrizeTableView::setSelectData(QVector<slctTbRow> *data)
{
    prizeDataVec = data;
    sparseDataVec = nullptr;
    useSparseData = false;
}

void SortPrizeTableView::setSparseData(QVector<SparseRow> *data)
{
    sparseDataVec = data;
    prizeDataVec = nullptr;
    useSparseData = true;
}

void SortPrizeTableView::setBlockColumnDividers(const QVector<QVector<int>> &blockDividers)
{
    m_blockDividers = blockDividers;
    viewport()->update();
}

void SortPrizeTableView::refreshModel()
{
    if (useSparseData)
        refreshModelFromSparse();
    else
        refreshModelFromOriginal();
    viewport()->update();
}

void SortPrizeTableView::refreshModelFromOriginal()
{
    if (!prizeDataVec)
        return;

    przModel.setRowCount(prizeDataVec->size());
    for (int row = 0; row < prizeDataVec->size(); ++row) {
        przModel.setItem(row, 0, new QStandardItem((*prizeDataVec)[row].date));
        for (int col = 1; col < 81; ++col)
            przModel.setItem(row, col, new QStandardItem(""));
    }
}

void SortPrizeTableView::refreshModelFromSparse()
{
    if (!sparseDataVec)
        return;

    przModel.setRowCount(sparseDataVec->size());
    for (int row = 0; row < sparseDataVec->size(); ++row) {
        const SparseRow &sr = (*sparseDataVec)[row];
        przModel.setItem(row, 0, new QStandardItem(sr.isSeparator ? "" : sr.date));
        for (int col = 1; col < 81; ++col)
            przModel.setItem(row, col, new QStandardItem(""));
        if (sr.isSeparator)
            setRowHeight(row, 4);
    }
}

void SortPrizeTableView::paintEvent(QPaintEvent *event)
{
    QTableView::paintEvent(event);

    if (!useSparseData || m_blockDividers.isEmpty() || !sparseDataVec)
        return;

    QPainter painter(viewport());
    drawRedDividers(&painter);
}

void SortPrizeTableView::drawRedDividers(QPainter *painter)
{
    if (!sparseDataVec || m_blockDividers.isEmpty())
        return;

    painter->setPen(QPen(Qt::red, 4));

    int blockIndex = 0;
    int startRow = 0;

    for (int row = 0; row < sparseDataVec->size(); ++row) {
        const SparseRow &sr = (*sparseDataVec)[row];
        if (!sr.isSeparator)
            continue;

        if (blockIndex < m_blockDividers.size() && row > startRow) {
            const QVector<int> &dividers = m_blockDividers[blockIndex];
            for (int col : dividers) {
                if (col < 1 || col > 80) continue;
                int xPos = columnViewportPosition(col);
                int yPosStart = rowViewportPosition(startRow);
                int yPosEnd = rowViewportPosition(row - 1) + rowHeight(row - 1);
                painter->drawLine(xPos, yPosStart, xPos, yPosEnd);
            }
        }
        blockIndex++;
        startRow = row + 1;
    }

    if (blockIndex < m_blockDividers.size() && startRow < sparseDataVec->size()) {
        const QVector<int> &dividers = m_blockDividers[blockIndex];
        for (int col : dividers) {
            if (col < 1 || col > 80) continue;
            int xPos = columnViewportPosition(col);
            int yPosStart = rowViewportPosition(startRow);
            int yPosEnd = rowViewportPosition(sparseDataVec->size() - 1) + rowHeight(sparseDataVec->size() - 1);
            painter->drawLine(xPos, yPosStart, xPos, yPosEnd);
        }
    }
}

// ========== SortDataDelegate ==========

SortDataDelegate::SortDataDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

void SortDataDelegate::setSelectData(QVector<slctTbRow> *data)
{
    delegateSelectDataVec = data;
    useSparseData = false;
}

void SortDataDelegate::setSparseData(QVector<SparseRow> *data)
{
    delegateSparseDataVec = data;
    useSparseData = true;
}

void SortDataDelegate::setColumnMapping(const QVector<int> &mapping)
{
    m_displayColToNumber = mapping;
    m_blockMappings.clear();
    m_blockDividers.clear();
}

void SortDataDelegate::setBlockColumnMappings(const QVector<QVector<int>> &blockMappings)
{
    m_blockMappings = blockMappings;
    m_displayColToNumber.clear();
}

void SortDataDelegate::setBlockColumnDividers(const QVector<QVector<int>> &blockDividers)
{
    m_blockDividers = blockDividers;
}

void SortDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const
{
    if (useSparseData)
        paintSparse(painter, option, index);
    else
        paintOriginal(painter, option, index);
}

void SortDataDelegate::paintSparse(QPainter *painter, const QStyleOptionViewItem &option,
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

    if (rowData.isSeparator) {
        painter->setPen(QPen(Qt::red, 2));
        painter->drawLine(rect.left(), rect.center().y(), rect.right(), rect.center().y());
        painter->restore();
        return;
    }

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

    if (rowData.isSelected) {
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(234, 177, 255));
        painter->drawRect(rect);
    }

    if (!m_blockDividers.isEmpty()) {
        int blockIndex = 0;
        for (int i = 0; i < row; ++i) {
            if ((*delegateSparseDataVec)[i].isSeparator) blockIndex++;
        }
        if (blockIndex < m_blockDividers.size() && m_blockDividers[blockIndex].contains(displayCol)) {
            painter->setPen(QPen(Qt::red, 4));
            painter->drawLine(rect.left(), rect.top(), rect.left(), rect.bottom());
        }
    }

    const slcInfo &prizeInfo = rowData.prizes[numberToShow];

    if (prizeInfo.prize != 0) {
        int centerX = rect.x() + rect.width() / 2;
        int centerY = rect.y() + rect.height() / 2;
        int radius = qMin(rect.width(), rect.height()) * 0.4;
        int value = prizeInfo.prize;

        if (prizeInfo.isDeleted) {
            painter->setPen(QPen(Qt::black, 2));
            painter->setBrush(Qt::transparent);
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(QPen(QColor(180, 0, 0), 2));
            painter->drawLine(QPoint(rect.left() + 2, rect.top() + 2),
                              QPoint(rect.right() - 2, rect.bottom() - 2));
            painter->setPen(QColor(100, 100, 100));
        } else if (prizeInfo.isSelect) {
            painter->setPen(QPen(QColor(0, 100, 0), 2));
            painter->setBrush(QColor(0, 200, 0));
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(Qt::white);
        } else {
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

void SortDataDelegate::paintOriginal(QPainter *painter, const QStyleOptionViewItem &option,
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
        } else if (prizeInfo->isSelect) {
            painter->setPen(QPen(QColor(0, 100, 0), 2));
            painter->setBrush(QColor(0, 200, 0));
            painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);
            painter->setPen(Qt::white);
        } else {
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

// ========== SortTableElementsByCountWgt ==========

SortTableElementsByCountWgt::SortTableElementsByCountWgt(QWidget *parent, const QRect& rect) :
    QDialog(parent)
{
    setWindowFlags(Qt::Window | Qt::WindowCloseButtonHint | Qt::WindowMinMaxButtonsHint);
    setGeometry(rect);
    setWindowTitle(QStringLiteral("数据处理窗口"));
    setupUI();
}

SortTableElementsByCountWgt::~SortTableElementsByCountWgt()
{
}

void SortTableElementsByCountWgt::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QHBoxLayout *btnLayout = new QHBoxLayout();
    btnGroupByFreq = new QPushButton(QStringLiteral("按出现频率分组"), this);
    btnUngroupFreq = new QPushButton(QStringLiteral("取消按照频率分组"), this);
    btnModeRepeat = new QPushButton(QStringLiteral("重号模式"), this);
    btnModeNeighbor = new QPushButton(QStringLiteral("邻号模式"), this);
    btnModeMix = new QPushButton(QStringLiteral("混合模式"), this);
    btnMoveSelectedLeft = new QPushButton(QStringLiteral("选中项靠边"), this);
    btnRestoreOrder = new QPushButton(QStringLiteral("靠边项还原"), this);

    btnLayout->addWidget(btnGroupByFreq);
    btnLayout->addWidget(btnUngroupFreq);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(btnModeRepeat);
    btnLayout->addWidget(btnModeNeighbor);
    btnLayout->addWidget(btnModeMix);
    btnLayout->addSpacing(20);
    btnLayout->addWidget(btnMoveSelectedLeft);
    btnLayout->addWidget(btnRestoreOrder);
    btnLayout->addStretch();
    layout->addLayout(btnLayout);

    m_tableView = new SortPrizeTableView(this);
    m_delegate = new SortDataDelegate();

    m_delegate->setSparseData(&m_sparseData);
    m_tableView->setSparseData(&m_sparseData);
    m_tableView->setItemDelegate(m_delegate);

    layout->addWidget(m_tableView);

    connect(btnGroupByFreq, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onGroupByFreq);
    connect(btnUngroupFreq, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onUngroupFreq);
    connect(btnModeRepeat, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onModeRepeat);
    connect(btnModeNeighbor, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onModeNeighbor);
    connect(btnModeMix, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onModeMix);
    connect(btnMoveSelectedLeft, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onMoveSelectedToLeft);
    connect(btnRestoreOrder, &QPushButton::clicked, this, &SortTableElementsByCountWgt::onRestoreSelectedOrder);
}

void SortTableElementsByCountWgt::rebuildSparseData()
{
    m_sparseData.clear();

    for (int g = 0; g < m_groups.size(); ++g) {
        if (g > 0) {
            SparseRow sep;
            sep.isSeparator = true;
            m_sparseData.append(sep);
        }

        const QVector<slctTbRow> *src = nullptr;
        switch (m_currentMode) {
        case 0: src = &m_groups[g].repeatData; break;
        case 1: src = &m_groups[g].neighborData; break;
        case 2: src = &m_groups[g].mixData; break;
        }

        for (const slctTbRow &row : *src) {
            m_sparseData.append(row.toSparseRow());
        }
    }

    // 如果当前处于分组状态，重新应用分组映射
    if (m_isGroupedByFreq) {
        // 先刷新数据再重新分组
        m_tableView->refreshModel();
        onGroupByFreq();
        return;
    }

    m_delegate->setBlockColumnMappings(QVector<QVector<int>>());
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_tableView->setBlockColumnDividers(QVector<QVector<int>>());
    m_tableView->refreshModel();
}

void SortTableElementsByCountWgt::updateData(const QVector<slctTbRow>& repeatData,
                                              const QVector<slctTbRow>& neighborData,
                                              const QVector<slctTbRow>& mixData)
{
    // 收集已有数据的日期集合
    QSet<QString> existingDates;
    for (const SparseRow &sr : m_sparseData) {
        if (!sr.isSeparator && !sr.date.isEmpty())
            existingDates.insert(sr.date);
    }

    // 用当前模式的数据过滤重复行
    const QVector<slctTbRow> *currentSrc = nullptr;
    switch (m_currentMode) {
    case 0: currentSrc = &repeatData; break;
    case 1: currentSrc = &neighborData; break;
    case 2: currentSrc = &mixData; break;
    }

    QVector<slctTbRow> uniqueRepeat, uniqueNeighbor, uniqueMix;
    int dupCount = 0;

    for (int i = 0; i < repeatData.size(); ++i) {
        if (existingDates.contains(repeatData[i].date)) {
            dupCount++;
        } else {
            uniqueRepeat.append(repeatData[i]);
            uniqueNeighbor.append(neighborData[i]);
            uniqueMix.append(mixData[i]);
            existingDates.insert(repeatData[i].date);
        }
    }

    if (dupCount > 0) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("存在 %1 组重复数据，已跳过").arg(dupCount));
    }

    if (uniqueRepeat.isEmpty())
        return;

    // 存入新的一组数据
    GroupData grp;
    grp.repeatData = uniqueRepeat;
    grp.neighborData = uniqueNeighbor;
    grp.mixData = uniqueMix;
    m_groups.append(grp);

    // 重建显示数据
    rebuildSparseData();
}

void SortTableElementsByCountWgt::computeBlockMappingAndDividers(const QVector<const SparseRow *> &rows,
                                                                  QVector<int> &mapping, QVector<int> &dividers)
{
    mapping.clear();
    dividers.clear();

    QVector<int> freq(81, 0);
    for (const SparseRow *sr : rows) {
        for (int col = 1; col <= 80; ++col) {
            if (sr->prizes[col].prize != 0)
                freq[col]++;
        }
    }

    QVector<QPair<int, int>> colFreq;
    for (int col = 1; col <= 80; ++col)
        colFreq.append(qMakePair(col, freq[col]));

    std::stable_sort(colFreq.begin(), colFreq.end(),
                     [](const QPair<int, int> &a, const QPair<int, int> &b) {
                         return a.second < b.second;
                     });

    for (const auto &p : colFreq)
        mapping.append(p.first);

    for (int i = 1; i < 80; ++i) {
        if (colFreq[i].second != colFreq[i - 1].second)
            dividers.append(i + 1);
    }
}

void SortTableElementsByCountWgt::onGroupByFreq()
{
    if (m_sparseData.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("暂无数据，请先拉取数据"));
        return;
    }

    QVector<QVector<int>> blockMappings;
    QVector<QVector<int>> blockDividers;
    QVector<const SparseRow *> blockRows;

    for (int i = 0; i < m_sparseData.size(); ++i) {
        const SparseRow &sr = m_sparseData[i];
        if (sr.isSeparator) {
            if (!blockRows.isEmpty()) {
                QVector<int> mapping, dividers;
                computeBlockMappingAndDividers(blockRows, mapping, dividers);
                blockMappings.append(mapping);
                blockDividers.append(dividers);
                blockRows.clear();
            }
        } else {
            blockRows.append(&sr);
        }
    }
    if (!blockRows.isEmpty()) {
        QVector<int> mapping, dividers;
        computeBlockMappingAndDividers(blockRows, mapping, dividers);
        blockMappings.append(mapping);
        blockDividers.append(dividers);
    }

    m_originalBlockMappings = blockMappings;
    m_blockDividers = blockDividers;

    m_delegate->setBlockColumnMappings(blockMappings);
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_tableView->setBlockColumnDividers(blockDividers);
    m_tableView->refreshModel();

    m_isGroupedByFreq = true;
}

void SortTableElementsByCountWgt::onUngroupFreq()
{
    m_delegate->setColumnMapping(QVector<int>());
    m_tableView->setBlockColumnDividers(QVector<QVector<int>>());
    m_originalBlockMappings.clear();
    m_blockDividers.clear();
    m_isGroupedByFreq = false;
    m_tableView->refreshModel();
}

void SortTableElementsByCountWgt::onModeRepeat()
{
    m_currentMode = 0;
    rebuildSparseData();
}

void SortTableElementsByCountWgt::onModeNeighbor()
{
    m_currentMode = 1;
    rebuildSparseData();
}

void SortTableElementsByCountWgt::onModeMix()
{
    m_currentMode = 2;
    rebuildSparseData();
}

QSet<int> SortTableElementsByCountWgt::getSelectedNumbersInBlock(const QVector<const SparseRow *> &rows) const
{
    QSet<int> selected;
    for (const SparseRow *sr : rows) {
        for (int col = 1; col <= 80; ++col) {
            if (sr->prizes[col].prize != 0 && sr->prizes[col].isSelect)
                selected.insert(col);
        }
    }
    return selected;
}

void SortTableElementsByCountWgt::rearrangeSubBlock(QVector<int> &mapping, int start, int end,
                                                      const QSet<int> &selectedNumbers)
{
    if (start > end || start < 0 || end >= mapping.size())
        return;

    QVector<int> selected;
    QVector<int> unselected;

    for (int i = start; i <= end; ++i) {
        int num = mapping[i];
        if (selectedNumbers.contains(num))
            selected.append(num);
        else
            unselected.append(num);
    }

    int idx = start;
    for (int num : selected)
        mapping[idx++] = num;
    for (int num : unselected)
        mapping[idx++] = num;
}

void SortTableElementsByCountWgt::onMoveSelectedToLeft()
{
    if (!m_isGroupedByFreq) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("此功能只能在按出现频率分组状态下执行"));
        return;
    }

    if (m_sparseData.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("暂无数据"));
        return;
    }

    // 1. 重新分割数据块，获取每个块的行指针和选中数字
    QVector<QVector<const SparseRow *>> allBlockRows;
    QVector<QSet<int>> allSelectedNumbers;
    QVector<const SparseRow *> currentBlockRows;

    for (int i = 0; i < m_sparseData.size(); ++i) {
        const SparseRow &sr = m_sparseData[i];
        if (sr.isSeparator) {
            if (!currentBlockRows.isEmpty()) {
                allBlockRows.append(currentBlockRows);
                allSelectedNumbers.append(getSelectedNumbersInBlock(currentBlockRows));
                currentBlockRows.clear();
            }
        } else {
            currentBlockRows.append(&sr);
        }
    }
    if (!currentBlockRows.isEmpty()) {
        allBlockRows.append(currentBlockRows);
        allSelectedNumbers.append(getSelectedNumbersInBlock(currentBlockRows));
    }

    // 检查是否有选中项
    bool hasSelection = false;
    for (const auto &selSet : allSelectedNumbers) {
        if (!selSet.isEmpty()) {
            hasSelection = true;
            break;
        }
    }
    if (!hasSelection) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("没有选中任何奖注"));
        return;
    }

    // 2. 对每个数据块单独处理
    QVector<QVector<int>> newBlockMappings;

    for (int blockIdx = 0; blockIdx < m_originalBlockMappings.size(); ++blockIdx) {
        QVector<int> mapping = m_originalBlockMappings[blockIdx];
        const QVector<int> &dividers = m_blockDividers[blockIdx];
        const QSet<int> &selectedNumbers = allSelectedNumbers[blockIdx];

        int start = 0;
        for (int divider : dividers) {
            int end = divider - 2;
            rearrangeSubBlock(mapping, start, end, selectedNumbers);
            start = divider - 1;
        }

        if (mapping.size() == 80)
            rearrangeSubBlock(mapping, start, 79, selectedNumbers);

        newBlockMappings.append(mapping);
    }

    // 3. 应用新映射，红竖线位置不变
    m_delegate->setBlockColumnMappings(newBlockMappings);
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_tableView->setBlockColumnDividers(m_blockDividers);
    m_tableView->refreshModel();

    int totalSelected = 0;
    for (const auto &selSet : allSelectedNumbers)
        totalSelected += selSet.size();

    QMessageBox::information(this, QStringLiteral("完成"),
                             QStringLiteral("已将 %1 个选中数字靠边排列").arg(totalSelected));
}

void SortTableElementsByCountWgt::onRestoreSelectedOrder()
{
    if (!m_isGroupedByFreq) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("此功能只能在按出现频率分组状态下执行"));
        return;
    }

    if (m_originalBlockMappings.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("没有可还原的映射"));
        return;
    }

    m_delegate->setBlockColumnMappings(m_originalBlockMappings);
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_tableView->setBlockColumnDividers(m_blockDividers);
    m_tableView->refreshModel();

    QMessageBox::information(this, QStringLiteral("完成"),
                             QStringLiteral("已还原为原始排列"));
}
