#include "downTbv.h"
#include "genericfunc.h"
#include <QMenu>
#include <QMessageBox>

QVector<int> generateRowIndex(int begin, int span) {
    QVector<int> rowIndex;
    rowIndex.reserve(span - begin + 1);  // 预分配空间提升性能

    for(int i = begin; i <= span; ++i) {
        rowIndex.append(i);
    }
    return rowIndex;
}

void DownTableView::showContextMenu_down(const QPoint &pos)
{
    // 创建上下文菜单
    QMenu contextMenu;

    // 创建按钮
    QAction copySelectAction("复制选中区域", this);

    // 点击"复制选中区域" 按钮
    connect(&copySelectAction, &QAction::triggered, this, [=]{

        //获取表格中被选中的部分
        //从第mainRow行，mainCol列开始，高rowSpan，宽colSpan的区域
        int mainRow, mainCol, rowSpan, colSpan;
        getSelectedRectInfo(this, mainRow, mainCol, rowSpan, colSpan);
        if (getSelectedRectInfo(this, mainRow, mainCol, rowSpan, colSpan)) {
            // QMessageBox::information(
            //     nullptr,  // 父窗口（nullptr 表示无父窗口）
            //     "Selected Rectangle Info",  // 弹窗标题
            //     QString("Selected Rect:\n"
            //             "Start Row = %1\n"
            //             "Start Col = %2\n"
            //             "Height = %3\n"
            //             "Width = %4")
            //         .arg(mainRow)
            //         .arg(mainCol)
            //         .arg(rowSpan)
            //         .arg(colSpan)
            //     );
        } else {
            qDebug() << "No selection or invalid selection.";
        }

        QVector<int> rowIndex = generateRowIndex(mainRow,mainRow+rowSpan-1);
        QVector<int> colIndex = generateRowIndex(mainCol,mainCol+colSpan-1);


        QString clipboardText;
        if(mode == repeat){
            for(int row = 0; row < selectDataVec.size();row++ ){
                for(int col = 0; col<20; col++)
                {
                    slcInfo item = selectDataVec.at(row).prizes.at(col);
                    if(rowIndex.contains(row+1) && colIndex.contains(item.prize) && item.isDeleted == false){
                        clipboardText += QString("%1 ").arg(item.prize, 2, 10, QChar('0')); // 补0的格式
                    }
                }
                clipboardText += "\n"; // 每行结束换行
            }
        }else if(mode == neighbor){
            for(int row = 0; row < selectNeighborDataVec.size();row++ ){
                for (int col = 0; col < selectNeighborDataVec.at(row).prizesSize(); col++) //selectNeighborDataVec一行的元素超出20个了
                {
                    slcInfo item = selectNeighborDataVec.at(row).prizes.at(col);
                    if(rowIndex.contains(row+1) && colIndex.contains(item.prize) && item.isDeleted == false){
                        clipboardText += QString("%1 ").arg(item.prize, 2, 10, QChar('0')); // 补0的格式
                    }
                }
                clipboardText += "\n"; // 每行结束换行
            }
        }else if(mode ==mix){
            //printSelectMixDataVec(selectMixDataVec);
            for(int row = 0; row < selectMixDataVec.size();row++ ){
                for (int col = 0; col < selectMixDataVec.at(row).prizesSize(); col++)
                    //for(int col = 0; col<20; col++)  //selectMixDataVec一行的元素超出20个了
                {
                    slcInfo item = selectMixDataVec.at(row).prizes.at(col);
                    if(rowIndex.contains(row+1) && colIndex.contains(item.prize) && item.isDeleted == false){
                        clipboardText += QString("%1 ").arg(item.prize, 2, 10, QChar('0')); // 补0的格式
                    }
                }
                clipboardText += "\n"; // 每行结束换行
            }
        }

        QClipboard *clipboard = QApplication::clipboard();
        clipboard->setText(clipboardText);





        //     //初始化一个slcInfo类型的数据
        //     slcInfo initPrize;
        //     initPrize.prize = 0;
        //     initPrize.color = Qt::black;
        //     initPrize.isDeleted = false;
        //     initPrize.isSelect = false;

        //     //定义二维数组，用来取被选中的行
        //     QVector<QVector<slcInfo>> markedPrize(rowSpan, QVector<slcInfo>(colSpan, initPrize));

        //     for (int row = mainRow; row < mainRow + rowSpan; ++row) {
        //         //if (row < 0 || row >= selectDataVec.size()) {
        //         //    qDebug() << "Row out of range:" << row;
        //         //    continue; // 跳过无效行
        //         //}

        //         for (int col = mainCol; col < mainCol + colSpan; ++col) {
        //             //if (col < 0 || col >= selectDataVec[row].prizes.size()) {
        //             //    qDebug() << "Column out of range:" << col;
        //             //    continue; // 跳过无效列
        //             //}

        //             int localRow = row - mainRow;
        //             int localCol = col - mainCol;
        //             int prize = col;

        //             if (localRow >= 0 && localRow < rowSpan && localCol >= 0 && localCol < colSpan) {
        //                 // 注意 row 是符合人类思维的行数 ，但 selectDataVec 的索引是从 0 开始，所以 row - 1

        //                 if (mode == repeat && selectDataVec.at(row-1).myContains(static_cast<quint8>(prize))) {
        //                     //markedPrize[localRow][localCol] = prize;
        //                     markedPrize[localRow][localCol] = selectDataVec.at(row-1).prizes.at(col);
        //                 }
        //                 else if(mode == neighbor && selectNeighborDataVec.at(row-1).myContains(static_cast<quint8>(prize))){
        //                     //markedPrize[localRow][localCol] = prize;
        //                     markedPrize[localRow][localCol] = selectNeighborDataVec.at(row-1).prizes.at(col);
        //                 }
        //                 else if(mode == mix && selectMixDataVec.at(row-1).myContains(static_cast<quint8>(prize))){
        //                     //markedPrize[localRow][localCol] = prize;
        //                     markedPrize[localRow][localCol] = selectMixDataVec.at(row-1).prizes.at(col);
        //                 }
        //                 else {
        //                     markedPrize[localRow][localCol].prize = 0;
        //                 }
        //             } else {
        //                 qDebug() << "Index out of range: row=" << row << ", col=" << col;
        //             }
        //         }
        //     }

        //     QString clipboardText;

        //     // 遍历 markedPrize 生成字符串
        //     for (const QVector<slcInfo>& row : markedPrize) {
        //         for (const slcInfo& value : row) {
        //             if(value.prize != 0 && value.isDeleted == false) {
        //                 clipboardText += QString("%1 ").arg(value.prize, 2, 10, QChar('0')); // 补0的格式
        //             }
        //         }
        //         clipboardText += "\n"; // 每行结束换行
        //     }

        //     // 将结果复制到剪切板
        //     QClipboard *clipboard = QApplication::clipboard();
        //     clipboard->setText(clipboardText);

    });

    contextMenu.addAction(&copySelectAction);

    // 显示菜单
    contextMenu.exec(mapToGlobal(pos));
}
