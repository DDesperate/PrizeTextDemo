#include "upTbv.h"

//返回值为0:没有导入新数据
//返回值为-1:导入数据存在错误
//返回值为1:导入新数据成功
void UpTableView::import(const QStringList &data)
{
    ///如果什么文件都没有选，直接返回
    if(data.isEmpty())
        return;

    ///导入新表前的准备
    //清空行数，但不清理表格格式
    clearModel();

    //清空"已选中"集合
    selectedSet.clear();    //PrizeTableView类中的成员，代表已选中的行

    //空表对应的数据结构
    dataMap.clear();        //UpTableView的成员，UpTableView的数据存在此数据结构中?

    //清除上表中坐标集对应的数据结构(已写入count函数中)
    //countCoos.clear();


    ///导入txt为数据结构(导入过程中检测数据是否有错误)
    //用于判定当前循环所在行,用于定位数据不正确的行(初始化为1，便于后面遍历)
    int row = 1;

    //遍历QStringList &data(遍历导入的txt)
    for(const QString& rowString:data)
    {
        //去掉两端可能存在的空格
        QString rowString_trimmed = rowString.trimmed();

        ///获取日期date，通过正则检测日期是否符合格式，如果不符合则返回
        QString date = rowString_trimmed.left(8);
        if(checkDate(date) == -1){
            QMessageBox::warning(nullptr,"警告","txt中日期不符合格式:"+date+"\n"+"行数:"+QString::number(row));
            return;
        }

        ///获取奖注
        //1.检测奖注数量格式是否正确
        //2.转成符合uptable的数据结构(注意:prizeVec需要初始化size为80)
        QString prizes = rowString_trimmed.mid(9).trimmed();
        QStringList prizeList = prizes.split(" ");

        //创建一个80个元素的数组
        QVector<prizeInfo> prizeVec;
        prizeVec.resize(80);

        //将文本转化为数据结构
        int col = 1;    //初始化col为1，便于后面遍历
        for(QString prize:prizeList){
            bool ok;
            quint8 num = static_cast<quint8>(prize.toUInt(&ok));
            if(ok) {
                prizeInfo tmpInfo; tmpInfo.num = num;
                prizeVec[num-1] = tmpInfo;
            } else {
                QMessageBox::warning(nullptr,"警告","txt中奖注不符合格式\n行数:"+QString::number(row)+"列数"+QString::number(col));
                return;
            }
            col++;
        }
        if(col != 21)
        {
            QMessageBox::warning(nullptr,"警告","txt中第"+QString::number(row)+"行奖注数量错误");
        }

        ///将日期date和奖注列表prizeList添加到数据结构中
        dataMap.insert(date,tbRow{false,prizeVec});
        addOneModelRow();
        row++;
    }

    count();

    this->viewport()->update();

    this->scrollToBottom();
}
