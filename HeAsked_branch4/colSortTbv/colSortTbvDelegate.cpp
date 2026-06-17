#include"colSortTbvDelegate.h"
#include<QMessageBox>
extern QFont aliFont;

// //1.画笔 2.表格形状信息:位置，大小 3.奖注数字 4.被标记为绿色的列
// void ColSortTbvDelegate::drawPrizeCircle(QPainter* painter, const QRect& rect, quint8 prizeValue) const
// {
//     //根据网格的位置计算圆心位置和半径
//     int centerX = rect.x() + rect.width() / 2;
//     int centerY = rect.y() + rect.height() / 2;
//     int radius = qMin(rect.width() * 0.5, rect.height() * 0.5);

//     painter->setRenderHint(QPainter::Antialiasing, true);
//     painter->setPen(QColor(0, 0, 0));

//     // 设置填充颜色
//     if (greenMarked.contains(prizeValue)) {
//         painter->setBrush(QColor(0, 255, 0));
//     } else {
//         painter->setBrush(QColor(49, 102, 204));
//     }

//     painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

//     // 绘制文本
//     painter->setPen(QPen(QColor(255, 255, 255)));
//     QFont font("Arial", qMin(rect.height(), rect.width()) * 0.4);
//     painter->setFont(font);
//     painter->drawText(rect, Qt::AlignCenter, QString::number(prizeValue).rightJustified(2, '0'));
// }

void ColSortTbvDelegate::drawStrikePrize(QPainter *painter, const QRect& rect, quint8 value) const
{
    //根据网格的位置计算圆心位置和半径
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;
    int radius = qMin(rect.width() * 0.5, rect.height() * 0.5);

    //设置画笔,画刷颜色
    painter->setPen(QColor(0,0,0));
    painter->setBrush(QColor(255,255,255,0));

    //画圆
    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    //划线:划掉奖注效果
    painter->drawLine(QPoint(rect.x(),rect.y()),QPoint(rect.x()+rect.width(),rect.y()+rect.height()));

    //绘制文本
    painter->setPen(QPen(QColor(0,0,0)));

    //设置字体随单元格大小变化
    QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
    painter->setFont(font);

    painter->drawText(rect, Qt::AlignCenter, QString::number(value).rightJustified(2,'0'));

}

void ColSortTbvDelegate::drawGreenCircle(QPainter* painter, const QRect& rect, quint8 prizeValue) const
{
    //根据网格的位置计算圆心位置和半径
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;
    int radius = qMin(rect.width() * 0.5, rect.height() * 0.5);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QColor(0, 0, 0));

    // 设置填充颜色
    painter->setBrush(QColor(0, 255, 0));

    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // 绘制文本
    painter->setPen(QPen(QColor(255, 255, 255)));
    QFont font("Arial", qMin(rect.height(), rect.width()) * 0.4);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, QString::number(prizeValue).rightJustified(2, '0'));
}

void ColSortTbvDelegate::drawBlueCircle(QPainter* painter, const QRect& rect, quint8 prizeValue) const
{
    //根据网格的位置计算圆心位置和半径
    int centerX = rect.x() + rect.width() / 2;
    int centerY = rect.y() + rect.height() / 2;
    int radius = qMin(rect.width() * 0.5, rect.height() * 0.5);

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QColor(0, 0, 0));

    // 设置填充颜色
    painter->setBrush(QColor(49, 102, 204));

    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

    // 绘制文本
    painter->setPen(QPen(QColor(255, 255, 255)));
    QFont font("Arial", qMin(rect.height(), rect.width()) * 0.4);
    painter->setFont(font);
    painter->drawText(rect, Qt::AlignCenter, QString::number(prizeValue).rightJustified(2, '0'));
}


void ColSortTbvDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QStyledItemDelegate::paint(painter, option, index);

    //设置画笔颜色形状
    painter->setPen(QPen(QColor(0, 0, 0)));
    painter->setBrush(QColor(255, 255, 255, 0));
    painter->drawRect(option.rect);

    //markCol：用于存储被标记的列，列为分界点，列中非零元素从n个到n+x个的分界点
    //为被标记的列的右侧画红线标注
    if (markCol->contains(index.column()-1)) {
        QRect rect = option.rect;

        // 设置组合模式为 Source，覆盖底层内容
        painter->setCompositionMode(QPainter::CompositionMode_Source);

        // 绘制加粗红色右边框
        painter->setPen(QPen(QColor(255, 0, 0), 4)); // 红色右边框，线宽为3
        QRect rightBorder(rect.right() , rect.top(), 3, rect.height());
        painter->drawRect(rightBorder);

        // 恢复默认组合模式
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    }

    int rowCount = 0;
    for (auto row = colSortData->begin(); row != colSortData->end(); ++row) {
        QString date = row->date;
        QVector<quint8> list = row->prizes;

        // 绘制第一列数据
        if (index.row() == rowCount && index.column() == 0) {
            QRect rect = option.rect;

            painter->setBrush(QColor(135, 206, 235));
            painter->drawRect(rect);

            painter->setPen(QPen(QColor(0, 0, 0)));
            QFont font("Arial", qMin(rect.height(), rect.width()) * 0.4);
            painter->setFont(font);

            painter->drawText(rect, Qt::AlignCenter, date);
        }

        // 绘制其他列数据
        if (index.row() == rowCount && index.column() > 0 && index.column() <= 80) {
            quint8 prizeValue = list.at(index.column() - 1); // Adjust index to match the prize vector

            //如果数据结构中表格中的cvalue不为零
            if (prizeValue != 0 && markCol_Strike.contains(prizeValue)) {
                drawStrikePrize(painter,option.rect,prizeValue);
            }else if(prizeValue != 0 && markCol_Green.contains(prizeValue)){
                drawGreenCircle(painter,option.rect,prizeValue);
            }else if(prizeValue != 0){
                drawBlueCircle(painter,option.rect,prizeValue);
            }
        }

        rowCount++;
    }
}
