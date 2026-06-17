#include "upTbv.h"
#include "genericfunc.h"
#include <QMenu>
void UpTableView::showContextMenu_upTbv(const QPoint &pos)
{
    // 创建上下文菜单
    QMenu contextMenu;

    // 创建按钮
    QAction copySelectAction("复制选中区域", this);

    //点击"复制选中区域" 按钮
    connect(&copySelectAction, &QAction::triggered, this, [=]{

        //获取被选中的区域
        //从第mainRow行，mainCol列开始，高rowSpan，宽colSpan的区域
        int mainRow, mainCol, rowSpan, colSpan;
        getSelectedRectInfo(this, mainRow, mainCol, rowSpan, colSpan);

        //数据结构:被选中的数据
        QVector<QVector<int>> markedPrize(rowSpan, QVector<int>(colSpan, 0));

        for (int row = mainRow; row < mainRow + rowSpan; ++row) {

            for (int col = mainCol; col < mainCol + colSpan; ++col) {

                int localRow = row - mainRow;
                int localCol = col - mainCol;

                if (localRow >= 0 && localRow < rowSpan && localCol >= 0 && localCol < colSpan) {
                    auto it = dataMap.begin() + row - 1;
                    markedPrize[localRow][localCol] = (*it).prizes[col-1].num;
                }
            }
        }

        QString clipboardText;

        // 遍历 markedPrize 生成字符串
        for (const auto& row : markedPrize) {
            for (const auto& value : row) {
                if(value != 0){
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

    // 显示菜单
    contextMenu.exec(mapToGlobal(pos));
}
