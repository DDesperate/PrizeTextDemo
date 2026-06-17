#include "dataprocessdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QHeaderView>
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

    // 同步按钮
    QPushButton *btnSync = new QPushButton(QStringLiteral("📥 点击同步主窗口数据"), this);
    btnSync->setFixedHeight(40);
    connect(btnSync, &QPushButton::clicked, this, &DataProcessDialog::requestDataSync);
    layout->addWidget(btnSync);

    // 功能按钮区域
    QHBoxLayout *btnLayout = new QHBoxLayout();

    QPushButton *btnAction1 = new QPushButton(QStringLiteral("功能一：按频率分块"), this);
    QPushButton *btnAction2 = new QPushButton(QStringLiteral("功能二（待实现）"), this);

    btnAction1->setFixedHeight(32);
    btnAction2->setFixedHeight(32);

    // 功能1：按列频率分块
    connect(btnAction1, &QPushButton::clicked, this, &DataProcessDialog::onAction1Clicked);

    btnLayout->addWidget(btnAction1);
    btnLayout->addWidget(btnAction2);
    btnLayout->addStretch();

    layout->addLayout(btnLayout);

    // 表格与代理配置
    m_subTableView = new PrizeTableView(this);
    m_sparseDelegate = new SparseDataDelegate(this);

    // 绑定稀疏数组数据源
    m_sparseDelegate->setSparseData(&m_sparseData);
    m_subTableView->setItemDelegate(m_sparseDelegate);
    m_subTableView->setSparseData(&m_sparseData);
    m_subTableView->setColumnCount(81);

    layout->addWidget(m_subTableView);
}

void DataProcessDialog::updateData(const QVector<slctTbRow> &sourceData)
{
    // 使用转换工具将原始数据转换为稀疏数组
    m_sparseData = DataConverter::toSparseData(sourceData);
    
    // 刷新显示
    m_subTableView->refreshModel();
}

void DataProcessDialog::onAction1Clicked()
{
    if (m_sparseData.isEmpty() || !m_subTableView || !m_sparseDelegate) {
        return;
    }

    // 1. 统计每一列（1-80）中数字出现的频率
    struct ColFreq {
        int col;
        int freq;
    };
    QVector<ColFreq> freqList;
    freqList.reserve(80);

    for (int c = 1; c <= 80; ++c) {
        int count = 0;
        for (const SparseRow &row : m_sparseData) {
            if (row.hasPrizeAt(c)) {
                ++count;
            }
        }
        freqList.append({c, count});
    }

    // 如果全部频率为0，则无需分块
    bool allZero = true;
    for (const ColFreq &cf : std::as_const(freqList)) {
        if (cf.freq != 0) {
            allZero = false;
            break;
        }
    }
    if (allZero) {
        m_sparseDelegate->clearBlockBoundaries();
        m_subTableView->horizontalHeader()->resetDefaultSectionSize();
        m_subTableView->horizontalHeader()->reset();
        m_subTableView->viewport()->update();
        return;
    }

    // 2. 按频率从低到高排序（频率相同按列号从小到大）
    std::sort(freqList.begin(), freqList.end(), [](const ColFreq &a, const ColFreq &b) {
        if (a.freq == b.freq) {
            return a.col < b.col;
        }
        return a.freq < b.freq;
    });

    // 3. 根据频率变化确定分块边界
    //    思路：同一频率的一组列视为一个块，
    //    当频率发生变化时，在前一个块的最后一列右侧画竖线。
    QVector<int> boundaryColumns;  // 边界“前一列”的逻辑列号
    if (!freqList.isEmpty()) {
        int currentFreq = freqList[0].freq;
        for (int i = 1; i < freqList.size(); ++i) {
            if (freqList[i].freq != currentFreq) {
                // 上一个元素所在的列为一个块的结束列
                boundaryColumns.append(freqList[i - 1].col);
                currentFreq = freqList[i].freq;
            }
        }
    }

    // 将边界信息告知代理，用于绘制红色竖线
    m_sparseDelegate->setBlockBoundaries(boundaryColumns);

    // 4. 按频率从低到高重排列（0列为期数列，保持在最左）
    QHeaderView *header = m_subTableView->horizontalHeader();
    if (!header) {
        m_subTableView->viewport()->update();
        return;
    }

    // 逐个把逻辑列移动到目标可视位置（从1开始）
    // freqList[i] 表示第 i+1 个位置应该显示的逻辑列号
    for (int visualPos = 1; visualPos <= freqList.size(); ++visualPos) {
        int logicalCol = freqList[visualPos - 1].col;
        int fromVisual = header->visualIndex(logicalCol);
        if (fromVisual != visualPos) {
            header->moveSection(fromVisual, visualPos);
        }
    }

    m_subTableView->viewport()->update();
}
