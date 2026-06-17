#ifndef WIDGET_H
#define WIDGET_H

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QToolButton>
#include <QMenu>
#include <QRadioButton>
#include <QLabel>
#include <QSpinBox>
#include <QLineEdit>
#include <QLCDNumber>
#include <QPushButton>
#include <QSplitter>
#include <QTableWidget>
#include <QTextBrowser>
#include <QPointer>
#include <QTimer>
#include "numLineEdit/numLineEdit.h"
#include "flippableStackedWidget/flippableStackedWidget.h"
#include "przTbv/prizeTableView.h"
#include "upTbv/upTbv.h"
#include "downTbv/downTbv.h"
#include "SimulateLotteryDialog/simulatelotterydialog.h"
#include "CheckoutWgt/checkoutWgt.h"
#include "randomSelectListWgt/randomSelectListWidget.h"
class ImportDialog;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void setUi(QWidget* widget);
    QStringList fileToStrList();

    ///tableWidget相关函数
    void initTableWidget(QTableWidget* tbwgt);
    void import(const QStringList& strList);
    int insertLineData(const QString& date,const QList<quint8>& prizes);
    void initBackGround();
    void searchRepeat();
    void searchNeighbor();
    void searchMix();
    void analysisRes(QVector<QPair<QString,QVector<QString>>>*,QList<QPair<QString,QVector<QString>>>&);    //提高代码复用性
    void repeatAnalysis(QTableWidget *tbwgt, QLineEdit *le, QTextBrowser *tb);
    void neighborAnalysis(QTableWidget* tbwgt,QLineEdit* le,QTextBrowser* tb);
    void mixAnalysis(QTableWidget* tbwgt,QLineEdit* le,QTextBrowser* tb);
    QList <int> requestRowId();
    void clearData(QTableWidget *tbwgt);
    void showCompareWidget();
    void cmnAnalysis(QLineEdit *le, QTextBrowser *tb);
    void SimulateLotteryTable();
    void SimulatedLottery(QLineEdit *prizeLe,QLineEdit *selectPrizeLe,QTextBrowser* tb);
    QStringList turnTableWidgetDataToStrList();
    bool checkDataExistenceForDate(const QString &date); //返回false则已有的表中不存在该期数，返回true则已存在
    void copyRow(QTableWidget *tbwgt,QLineEdit *le,QLineEdit *lePrize,QLineEdit *lePurple);
    void getTbwSamePrize(QTableWidget *tbwgt);
    void samePrizeCmn();
    QString prizeListToString(const QList<quint8>& list);

    //对比Tab
    QVector<QList<quint8>> textToDataStructure(const QString &text);
    QString dataStructureToText(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition);
    QList<quint8> getCommonItems(const QList<quint8>& list1, const QList<quint8>& list2);

    ///tableWidget相关成员
    SimulateLotteryDialog* simulateLotteryDlg = nullptr;

    //重边号相同项Tab--相关
    QList<int> sameNum;

    ///成员:
    //radiobtn的起始值和结束值
    int startNum = 3;
    int endNum = 18;

    //最外层布局
    QVBoxLayout *layV;



    ///共享栏
    //第一行:spinbox+radioBtn
    QHBoxLayout *layH_radioBtn_spinBox;
    QLabel *analysisNumLabel;
    QSpinBox *analysisNumSpinBox;
    QButtonGroup *group;
    QButtonGroup *modeGroup;
    QRadioButton *repeatMode;
    QRadioButton *neighborMode;
    QRadioButton *mixMode;

    //第二行:numLineEdit+lcd
    QHBoxLayout *layH_lineEdit_lcd;
    NumLineEdit *inputEdt;
    QLCDNumber *inputLcd;

    //第三行:button
    QHBoxLayout *layH_prztb_multiFuncBtns;

    //导入按钮
    QPushButton *importBtn;
    QMenu *importMenu;
    QAction *importTxt;
    QAction *importOneRow;
    ImportDialog *importDialog;

    //查询按钮
    QPushButton *searchBtn;
    QMenu *searchMenu;
    QAction *repeatSearchBtn;
    QAction *neighborSearchBtn;
    QAction *mixSearchBtn;

    //清除高亮按钮
    QPushButton *clearBtn;
    QMenu *clearMenu;
    QAction *clearSearchBtn;
    QAction *clearRowBtn;

    //删除按钮
    QPushButton *deleteBtn;

    //切换视图按钮
    QPushButton *changeViewPortBtn;


    ///堆叠窗口，用于设置两种页面
    FlippableStackedWidget *stackedWidget;
    QWidget* pgTbw;
    QWidget* pgTbv;

    ///tbv窗口
    QVBoxLayout *layV_page1;

    //分裂布局和两个tableView
    QSplitter *splitter;
    UpTableView *upTbv;
    DownTableView *downTbv;

    //相同项和随机选择n行
    QHBoxLayout *layH_repeatPrize_selectRows;
    QLabel *label_randomSelectRows;
    QSpinBox *spinBox_randomSelectRows;
    QLabel *label_row;
    QPushButton *okBtn_randomSelectRows;
    QPushButton *deleteBtn_randomDeleteOneRow;
    QFrame *lineV_repeatPrize_selectRows;
    QLabel *samePrizeLabel;
    NumLineEdit *samePrizeLineEdit;
    QLCDNumber *samePrizeLcdNum;

    //随机选
    QHBoxLayout *layH_randomSelect;
    QLabel *randomSelectLabel1;
    QSpinBox *randomSelectSpinBox1;
    QLabel *rowLabel1;
    QPointer<RandomSelectListWidget> randomSelectListWgt;
    QTimer *randomSelectTimer;
    QPushButton *randomSelectStart;
    QPushButton *randomSelectEnd;
    QPushButton *excludeBtn;
    QFrame *lineV1;
    QLabel *label_exclude;
    NumLineEdit *excludeEdtline;
    QLCDNumber *lcdNumber_exclude;


    //清除和划掉
    QHBoxLayout *layH_strike_clear;
    QPushButton *clearAllDateBtn_downTbv;
    QPushButton *clearSelectedRowBtn_downTbv;
    QPushButton *strikeItemBtn_downTbv;
    QPushButton *strikeSameItemBtn_downTbv;
    QPushButton *clearHighLight_downTbv;

    //4.2-1:
    QHBoxLayout *layH_page2;
    QTableWidget *dataTable;
    QTabWidget *tabWidget;
    QWidget *analysis1;
    QVBoxLayout *layV_analysis1;
    QVBoxLayout *layV_analysis2;
    QHBoxLayout *layH1_analysis1;
    QHBoxLayout *layH2_analysis1;
    QHBoxLayout *layH1_analysis2;
    QPushButton *repeatAnalysisBtn;
    QTextBrowser *repeatAnalysisText;
    QPushButton *neighborAnalysisBtn;
    QTextBrowser *neighborAnalysisText;
    QPushButton *mixAnalysisBtn;
    QTextBrowser *mixAnalysisText;
    QWidget *analysis2;
    QWidget *cmn;
    QVBoxLayout *layV_cmn;
    QHBoxLayout *layH_cmn;
    NumLineEdit *cmnLineEdt;
    QLCDNumber *cmnLcd;
    QPushButton *cmnBtn;
    QTextBrowser *cmnText;
    QWidget *winningTest;
    QVBoxLayout *layV_winTest;
    QHBoxLayout *layH_win;
    QLabel *winNumLabel;
    NumLineEdit *winNumLineEdit;
    QHBoxLayout *layH_select;
    QLabel *selectNumLabel;
    NumLineEdit *selectNumLineEdit;
    QLCDNumber *selectNumLcd;
    QHBoxLayout *layH_btn;
    QLabel *winRes;
    QPushButton *startTestBtn;
    QPushButton *detailInfoBtn;
    QTextBrowser *detailText;

    ///重边号相同项
    QWidget *samePrizeAnalysis;
    QVBoxLayout *layV_samePrizeAnalysis;
    QHBoxLayout *layH_samePrizeBtn;
    QHBoxLayout *layH_samePrizeCmnBtn;
    QPushButton *getSamePrizeBtn;
    QPushButton *samePrizeCmnBtn;
    QTextBrowser *samePrizeText;
    QTextBrowser *samePrizeCmnText;

    ///对比页面
    QWidget *comparePage;
    QVBoxLayout *layV_comparePage;
    QHBoxLayout *layH_compare;
    QHBoxLayout *layH_compare_condition_btn;
    QVBoxLayout *layV_compare_condition;
    QHBoxLayout *layH_compare_btn;
    QVBoxLayout *layV_compare;
    QHBoxLayout *layH_table;
    QTextEdit *leftTable;
    QTextEdit *rightTable;
    QPushButton *compareBtn_condition;
    QPushButton *compareBtn;
    QTextEdit *compare_text;
    QTextEdit *compare_condition_text;
    QSpinBox *condition_spin;
    QPushButton *copy_condition;
    QPushButton *copy;
    QPushButton *checkoutBtn;
    QPointer<CheckoutWgt> checkoutWgt = nullptr;
    QMap<QList<quint8>,QPair<int,QString>> res_samePrizes;


};
#endif // WIDGET_H
