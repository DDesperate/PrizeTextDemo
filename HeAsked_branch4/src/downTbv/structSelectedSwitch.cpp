#include "downTbv.h"
void DownTableView::structSelectedSwitch(QModelIndex const &Index,QVector<slctTbRow>* list)
{
    for(auto row = list->begin();row != list->end();row++)
    {
        if(Index.row() == std::distance(list->begin(),row)){
            for(auto col = row->prizes.begin();col != row->prizes.end();col++)
            {
                if(col->prize == Index.column())
                {
                    if(col->isDeleted)
                    {
                        return;
                    }
                    col->switchSelect();
                }
            }
        }
    }
}
