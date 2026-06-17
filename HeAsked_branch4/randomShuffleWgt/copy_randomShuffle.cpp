#include "randomshufflewgt.h"
#include <QApplication>
#include <QClipboard>
#include <QMessageBox>

void RandomShuffleWgt::copyAllPrize()
{
    QString res;
    for(int row = 0;row < dataTable_randomshuffling->rowCount();row++){
        for(int col = 1;col <= 20;col++){
            if(col != 20){
                res += dataTable_randomshuffling->item(row,col)->text() + " ";
            }
            else{
                res += dataTable_randomshuffling->item(row,col)->text();
            }
        }
        res += "\n";
    }
    QApplication::clipboard()->setText(res);
}

void RandomShuffleWgt::copySelectedCol()
{
    QString res;
    QList<int> colList = getSelectedIndices(dataTable_randomshuffling,true);
    for(int row = 0;row < dataTable_randomshuffling->rowCount();row++){
        QList<int>::const_iterator it = colList.constBegin();
        for (; it != colList.constEnd(); ++it) {
            if (it + 1 != colList.constEnd()) {
                res += dataTable_randomshuffling->item(row,*it)->text() + " ";
            } else {
                res += dataTable_randomshuffling->item(row,*it)->text();
            }
        }
        res += "\n";
    }
    QApplication::clipboard()->setText(res);
}
