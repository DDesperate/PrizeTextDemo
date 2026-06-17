#include "downTbv.h"

void DownTableView::printSelectMixDataVec(const QVector<slctTbRow>& vec) {
    for (const slctTbRow& row : vec) {
        qDebug() << "Selected: " << row.isSelected;
        qDebug() << "Date: " << row.date;

        qDebug() << "Prizes:";
        for (const slcInfo& info : row.prizes) {
            qDebug() << "Color: " << info.color;
            qDebug() << "Prize: " << info.prize;
            qDebug() << "Selected: " << info.isSelect;
            qDebug() << "Deleted: " << info.isDeleted;
        }
    }
}
