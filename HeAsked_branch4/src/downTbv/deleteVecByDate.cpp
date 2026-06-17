#include"downTbv.h"

void DownTableView::deleteVecByDate(QVector<slctTbRow> &vec, QString date)
{
    for (int i = 0; i < vec.size(); i++) {
         if (vec[i].date == date) {
             vec.remove(i);
             i--;
         }
     }
}
