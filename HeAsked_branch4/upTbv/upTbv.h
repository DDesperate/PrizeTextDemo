#include "przTbv/prizeTableView.h"
#include "dataTableDelegate.h"
#include "upStruct.h"
class UpTableView: public PrizeTableView{
    Q_OBJECT
public:
    UpTableView(QWidget *parent = nullptr);
    ~UpTableView();

    void import(const QStringList &data);
    int  insertOneRow(const QString &date, const QList<quint8> &prizes);
    void refreshOneRowByDate(const QString& date);
    void dbClkDate(const QModelIndex &Index) override;
    void clearSearchHighLight();
    void clearSelectedRowHighLight();
    void searchRepeat(const QList<quint8> &numList,int row);
    void searchNeighbor(const QList<quint8> &numList,int row);
    void searchMix(const QList<quint8> &numList,int row);
    void deleteSelectedRow();
    void unMarkOneRow(const QString &date); //取消选中一行(包括selectedSet中清除)
    void getRandomMap(int n);
    QStringList turnDataToStringList();
    QList<quint8> getLastRow();
    void showContextMenu_upTbv(const QPoint &pos);
private:
    int checkDate(const QString &date);
    int checkPrizes(const QString &date,QList<quint8> prizes);  //返回-1，行奖注数量出错，返回其他值，则表示出错的列数
    void count();
    QList<quint8> vec80toList(QVector<prizeInfo>);
    QVector<prizeInfo> listToVec80(QList<quint8>);



    DataTableDelegate dataTableD;      //DataTable Delegate
    QMap<QString,tbRow> dataMap;    //数据表
    QList<coo> countCoos;   //计数坐标集

signals:
    void insertToInputEdt(const QList<quint8> &prizes);
    void insertToDownTbv(const QString& date,const QList<quint8> &prizes);
    void cancelInsert(const QString &date);
};
