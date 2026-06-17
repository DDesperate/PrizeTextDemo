#ifndef CHECKOUTWGT_H
#define CHECKOUTWGT_H

#include <QWidget>
#include <QMap>
#include <QList>
#include <QPair>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include "numLineEdit/numLineEdit.h"
class CheckoutWgt : public QWidget
{
    Q_OBJECT
public:
    explicit CheckoutWgt(QWidget *parent = nullptr);
    ~CheckoutWgt();
    void setUi_checkoutWgt(QWidget* widget);
    void getDate(const QMap<QList<quint8>,QPair<int,QString>> &res){m_res = res;}
    void clearAll(){lineEdit->clear();resultTxt->clear();}

private:
    QVBoxLayout *layV_checkoutWgt;
    NumLineEdit *lineEdit;
    QPushButton *searchBtn;
    QTextEdit *resultTxt;
    QMap<QList<quint8>,QPair<int,QString>> m_res;

};

#endif // CHECKOUTWGT_H
