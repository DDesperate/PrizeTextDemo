#include "downTbv.h"
void DownTableView::deleteSelectedRow(){
    for(QString date:selectedSet){
        deleteOneRow_passive(date);
        emit deleteOneRow(date);
    }
    selectedSet.clear();
}
