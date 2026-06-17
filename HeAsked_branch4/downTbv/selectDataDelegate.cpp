#include"selectDataDelegate.h"
extern QFont aliFont;
void SelectDataDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);

    painter->setPen(QPen(QColor(0,0,0)));
    painter->setBrush(QColor(255,255,255,0));
    painter->drawRect(option.rect);

    int rowCount = 0;
    for (auto row = delegateSelectDataVec->begin(); row != delegateSelectDataVec->end(); ++row) {
        QString date = row->date;
        QList<slcInfo> list = row->prizes;

        //设置被选中行的颜色
        if(index.row() == rowCount)
        {
            if(row->isSelected)
            {
                QRect rect = option.rect;
                painter->setPen(QPen(QColor(0,0,0)));
                painter->setBrush(QColor(234,177,255));

                //设置颜色混合模式
                painter->setCompositionMode(QPainter::CompositionMode_Multiply);

                painter->drawRect(rect.x(),rect.y(),rect.width(),rect.height());

                //恢复默认模式
                painter->setCompositionMode(QPainter::CompositionMode_SourceOver);
            }
        }


        //绘制行首日期文本
        if(index.row()==rowCount && index.column() == 0){

            //获取形状信息
            QRect rect = option.rect;

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

        //绘制各色奖注
        for (auto item = list.begin(); item != list.end(); ++item) {
            QColor color = item->color;
            quint8 value = item->prize;
            // 处理color和value

            if(index.row()==rowCount && index.column()==value){
                //获取单元格图形信息
                QRect rect = option.rect;

                //计算单元格中心
                int centerX = rect.x() + rect.width() / 2;
                int centerY = rect.y() + rect.height() / 2;

                //获取圆的半径
                int radius = qMin(rect.width() * 0.5,rect.height() * 0.5);

                //抗锯齿
                painter->setRenderHint(QPainter::Antialiasing, true);

                //画圆
                QPair<int,int> pairTmp;
                pairTmp.first = index.row();
                pairTmp.second = index.column();

                //如果该元素被划掉
                if(item->isDeleted)
                {
                    painter->setPen(QColor(0,0,0));
                    painter->setBrush(QColor(255,255,255,0));
                    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

                    painter->drawLine(QPoint(rect.x(),rect.y()),QPoint(rect.x()+rect.width(),rect.y()+rect.height()));

                    //绘制文本
                    painter->setPen(QPen(QColor(0,0,0)));

                    //设置字体随单元格大小变化
                    QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
                    painter->setFont(font);

                    painter->drawText(rect, Qt::AlignCenter, QString::number(value).rightJustified(2,'0'));
                }
                //如果没有被划掉且该元素被选中，渲染为绿色
                else if(item->isSelect == true)
                {
                    painter->setPen(QColor(0,0,0));
                    painter->setBrush(QColor(0,255,0));
                    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

                    //绘制文本
                    painter->setPen(QPen(QColor(255,255,255)));

                    //设置字体随单元格大小变化
                    QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
                    painter->setFont(font);

                    painter->drawText(rect, Qt::AlignCenter, QString::number(value).rightJustified(2,'0'));
                }
                //其他情况：按照数据结构中的颜色绘制
                else{
                    //画圆
                    painter->setPen(QColor(0,0,0));
                    painter->setBrush(color);
                    painter->drawEllipse(centerX - radius, centerY - radius, radius * 2, radius * 2);

                    //绘制文本
                    painter->setPen(QPen(QColor(255,255,255)));

                    //设置字体随单元格大小变化
                    QFont font("Arial", qMin(rect.height(), rect.width())*0.4);
                    painter->setFont(font);

                    painter->drawText(rect, Qt::AlignCenter, QString::number(value).rightJustified(2,'0'));
                }


            }
        }
        rowCount++;
    }
}

