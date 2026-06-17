#ifndef RANDOMSHUFFLEWGT_H
#define RANDOMSHUFFLEWGT_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QTableWidget>
#include <QApplication>
#include <QDesktopWidget>
#include "numLineEdit/numLineEdit.h"
#include "genericfunc.h"
class RandomShuffleWgt : public QWidget
{
    Q_OBJECT

public:
    explicit RandomShuffleWgt(QWidget *parent = nullptr);
    ~RandomShuffleWgt();
    void setUi_randomShuffleWgt(QWidget* widget);
    void getTableWigetPointer(QTableWidget *dataTable) {p_parentDataTable = dataTable;}
    void shuffleByCol(int rowCount,const QList<quint8> fixedNum,QVector<QString> &issue_num,QVector<QVector<quint8>> &prize2DArray);
    void markFixedNum(QTableWidget* tbwgt,const QList<quint8> fixedNum);
    void shuffleSelectedColumns(QTableWidget *dataTable, const QList<int> &selectedColumns);
    void copyAllPrize();
    void copySelectedCol();

    QTableWidget *dataTable_randomshuffling;

private:
    QTableWidget *p_parentDataTable;

    QVBoxLayout *vlay_randomshuffling;
    QHBoxLayout *hlay_getInfo_randomshuffling;
    QSpinBox *spinbox_randomshuffling;
    QPushButton *getInfo_randomshuffling;
    QHBoxLayout *hlay_shufflingitem_randomshuffling;
    QPushButton *shufflingitem_randomshuffling;
    NumLineEdit *inputEdt_randomshuffling;
    QPushButton *btn_columnsSwap;

    QHBoxLayout *hlay_copybtn_randomshuffling;
    QPushButton *btn_copyPrize_randomshuffling;
    QPushButton *btn_copySelectedPrize_randomshuffling;

//    QHBoxLayout *hlay_searchBtn;
//    QPushButton *repeatSearchBtn;
//    QPushButton *neighborSearchBtn;
//    QPushButton *mixSearchBtn;
};

#endif // RANDOMSHUFFLEWGT_H
