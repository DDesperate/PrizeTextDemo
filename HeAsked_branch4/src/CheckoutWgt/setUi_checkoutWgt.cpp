#include "checkoutWgt.h"
void CheckoutWgt::setUi_checkoutWgt(QWidget *widget)
{
    layV_checkoutWgt = new QVBoxLayout(widget);
    lineEdit = new NumLineEdit(widget);
    searchBtn = new QPushButton(widget);
    resultTxt = new QTextEdit(widget);
    layV_checkoutWgt->addWidget(lineEdit);
    layV_checkoutWgt->addWidget(searchBtn);
    layV_checkoutWgt->addWidget(resultTxt);
}
