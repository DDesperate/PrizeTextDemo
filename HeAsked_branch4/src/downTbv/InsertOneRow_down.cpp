#include "downTbv/downTbv.h"

void DownTableView::insertRow(const QString &date,const QList<quint8> &prizes)
{
    addOneModelRow();

    QList<slcInfo> selectDataTableRow;
    QList<slcInfo> selectNeighborDataRow;
    QList<slcInfo> selectMixDataTableRow;

    QList<quint8> dbsign1;
    QList<slcInfo> dbsign2;
    QList<quint8> nbsign1;
    QList<slcInfo> nbsign2;
    QList<quint8> dbnbsign1;
    QList<slcInfo> dbnbsign2;

    foreach(auto value,prizes)
    {
        dbsign1.append(value);
        slcInfo info{QColor(49,102,204),value,false,false};
        selectDataTableRow.append(info);
        if(value>0&&value<81){
            nbsign1.append(value+1);
            nbsign1.append(value-1);
        }
    }

    //将选中的一行处理后插入到selectDataTableList中
    selectDataVec.insert(selectDataVec.end(),slctTbRow{false,date,selectDataTableRow});

    //邻号nbsign1去掉所有0和81
    nbsign1.removeAll(0);
    nbsign1.removeAll(81);

    //邻号nbsign1去重排序
    nbsign1 = nbsign1.toSet().toList();
    qSort(nbsign1.begin(), nbsign1.end());

    //将选中的一行处理后获取邻号插入到selectNeighborDataList中
    foreach(auto item,nbsign1)
    {
        slcInfo info{QColor(255,0,0),item,false,false};
        selectNeighborDataRow.append(info);
    }
    selectNeighborDataVec.insert(selectNeighborDataVec.end(),slctTbRow{false,date,selectNeighborDataRow});

    //dbnbsign1用于装邻号nbsign1和重号dbsign1的交集
    dbnbsign1 = dbsign1.toSet().intersect(nbsign1.toSet()).toList();

    //取dbnbsign1在dbsign1中的补集，涂成蓝色，即放进dbsign2中，dbsign2带有颜色属性
    foreach (quint8 value, dbsign1) {
        if (!dbnbsign1.contains(value)) {
            slcInfo dbsign2Info{QColor(49,102,204),value,false,false};
            dbsign2.append(dbsign2Info);
        }
    }

    //取dbnbsign1在nbsign1中的补集，涂成红色，即放进nbsign2中，nbsign2带有颜色属性
    foreach (quint8 value, nbsign1) {
        if (!dbnbsign1.contains(value)) {
            slcInfo nbsign2Item{QColor(255,0,0),value,false,false};
            nbsign2.append(nbsign2Item);
        }
    }

    //最后交集涂成黑色,得到dbnbsign2
    foreach(quint8 value,dbnbsign1){
        slcInfo dbnbsign2Item{QColor(0,0,0),value,false,false};
        dbnbsign2.append(dbnbsign2Item);
    }

    //prizeList装有重号和邻号，不带颜色属性
    //prizeList = dbsign1 + nbsign1;

    //colorPrizeList装有重号和邻号，带有颜色属性,带有选中属性
    selectMixDataTableRow = dbsign2 + nbsign2 + dbnbsign2;

    QPair<QString,QList<slcInfo>> pairTmp(date,selectMixDataTableRow);//日期，颜色，奖注
    selectMixDataVec.insert(selectMixDataVec.end(),slctTbRow{false,date,selectMixDataTableRow});

    if(mode == repeat)
    {
        getSamePrize(&selectDataVec);
    }
    if(mode == neighbor)
    {
        getSamePrize(&selectNeighborDataVec);
    }
    if(mode == mix)
    {
        getSamePrize(&selectMixDataVec);
    }

}
