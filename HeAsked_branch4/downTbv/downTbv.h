#include "przTbv/prizeTableView.h"
#include "selectDataDelegate.h"
#include "downStruct.h"
#include "modeWidget/modeWidget.h"

enum showMode { repeat, neighbor, mix };

class DownTableView: public PrizeTableView{
    Q_OBJECT
public:
    DownTableView(QWidget *parent = nullptr);
    ~DownTableView();

    void dbClkDate(const QModelIndex &Index) override;
    void insertRow(const QString &date,const QList<quint8>& prizes);    //插入一行
    void deleteVecByDate(QVector<slctTbRow> &vec, QString date);    //服务于deleteRow函数
    void deleteOneRow_passive(const QString &date);    //根据日期删除一行
    void deleteSelectedRow();   //删除被选中行，上表对应行清除高亮
    void listSelectItem(QVector<slctTbRow> *list);  //列出所有选中项(绿色)，放到lineEdit中
    void selectListItem(const QList<quint8> &list); //把列表list中的项全都标记出来
    void selectListItem_struct(const QList<quint8> &list,QVector<slctTbRow > &vec); //把列表list中的项全都标记出来
    void randomClearOneRow();
    void refreshItem(int x,int y);
    void strikeItem_struct(QVector<slctTbRow > &vec); //划掉(一种标记)选中项(从数据结构层面)
    void strikeItem();  //划掉被选中项
    void strikeSameItem_struct(QVector<slctTbRow > &vec);
    void strikeSameItem();
    void clearHighLight_struct(QVector<slctTbRow> *vec);
    void clearHighLightAndDeleted_struct(QVector<slctTbRow> *list);
    void clearHighLight();
    void clearHighLightAndDeleted();
    void clearAllDate();
    void randomSelectPrizes(int n); //从每一行的有效数据中，随机选出 n 个不重复的项目并高亮显示。
    void randomSelectPrizesForTbv(int n,QVector<slctTbRow>* list);
    QList<QList<quint8>> getSelectedPrize();
    QList<QList<quint8>> getSelectedPrizeForTbv(QVector<slctTbRow>* list);
    void exclude(const QList<quint8> &prizeListToBeExcluded);
    void excludeForTbv(const QList<quint8> &prizeListToBeExcluded,QVector<slctTbRow> *list);
    void include(const QList<quint8> &prizeListToBeIncluded);
    void includeForTbv(const QList<quint8> &prizeListToBeIncluded,QVector<slctTbRow> *list);
    void copyUnDeleteNum();
    void copyUnDeleteNum_struct(QVector<slctTbRow> &vec);
    void printSelectMixDataVec(const QVector<slctTbRow>& vec);
    QVector<slctTbRow> outputData();
    QVector<slctTbRow> outputRepeatData();
    void inputData(const QVector<slctTbRow> &newData);
    void showContextMenu_down(const QPoint &pos);

    showMode mode = repeat;
public slots:
    void selectMode(int n);



protected:
    void resizeEvent(QResizeEvent *event);

private:
    QVector<slctTbRow> selectDataVec;
    QVector<slctTbRow> selectNeighborDataVec;
    QVector<slctTbRow> selectMixDataVec;

    SelectDataDelegate selectDataTableD;

    QList<QList<quint8>> selectedPrizes;



    //ModeWidget *modeWgt;
    //AnimationWidget *aModeWgt;
    //int aModeWgtWidth;

    //func:

    //获取多期数据中相同的奖注，发送给lineEidt
    void getSamePrize(QVector<slctTbRow> *list);

    //点击一项后更改对应的数据结构(已被选中更改为未选中，未选中更改为已被选中)
    void structSelectedSwitch(QModelIndex const &Index,QVector<slctTbRow>* list);

private slots:

    void selectItem(QModelIndex const &Index);

signals:
    void sendNum(int num);
    void sendSamePrizeList(const QList<quint8> &prizeList);
    void deleteOneRow(const QString &date);

};
