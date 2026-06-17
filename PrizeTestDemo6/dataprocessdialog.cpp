#include "dataprocessdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QMap>
#include <algorithm>

DataProcessDialog::DataProcessDialog(QWidget *parent) : QDialog(parent)
{
    setupUI();
    setWindowTitle(QStringLiteral("数据处理窗口"));
    resize(1000, 600);
    setWindowFlags(Qt::Window | Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint);
}

void DataProcessDialog::setupUI()
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // 按钮区域
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnSync = new QPushButton(QStringLiteral("拉取主窗口数据"), this);
    QPushButton *btnClear = new QPushButton(QStringLiteral("清空子窗口的全部数据"), this);
    QPushButton *btnGroupByFreq = new QPushButton(QStringLiteral("按出现频率分组"), this);
    QPushButton *btnUngroupFreq = new QPushButton(QStringLiteral("取消按照频率分组"), this);
    QPushButton *btnMoveSelectedLeft = new QPushButton(QStringLiteral("📍 选中项靠边"), this);
    QPushButton *btnRestoreOrder = new QPushButton(QStringLiteral("↩️ 靠边项还原"), this);

    btnSync->setFixedHeight(40);
    btnClear->setFixedHeight(40);
    btnGroupByFreq->setFixedHeight(40);
    btnUngroupFreq->setFixedHeight(40);
    btnMoveSelectedLeft->setFixedHeight(40);
    btnRestoreOrder->setFixedHeight(40);

    connect(btnSync, &QPushButton::clicked, this, &DataProcessDialog::requestDataSync);
    connect(btnClear, &QPushButton::clicked, this, &DataProcessDialog::onClearAll);
    connect(btnGroupByFreq, &QPushButton::clicked, this, &DataProcessDialog::onGroupByFreq);
    connect(btnUngroupFreq, &QPushButton::clicked, this, &DataProcessDialog::onUngroupFreq);
    connect(btnMoveSelectedLeft, &QPushButton::clicked, this, &DataProcessDialog::onMoveSelectedToLeft);
    connect(btnRestoreOrder, &QPushButton::clicked, this, &DataProcessDialog::onRestoreSelectedOrder);

    btnLayout->addWidget(btnSync);
    btnLayout->addWidget(btnClear);
    btnLayout->addWidget(btnGroupByFreq);
    btnLayout->addWidget(btnUngroupFreq);
    btnLayout->addWidget(btnMoveSelectedLeft);
    btnLayout->addWidget(btnRestoreOrder);
    layout->addLayout(btnLayout);

    // 表格与代理配置
    m_subTableView = new PrizeTableView(this);
    m_delegate = new SelectDataDelegate(this);

    m_delegate->setSparseData(&m_sparseData);
    m_subTableView->setItemDelegate(m_delegate);
    m_subTableView->setSparseData(&m_sparseData);
    m_subTableView->setColumnCount(81);

    layout->addWidget(m_subTableView);
}

void DataProcessDialog::updateData(const QVector<slctTbRow> &sourceData)
{
    if (!m_sparseData.isEmpty()) {
        SparseRow sepRow;
        sepRow.isSeparator = true;
        m_sparseData.append(sepRow);
    }

    for (const slctTbRow &row : sourceData) {
        SparseRow sparseRow;
        sparseRow.isSelected = row.isSelected;
        sparseRow.date = row.date;
        for (const slcInfo &info : row.prizes) {
            int prizeNum = info.prize;
            if (prizeNum >= 1 && prizeNum <= 80) {
                sparseRow.prizes[prizeNum] = info;
            }
        }
        m_sparseData.append(sparseRow);
    }

    m_subTableView->refreshModel();
}

void DataProcessDialog::onClearAll()
{
    auto reply = QMessageBox::question(this, QStringLiteral("确认"),
                                       QStringLiteral("确定要清空子窗口全部数据吗？"),
                                       QMessageBox::Yes | QMessageBox::No,
                                       QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        m_sparseData.clear();
        m_delegate->setColumnMapping(QVector<int>());
        m_subTableView->setColumnMapping(QVector<int>());
        m_subTableView->setBlockColumnDividers(QVector<QVector<int>>());
        m_originalBlockMappings.clear();
        m_blockDividers.clear();
        m_isGroupedByFreq = false;
        m_subTableView->refreshModel();
    }
}

void DataProcessDialog::onGroupByFreq()
{
    if (m_sparseData.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("暂无数据，请先拉取主窗口数据"));
        return;
    }

    // 1. 按红色分隔行拆分为多个数据块
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

    // 保存原始映射
    m_originalBlockMappings = blockMappings;
    m_blockDividers = blockDividers;

    m_delegate->setBlockColumnMappings(blockMappings);
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_subTableView->setBlockColumnDividers(blockDividers);
    m_subTableView->setColumnMapping(QVector<int>());
    m_subTableView->refreshModel();

    m_isGroupedByFreq = true;
}

