#include "colSortTbv.h"
#include "genericfunc.h"
#include <QMenu>

void ColSortTbv::showContextMenu_colSort(const QPoint &pos)
{
    // 创建上下文菜单
    QMenu contextMenu;

    // 复制选中区域
    // 创建按钮 "复制选中区域"
    QAction copySelectAction("复制选中区域", this);

    //点击"复制选中区域" 按钮
    connect(&copySelectAction, &QAction::triggered, this, [=]{
        //获取表格中被选中的部分
        //从第mainRow行，mainCol列开始，高rowSpan，宽colSpan的区域
        int mainRow, mainCol, rowSpan, colSpan;
        getSelectedRectInfo(this, mainRow, mainCol, rowSpan, colSpan);
        //if (getSelectedRectInfo(this, mainRow, mainCol, rowSpan, colSpan)) {
        //    QMessageBox::information(
        //        nullptr,  // 父窗口（nullptr 表示无父窗口）
        //        "Selected Rectangle Info",  // 弹窗标题
        //        QString("Selected Rect:\n"
        //                "Start Row = %1\n"
        //                "Start Col = %2\n"
        //                "Height = %3\n"
        //                "Width = %4")
        //            .arg(mainRow)
        //            .arg(mainCol)
        //            .arg(rowSpan)
        //            .arg(colSpan)
        //        );
        //} else {
        //    qDebug() << "No selection or invalid selection.";
        //}

        //假设从第三行，第四列开始，高4，宽7想要复制这样一个矩阵
        

        QVector<QVector<int>> markedPrize(rowSpan, QVector<int>(colSpan, 0));


        //mainRow = 3  ,row < 3 + 4 , 那么就是遍历 3 - 6
        for (int row = mainRow; row < mainRow + rowSpan; ++row) {

            //if (row < 0 || row >= dataVec.size()) {
            //    qDebug() << "Row out of range:" << row;
            //    continue; // 跳过无效行
            //}

            //mainCol = 4 ,col < 4 + 7 ,那么就是遍历 4 - 10

            for (int col = mainCol; col < mainCol + colSpan; ++col) {
                //    if (col < 0 || col >= dataVec[row].prizes.size()) {
                //        qDebug() << "Column out of range:" << col;
                //        continue; // 跳过无效列
                //    }

                int localRow = row - mainRow;       //localRow = 0,1,2,3
                int localCol = col - mainCol;       //localCol = 0,1,2,3,4,5,6
                //int prize = dataVec[row-1].prizes[col-1];

                if (localRow >= 0 && localRow < rowSpan && localCol >= 0 && localCol < colSpan) {
                    // 注意 row ,col是符合人类思维的行数 ，但 dataVec和 prizes 的索引是从 0 开始。
                    // if (dataVec.at(row-1).prizes.contains(static_cast<quint8>(prize))) {
                    //     markedPrize[localRow][localCol] = prize;
                    // } else {
                    //     markedPrize[localRow][localCol] = 0;
                    // }
                    markedPrize[localRow][localCol] = dataVec[row-1].prizes[col-1];
                    qDebug() << "Index out of range: row=" << row << ", col=" << col;
                }

            }

        }
        QString clipboardText;

        // 遍历 markedPrize 生成字符串
        for (const auto& row : markedPrize) {
            for (const auto& value : row) {
                if(value != 0 && (!colSortDataTableD.markCol_Strike.contains(value)) ){
                    clipboardText += QString("%1 ").arg(value, 2, 10, QChar('0')); // 补0的格式
                }
            }
            clipboardText += "\n"; // 每行结束换行
        }

        // 将结果复制到剪切板
        QClipboard* clipboard = QApplication::clipboard();
        clipboard->setText(clipboardText);


    });

    contextMenu.addAction(&copySelectAction);

    // 删除本表格按钮
    QAction deleteAction("删除本表格", this);
    connect(&deleteAction, &QAction::triggered, this, [=]{
        // 发出删除表格的信号
        emit deleteRequested(this);
    });
    contextMenu.addAction(&deleteAction);

    // 显示菜单
    contextMenu.exec(mapToGlobal(pos));
}
