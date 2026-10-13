#include "widget.h"
#include <QDebug>
#include <QItemSelectionModel>

void Widget::copySelectedItem(QTableWidget *tbwgt)
{
    QItemSelectionModel *selection = tbwgt->selectionModel();
    if (!selection || !selection->hasSelection()) return;

    const QItemSelection &sel = selection->selection();
    if (sel.isEmpty()) return;

    QStringList rangeTexts;
    for (const QItemSelectionRange &range : sel) {
        QString rangeText;
        for (int row = range.top(); row <= range.bottom(); ++row) {
            QStringList rowData;
            for (int col = range.left(); col <= range.right(); ++col) {
                QTableWidgetItem *item = tbwgt->item(row, col);
                rowData << (item ? item->text() : "");
            }
            rangeText += rowData.join(" ") + "\n";
        }
        if (!rangeText.isEmpty())
            rangeTexts << rangeText;
    }

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(rangeTexts.join("\n"));
}
