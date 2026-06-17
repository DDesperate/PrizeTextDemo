#ifndef PRIZETABLEVIEW_H
#define PRIZETABLEVIEW_H
#include <QTableView>
#include <QStandardItemModel>
//#include "topbottomwidget/topBottomwidget.h"
//#include "animationWidget/animationWidget.h"

class PrizeTableView : public QTableView
{
    Q_OBJECT
public:
    //func:
    PrizeTableView(QWidget *parent = nullptr);
    ~PrizeTableView();

    //member:
    QStandardItemModel przModel;

protected:
    //animation move Widget
    //窗口:
    //1.移到顶部按钮
    //2.移到底部按钮
//    AnimationWidget *aMoveWgt;

    int aMoveWgtWidth;
    int totalWidth;
//    TopBottomWidget *topBottomWgt;
    QSet<QString> selectedSet;

    void resizeEvent(QResizeEvent *event);
    virtual void dbClkDate(QModelIndex const &Index) = 0;   //double click date
    void addOneModelRow(){QList<QStandardItem*> items;przModel.appendRow(items);}
    void removeOneModelRow(){przModel.removeRow(0);}
    void clearModel();
    void refreshOneRow(int row);

};

#endif
