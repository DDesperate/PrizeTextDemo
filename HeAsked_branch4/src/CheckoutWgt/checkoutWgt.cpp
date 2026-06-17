#include "checkoutWgt.h"

CheckoutWgt::CheckoutWgt(QWidget *parent) :
    QWidget(parent)
{
    setUi_checkoutWgt(this);
    setWindowFlags(Qt::Window);


    connect(searchBtn,&QPushButton::clicked,[=]{
        //resultTxt->setText(lineEdit->text());
        //qDebug() << "测试";
        //ui->lineEdit->
        QList<quint8> list = lineEdit->strToList();
        if (m_res.contains(list)) {
            QPair<int, QString> pair = m_res.value(list);
            QString result = pair.second;
            resultTxt->setText(result);
            // 使用 result 做进一步的操作
        } else {
            // 处理 QMap 中不存在给定键的情况
        }
    });
}

CheckoutWgt::~CheckoutWgt()
{
}
