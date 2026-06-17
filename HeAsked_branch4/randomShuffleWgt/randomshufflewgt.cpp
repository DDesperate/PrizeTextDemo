#include "randomshufflewgt.h"


RandomShuffleWgt::RandomShuffleWgt(QWidget *parent) :
    QWidget(parent)
{
    setUi_randomShuffleWgt(this);
    setWindowFlags(Qt::Window);

    //把左表dataTable中的数据前n行放到dataTable_randomshuffling当中
    connect(getInfo_randomshuffling,&QPushButton::clicked,[=]{
        clearData(dataTable_randomshuffling);

        //检验表中是否有数据
        if (p_parentDataTable->rowCount() == 0 || p_parentDataTable->columnCount() == 0) {
            QMessageBox::warning(nullptr, tr("警告"), tr("表中无数据"));
        }
        int n = qMin(spinbox_randomshuffling->value(),p_parentDataTable->rowCount());

        // 遍历dataTable的前n行
        for (int row = 0; row < n; ++row) {
            // 在dataTable_randomshuffling中创建新行
            int newRow = dataTable_randomshuffling->rowCount();
            dataTable_randomshuffling->insertRow(newRow);

            // 遍历当前行的所有列
            for (int column = 0; column < p_parentDataTable->columnCount(); ++column) {
                // 复制每个单元格的数据到新表中
                QTableWidgetItem *item = p_parentDataTable->item(row, column);
                if (item) {
                    dataTable_randomshuffling->setItem(newRow, column, new QTableWidgetItem(item->text()));
                }
            }
        }

        initBackGround(dataTable_randomshuffling);

    });

    connect(shufflingitem_randomshuffling,&QPushButton::clicked,[=]{
        QList<quint8> fixedNum = inputEdt_randomshuffling->strToList();
        QVector<QString> dateList;
        QVector<QVector<quint8>> prize2DArray;
        //
        shuffleByCol(dataTable_randomshuffling->rowCount(),fixedNum,dateList,prize2DArray);

        //        QVector<QString> issue_num;
        //        QVector<QVector<quint8>> prize2DArray;
        //        QList<quint8> fixedNum = inputEdt_randomshuffling->strToList();
        //        shufflingByCol(spinbox_randomshuffling->value(),fixedNum,issue_num,prize2DArray);


        clearData(dataTable_randomshuffling);
        for (int row = 0; row < dateList.size(); ++row) {
            dataTable_randomshuffling->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(dateList[row]);
            dataTable_randomshuffling->setItem(row, 0, item); // 第一列填充期号

            for (int col = 0; col < prize2DArray[row].size(); ++col) {
                quint8 prize = prize2DArray[row][col];
                QTableWidgetItem *prizeItem = new QTableWidgetItem(QString::number(prize).rightJustified(2,'0'));
                dataTable_randomshuffling->setItem(row, col + 1, prizeItem); // 从第二列开始填充奖项
            }
        }

        initBackGround(dataTable_randomshuffling);
        markFixedNum(dataTable_randomshuffling,fixedNum);


        //        //清除上一次得表中数据

    });

    connect(btn_columnsSwap,&QPushButton::clicked,[=]{
        QList<int> res = getSelectedIndices(dataTable_randomshuffling,true);
        shuffleSelectedColumns(dataTable_randomshuffling,res);
    });

    connect(btn_copyPrize_randomshuffling,&QPushButton::clicked,[=]{
        copyAllPrize();
    });

    connect(btn_copySelectedPrize_randomshuffling,&QPushButton::clicked,[=]{
        copySelectedCol();
    });

//    connect(repeatSearchBtn,&QPushButton::clicked,[=]{

//    });

//    connect(neighborSearchBtn,&QPushButton::clicked,[=]{

//    });

//    connect(mixSearchBtn,&QPushButton::clicked,[=]{

//    });
}


RandomShuffleWgt::~RandomShuffleWgt()
{
}
