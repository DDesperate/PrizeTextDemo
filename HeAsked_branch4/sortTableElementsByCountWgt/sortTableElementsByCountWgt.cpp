#include "sortTableElementsByCountWgt.h"
#include <QVBoxLayout>
#include <QHeaderView>

void SortPrizeTableView::refreshModel()
{
    if (!selectDataVec)
        return;

    przModel.setRowCount(selectDataVec->size());

    for (int row = 0; row < selectDataVec->size(); ++row) {
        przModel.setItem(row, 0, new QStandardItem((*selectDataVec)[row].date));
        for (int col = 1; col < 81; ++col) {
            przModel.setItem(row, col, new QStandardItem(""));
        }
    }

    viewport()->update();
}

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

    m_tableView = new SortPrizeTableView(this);
    m_delegate = new SelectDataDelegate();

    m_tableView->setSelectData(&m_data);
    m_delegate->delegateSelectDataVec = &m_data;
    m_tableView->setItemDelegate(m_delegate);

    layout->addWidget(m_tableView);
}

void SortTableElementsByCountWgt::updateData(const QVector<slctTbRow>& data)
{
    m_data = data;
    m_tableView->refreshModel();
}

void SortTableElementsByCountWgt::refreshModel()
{
    m_tableView->refreshModel();
}
