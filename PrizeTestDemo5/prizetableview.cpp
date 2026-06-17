#include "prizetableview.h"
#include <QHeaderView>
#include <QResizeEvent>

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
    // 设置列数和表头
    przModel.setColumnCount(columnCount);
    przModel.setHeaderData(0, Qt::Horizontal, QStringLiteral("期数"));
    for (int i = 1; i < columnCount; i++) {
        przModel.setHeaderData(i, Qt::Horizontal, QString::number(i));
    }

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

void PrizeTableView::setSparseData(SparseTableData *data)
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
    przModel.setHeaderData(0, Qt::Horizontal, QStringLiteral("期数"));
    for (int i = 1; i < columnCount; i++) {
        przModel.setHeaderData(i, Qt::Horizontal, QString::number(i));
    }
    updateColumnWidths();
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
        przModel.setItem(row, 0, new QStandardItem((*sparseDataVec)[row].date));

        for (int col = 1; col < columnCount; ++col) {
            przModel.setItem(row, col, new QStandardItem(""));
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
