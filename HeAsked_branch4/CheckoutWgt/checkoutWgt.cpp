#include "checkoutWgt.h"
#include <QDebug>

CheckoutWgt::CheckoutWgt(QWidget *parent) :
    QWidget(parent)
{
    setUi_checkoutWgt(this);
    setWindowFlags(Qt::Window);
    if(m_res.isEmpty())
        qDebug() << "数据没有传过来";


    connect(searchBtn,&QPushButton::clicked,[=]{
        QList<quint8> list = lineEdit->strToList(); //获取输入奖注组
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
