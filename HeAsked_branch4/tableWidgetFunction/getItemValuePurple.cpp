#include "widget.h"
void Widget::getItemValuePurple(QTableWidgetItem* tbwgtit)
{
    if(tbwgtit->column() != 0){
        tbwgtit->setBackground(QColor(170,0,255));
        inputEdt->addNum(tbwgtit->text().toInt());
    }
}
