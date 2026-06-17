#include "upTbv.h"

UpTableView::UpTableView(QWidget *parent):PrizeTableView(parent){
    dataTableD.delegateDataMap = &dataMap;
    setItemDelegate(&dataTableD);
}

UpTableView::~UpTableView(){

}
