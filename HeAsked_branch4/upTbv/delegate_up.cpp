#include "dataTableDelegate.h"
//int DataTableDelegate::i=0;
void DataTableDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{

    //委托原理:计算出当前窗口应该显示出哪些单元格，再到数据结构中查询该单元格应该显示什么图像，画图
    //在循环中qDebug() << "row" <<index.row() << "col" << index.column();
    //发现每次刷出图像时会打印行列值

    //qDebug() << "row" <<index.row() << "col" << index.column();


    QStyledItemDelegate::paint(painter, option, index);

    //获取单元格形状
    QRect rect = option.rect;

    //网格线加粗
    painter->setPen(QPen(QColor(0,0,0)));
    painter->setBrush(QColor(255,255,255,0));
    painter->drawRect(rect);

    //不用遍历整个map，从行数获取到相应的map中的信息
    //获取指向Map中第index.row()个键值对的指针
    auto it = delegateDataMap->begin();
    std::advance(it, index.row());

    QString date = it.key();
    //设置被选中行的颜色
    if(it.value().isSelected)
    {
        painter->setPen(QPen(QColor(0,0,0)));
        painter->setBrush(QColor(234,177,255));

        //设置颜色混合模式
        painter->setCompositionMode(QPainter::CompositionMode_Multiply);

        painter->drawRect(rect.x(),rect.y(),rect.width(),rect.height());

        //恢复默认模式
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
    }
    if(index.column() == 0){
        //qDebug() << "row" <<index.row() << "col" << index.column();

        //设置颜色混合模式
        painter->setCompositionMode(QPainter::CompositionMode_Multiply);

        //设置日期列背景颜色
        painter->setBrush(QColor(135,206,235));
        painter->drawRect(rect);

        //恢复默认模式
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

        //绘制文本
        painter->setPen(QPen(QColor(0,0,0)));

        //设置字体随单元格大小变化
        QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
        painter->setFont(font);

        painter->drawText(rect, Qt::AlignCenter, date);
    }


    else if(it.value().prizes.at(index.column()-1).num != 0){

        //计算单元格中心
        int centerX = rect.x() + rect.width() / 2;
        int centerY = rect.y() + rect.height() / 2;

        //获取圆的半径
        int radius = qMin(rect.width() * 0.5,rect.height() * 0.5);

        //抗锯齿
        painter->setRenderHint(QPainter::Antialiasing, true);

        //设置圆圈背景色
        painter->setBrush(it.value().prizes.at(index.column()-1).color);

        //painter->setBrush(it.value().prizes.at(index.column()).second);

        //设置圆圈轮廓色
        painter->setPen(QColor(0,0,0));

        //设置颜色混合模式
        painter->setCompositionMode(QPainter::CompositionMode_Multiply);

        painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

        //恢复默认模式
        painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

        //绘制文本
        painter->setPen(QPen(QColor(255,255,255)));

        //设置字体随单元格大小变化
        QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
        painter->setFont(font);

        painter->drawText(rect, Qt::AlignCenter, QString::number(index.column()).rightJustified(2,'0'));
    }


    //计数
    if(index.row() >= delegateDataMap->size() - maxCount){
        for(auto coo = delegateCountCoos->begin();coo != delegateCountCoos->end();coo++)
        {
            if(index.row() == (*coo).row && index.column()== (*coo).col){

                //画计数单元格
                painter->setBrush(QColor(148,152,153));
                painter->setPen(QColor(236,236,236));

                //设置颜色混合模式
                painter->setCompositionMode(QPainter::CompositionMode_Multiply);

                painter->drawRect(rect.x(),rect.y(),rect.width(),rect.height());

                //恢复默认模式
                painter->setCompositionMode(QPainter::CompositionMode_SourceOver);

                //抗锯齿
                painter->setRenderHint(QPainter::Antialiasing, true);

                //绘制文本
                //if(coo.text<5)
                painter->setPen(QPen(QColor(49,102,204)));

                //设置字体大小为单元格宽高中较小值的0.8倍
                QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
                painter->setFont(font);

                painter->drawText(rect, Qt::AlignCenter, (*coo).text);

                //一次只会paint一个格子，如果找到了就不用找了
                break;
            }
        }
    }


}