void DataProcessDialog::computeBlockMappingAndDividers(const QVector<const SparseRow *> &rows,
                                                       QVector<int> &mapping, QVector<int> &dividers)
{
    mapping.clear();
    dividers.clear();

    // 统计频率
    QVector<int> freq(81, 0);
    for (const SparseRow *sr : rows) {
        for (int col = 1; col <= 80; ++col) {
            if (sr->prizes[col].prize != 0)
                freq[col]++;
        }
    }

    // 按频率排序
    QVector<QPair<int, int>> colFreq;
    for (int col = 1; col <= 80; ++col) {
        colFreq.append(qMakePair(col, freq[col]));
    }
    std::stable_sort(colFreq.begin(), colFreq.end(),
                     [](const QPair<int, int> &a, const QPair<int, int> &b) {
                         return a.second < b.second;
                     });

    for (const auto &p : colFreq) {
        mapping.append(p.first);
    }

    // 频率变化处画红竖线
    for (int i = 1; i < 80; ++i) {
        if (colFreq[i].second != colFreq[i - 1].second) {
            dividers.append(i + 1);  // 1-based 列号
        }
    }
}

// ========== 获取某个数据块的选中数字 ==========
QSet<int> DataProcessDialog::getSelectedNumbersInBlock(const QVector<const SparseRow *> &rows)
{
    QSet<int> selected;
    for (const SparseRow *sr : rows) {
        for (int col = 1; col <= 80; ++col) {
            if (sr->prizes[col].prize != 0 && sr->prizes[col].isSelect) {
                selected.insert(col);
            }
        }
    }
    return selected;
}

// ========== 在细分数据块内重排 ==========
void DataProcessDialog::rearrangeSubBlock(QVector<int> &mapping, int start, int end,
                                          const QSet<int> &selectedNumbers)
{
    if (start > end || start < 0 || end >= mapping.size())
        return;

    QVector<int> selected;
    QVector<int> unselected;

    for (int i = start; i <= end; ++i) {
        int num = mapping[i];
        if (selectedNumbers.contains(num)) {
            selected.append(num);
        } else {
            unselected.append(num);
        }
    }

    // 重排：选中的在前，未选中的在后（保持原有相对顺序）
    int idx = start;
    for (int num : selected) {
        mapping[idx++] = num;
    }
    for (int num : unselected) {
        mapping[idx++] = num;
    }
}

// ========== 选中项靠边 ==========
void DataProcessDialog::onMoveSelectedToLeft()
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
        // 复制原始映射
        QVector<int> mapping = m_originalBlockMappings[blockIdx];
        const QVector<int> &dividers = m_blockDividers[blockIdx];
        const QSet<int> &selectedNumbers = allSelectedNumbers[blockIdx];

        // 根据红竖线位置，对每个细分数据块单独处理
        int start = 0;
        for (int divider : dividers) {
            // divider 是 1-based 列号，红竖线在第 divider 列左侧
            // mapping[0..divider-2] 是一个细分数据块（对应显示列 1 到 divider-1）
            int end = divider - 2;

            rearrangeSubBlock(mapping, start, end, selectedNumbers);
            start = divider - 1;
        }

        // 最后一个细分数据块
        if (mapping.size() == 80) {
            rearrangeSubBlock(mapping, start, 79, selectedNumbers);
        }

        newBlockMappings.append(mapping);
    }

    // 3. 应用新映射，红竖线位置不变
    m_delegate->setBlockColumnMappings(newBlockMappings);
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_subTableView->setBlockColumnDividers(m_blockDividers);
    m_subTableView->refreshModel();

    // 统计选中数量
    int totalSelected = 0;
    for (const auto &selSet : allSelectedNumbers) {
        totalSelected += selSet.size();
    }

    QMessageBox::information(this, QStringLiteral("完成"),
                             QStringLiteral("已将 %1 个选中数字靠边排列").arg(totalSelected));
}

// ========== 靠边项还原 ==========
void DataProcessDialog::onRestoreSelectedOrder()
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

    // 恢复原始映射
    m_delegate->setBlockColumnMappings(m_originalBlockMappings);
    m_delegate->setBlockColumnDividers(QVector<QVector<int>>());
    m_subTableView->setBlockColumnDividers(m_blockDividers);
    m_subTableView->refreshModel();

    QMessageBox::information(this, QStringLiteral("完成"),
                             QStringLiteral("已还原为原始排列"));
}

void DataProcessDialog::onUngroupFreq()
{
    m_delegate->setColumnMapping(QVector<int>());
    m_subTableView->setColumnMapping(QVector<int>());
    m_subTableView->setBlockColumnDividers(QVector<QVector<int>>());
    m_originalBlockMappings.clear();
    m_blockDividers.clear();
    m_isGroupedByFreq = false;
    m_subTableView->refreshModel();
}
