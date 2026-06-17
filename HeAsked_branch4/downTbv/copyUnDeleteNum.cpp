#include "downTbv/downTbv.h"
#include<QClipboard>
#include<QApplication>

void DownTableView::copyUnDeleteNum()
{
    if(mode == repeat){
        copyUnDeleteNum_struct(selectDataVec);
        //printSelectMixDataVec(selectNeighborDataVec); //打印下表数据结构
    }
    if(mode == mix)
    {
        copyUnDeleteNum_struct(selectMixDataVec);
        printSelectMixDataVec(selectNeighborDataVec);
    }

    if(mode == neighbor)
    {
        copyUnDeleteNum_struct(selectNeighborDataVec);
        //printSelectMixDataVec(selectNeighborDataVec);
    }
}

void DownTableView::copyUnDeleteNum_struct(QVector<slctTbRow> &vec)
{
    QString res;
    bool empty = true;
    for(const slctTbRow &row:vec)
    {
        if(row.isSelected)
        {
            empty = false;
            for(const slcInfo &item:row.prizes)
            {
                if(!item.isDeleted)
                {
                    res += QString::number(item.prize).rightJustified(2,'0') + " ";
                }
            }
        }
        res = res.trimmed() + "\n";
    }
    if(empty)
    {
        QMessageBox::warning(nullptr,tr("警告"),tr("未选中任何行"));
    }
    else
    {
        QApplication::clipboard()->setText(res);
        QMessageBox::warning(nullptr,tr("提示"),tr("复制成功"));
    }

}
