#include "prizetableview.h"
#include <QHeaderView>
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>

PrizeTableView::PrizeTableView(QWidget *parent)
    : QTableView(parent)
{
    setupStyle();
}

PrizeTableView::~PrizeTableView()
{
}

void PrizeTableView::setupStyle()
{
    przModel.setColumnCount(columnCount);
    updateColumnHeaders();

    this->setModel(&przModel);

    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    this->setEditTriggers(QAbstractItemView::NoEditTriggers);

    this->setSelectionBehavior(QAbstractItemView::SelectItems);
    this->setSelectionMode(QAbstractItemView::SingleSelection);

    this->horizontalHeader()->setMinimumSectionSize(1);
    this->verticalHeader()->setMinimumSectionSize(1);

    this->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    this->setColumnWidth(0, 60);

    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    this->horizontalHeader()->setStyleSheet(
        "QHeaderView::section{"
        "background:skyblue;"
        "color: black;"
        "font-weight: bold;"
        "border: 1px solid #aaa;"
        "padding: 2px;"
        "}"
        );

    this->verticalHeader()->setVisible(false);

    connect(this, &QTableView::clicked, this, &PrizeTableView::onClicked);
}

void PrizeTableView::setPrizeData(QVector<slctTbRow> *data)
{
    prizeDataVec = data;
    sparseDataVec = nullptr;
    useSparseData = false;
    refreshModel();
}

void PrizeTableView::setSparseData(QVector<SparseRow> *data)
{
    sparseDataVec = data;
    prizeDataVec = nullptr;
    useSparseData = true;
    refreshModel();
}

void PrizeTableView::setColumnCount(int count)
{
    columnCount = count;
    przModel.setColumnCount(columnCount);
    updateColumnHeaders();
    updateColumnWidths();
}

void PrizeTableView::setColumnMapping(const QVector<int> &mapping)
{
    m_columnMapping = mapping;
    updateColumnHeaders();
}

// ========== 新增：设置红竖线分隔列 ==========
void PrizeTableView::setBlockColumnDividers(const QVector<QVector<int>> &blockDividers)
{
    m_blockDividers = blockDividers;
    viewport()->update();
}

void PrizeTableView::updateColumnHeaders()
{
    przModel.setHeaderData(0, Qt::Horizontal, QStringLiteral("期数"));
    for (int i = 1; i < columnCount; i++) {
        if (m_columnMapping.size() >= 80 && i - 1 < m_columnMapping.size()) {
            przModel.setHeaderData(i, Qt::Horizontal, QString::number(m_columnMapping[i - 1]));
        } else {
            przModel.setHeaderData(i, Qt::Horizontal, QString::number(i));
        }
    }
}

void PrizeTableView::refreshModel()
{
    if (useSparseData) {
        refreshModelFromSparse();
    } else {
        refreshModelFromOriginal();
    }

    this->viewport()->update();
}

void PrizeTableView::refreshModelFromOriginal()
{
    if (!prizeDataVec)
        return;

    przModel.setRowCount(prizeDataVec->size());

    for (int row = 0; row < prizeDataVec->size(); ++row) {
        przModel.setItem(row, 0, new QStandardItem((*prizeDataVec)[row].date));

        for (int col = 1; col < columnCount; ++col) {
            przModel.setItem(row, col, new QStandardItem(""));
        }
    }
}

void PrizeTableView::refreshModelFromSparse()
{
    if (!sparseDataVec)
        return;

    przModel.setRowCount(sparseDataVec->size());

    for (int row = 0; row < sparseDataVec->size(); ++row) {
        const SparseRow &sr = (*sparseDataVec)[row];
        przModel.setItem(row, 0, new QStandardItem(sr.isSeparator ? "" : sr.date));

        for (int col = 1; col < columnCount; ++col) {
            przModel.setItem(row, col, new QStandardItem(""));
        }

        if (sr.isSeparator) {
            this->setRowHeight(row, 4);
        }
    }
}

void PrizeTableView::resizeEvent(QResizeEvent *event)
{
    QTableView::resizeEvent(event);
    updateColumnWidths();
}

void PrizeTableView::updateColumnWidths()
{
    int totalWidth = this->viewport()->width();

    int firstColWidth = 60;
    this->setColumnWidth(0, firstColWidth);

    int remainingWidth = totalWidth - firstColWidth;
    int otherColumnCount = columnCount - 1;

    if (otherColumnCount <= 0) return;

    int baseWidth = remainingWidth / otherColumnCount;
    int extraPixels = remainingWidth % otherColumnCount;

    for (int i = 1; i < columnCount; i++) {
        int width = baseWidth;
        if (extraPixels > 0) {
            width++;
            extraPixels--;
        }
        this->setColumnWidth(i, qMax(1, width));
    }

    this->verticalHeader()->setDefaultSectionSize(baseWidth > 0 ? baseWidth : 20);
}

void PrizeTableView::onClicked(const QModelIndex &index)
{
    currentRow = index.row();
    currentCol = index.column();
    emit cellClicked(currentRow, currentCol);
}

// ========== 新增：重写paintEvent ==========
void PrizeTableView::paintEvent(QPaintEvent *event)
{
    // 1. 先让父类绘制所有单元格内容
    QTableView::paintEvent(event);

    // 2. 在所有单元格之上绘制红竖线
    if (!useSparseData || m_blockDividers.isEmpty() || !sparseDataVec)
        return;

    QPainter painter(viewport());
    drawRedDividers(&painter);
}

// ========== 新增：绘制红竖线 ==========
void PrizeTableView::drawRedDividers(QPainter *painter)
{
    if (!sparseDataVec || m_blockDividers.isEmpty())
        return;

    painter->setPen(QPen(Qt::red, 4));  // 红色，线宽4

    int blockIndex = 0;
    int startRow = 0;

    for (int row = 0; row < sparseDataVec->size(); ++row) {
        const SparseRow &sr = (*sparseDataVec)[row];

        if (sr.isSeparator) {
            // 遇到分隔行，绘制上一个块的红竖线
            if (blockIndex < m_blockDividers.size()) {
                const QVector<int> &dividers = m_blockDividers[blockIndex];
                for (int col : dividers) {
                    if (col < 1 || col > 80) continue;

                    // 获取列的X坐标
                    int xPos = columnViewportPosition(col);

                    // 获取起始行和结束行的Y坐标
                    int yPosStart = rowViewportPosition(startRow);
                    int yPosEnd = rowViewportPosition(row - 1) + rowHeight(row - 1);

                    // 绘制红竖线
                    painter->drawLine(xPos, yPosStart, xPos, yPosEnd);
                }
            }
            blockIndex++;
            startRow = row + 1;
        }
    }

    // 绘制最后一个块的红竖线
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
