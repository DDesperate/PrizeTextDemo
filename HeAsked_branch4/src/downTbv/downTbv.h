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
    void randomClearOneRow();
    void refreshItem(int x,int y);
    void strikeItem_struct(QVector<slctTbRow > &vec);
    void strikeItem();
    void strikeSameItem_struct(QVector<slctTbRow > &vec);
    void strikeSameItem();
    void clearHighLight_struct(QVector<slctTbRow> *vec);
    void clearHighLight();
    void clearAllDate();
    void randomSelectPrizes(int n);
    void randomSelectPrizesForTbv(int n,QVector<slctTbRow>* list);
    QList<QList<quint8>> getSelectedPrize();
    QList<QList<quint8>> getSelectedPrizeForTbv(QVector<slctTbRow>* list);
    void exclude(const QList<quint8> &prizeListToBeExcluded);
    void excludeForTbv(const QList<quint8> &prizeListToBeExcluded,QVector<slctTbRow> *list);


protected:
    void resizeEvent(QResizeEvent *event);

private:
    QVector<slctTbRow> selectDataVec;
    QVector<slctTbRow> selectNeighborDataVec;
    QVector<slctTbRow> selectMixDataVec;

    SelectDataDelegate selectDataTableD;

    QList<QList<quint8>> selectedPrizes;

    showMode mode;

    //ModeWidget *modeWgt;
    //AnimationWidget *aModeWgt;
    //int aModeWgtWidth;

    //func:

    //获取多期数据中相同的奖注，发送给lineEidt
    void getSamePrize(QVector<slctTbRow> *list);

    //点击一项后更改对应的数据结构(已被选中更改为未选中，未选中更改为已被选中)
    void structSelectedSwitch(QModelIndex const &Index,QVector<slctTbRow>* list);

private slots:
    void selectMode(int n);
    void selectItem(QModelIndex const &Index);

signals:
    void sendSamePrizeList(const QList<quint8> &prizeList);
    void deleteOneRow(const QString &date);

};
