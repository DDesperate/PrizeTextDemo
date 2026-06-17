#ifndef MULTILISTWGT_H
#define MULTILISTWGT_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include "genericfunc.h"
#include "tableWithCopy.h"

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include "genericfunc.h"
#include "tableWithCopy.h"

class MultiListWidget : public QWidget
{
    Q_OBJECT

public:
    //explicit MultiListWidget(QWidget *parent = nullptr,int list_count = 0,const QVector<QList<quint8>> &selectedCol = QVector<QList<quint8>>(),TableWithCopy *originTable = nullptr);
    explicit MultiListWidget(QWidget *parent = nullptr);
    void setUi_multiListWgt(QWidget* widget);
    void getPointer_OriginTable(TableWithCopy* p_table){p_originTable = p_table;}
    ~MultiListWidget();

private:
    QVBoxLayout *layV_multiListWgt;
    TableWithCopy* p_originTable;
    QVector<TableWithCopy*> tableWidgets;
    QPushButton *btn_getData;

};

#endif // MULTILISTWGT_H
