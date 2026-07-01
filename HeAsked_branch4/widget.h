#ifndef WIDGET_H
#define WIDGET_H

#include <QClipboard>
#include <QApplication>
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
#include <QPlainTextEdit>
#include <QPointer>
#include <QTimer>
#include <QDateTime>
#include <QProgressBar>
#include "numLineEdit/numLineEdit.h"
#include "flippableStackedWidget/flippableStackedWidget.h"
#include "przTbv/prizeTableView.h"
#include "upTbv/upTbv.h"
#include "downTbv/downTbv.h"
#include "SimulateLotteryDialog/simulatelotterydialog.h"
#include "CheckoutWgt/checkoutWgt.h"
#include "twoStepVerification/twoStepVerificationWgt.h"
#include "randomSelectListWgt/randomSelectListWidget.h"
#include "comparethread.h"
#include "multiListWgt/multiListWgt.h"
#include "tableWithCopy.h"
#include "sortTableElementsByCountWgt/sortTableElementsByCountWgt.h"
class ImportDialog;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void sendInput(const QVector<QList<quint8>> &left,const QVector<QList<quint8>> &right);
private slots:
    void recvProgressSlot(int totalCount,int count){
        compareProgressBar->setMaximum(totalCount);
        compareProgressBar->setValue(count);
    }
    void getItemValuePurple(QTableWidgetItem* tbwgtit);

    //模式改变，处理downTbv的同时，如果ColSortTbv存在的话需要对ColrSortTbv内的数据进行更新
    void handleModeChange(int mode);

    //右键表格弹出菜单
    void showContextMenu(const QPoint &pos);
private:
    void setUi(QWidget* widget);
    QStringList fileToStrList();

    ///tableWidget相关函数
    void import(const QStringList& strList);
    int insertLineData(const QString& date,const QList<quint8>& prizes);
    void initBackGround(QTableWidget* tbwgt);
    void markFixedNum(QTableWidget* tbwgt,const QList<quint8> fixedNum);
    void searchRepeat(QTableWidget* tbwgt);
    void searchNeighbor(QTableWidget* tbwgt);
    void searchMix(QTableWidget* tbwgt);
    void analysisRes(QVector<QPair<QString,QVector<QString>>>*,QList<QPair<QString,QVector<QString>>>&);    //提高代码复用性
    void repeatAnalysis(QTableWidget *tbwgt, QLineEdit *le, QTextBrowser *tb);
    void neighborAnalysis(QTableWidget* tbwgt,QLineEdit* le,QTextBrowser* tb);
    void mixAnalysis(QTableWidget* tbwgt,QLineEdit* le,QTextBrowser* tb);
    QList <int> getSelectedIndices(QTableWidget *tbwgt,bool selectColumns);
    void clearData(QTableWidget *tbwgt);
    void showCompareWidget();
    void cmnAnalysis(QLineEdit *le, QTextBrowser *tb);
    void SimulateLotteryTable();
    void SimulatedLottery(QLineEdit *prizeLe,QLineEdit *selectPrizeLe,QTextBrowser* tb);
    QStringList turnTableWidgetDataToStrList();
    bool checkDataExistenceForDate(const QString &date); //返回false则已有的表中不存在该期数，返回true则已存在
    void copyRow(QTableWidget *tbwgt,QLineEdit *le,QLineEdit *lePrize,QLineEdit *lePurple);
    void copySelectedItem(QTableWidget *tbwgt);
    void getTbwSamePrize(QTableWidget *tbwgt);
    void samePrizeCmn();
    void closeEvent(QCloseEvent *event){
        thread.quit();       // 终止事件循环
        thread.wait(1000);   // 等待1秒超时
        event->accept();       // 允许关闭窗口
    };

    //2024年12月12日19点02分添加,用于暂时存放混合查询得到的数据，数据用于后续复制
    QString mixAnalysis_data2Bcopy;


    //对比Tab
    QPair<int,QString> textToDataStructure(QVector<QList<quint8>> &data, const QString &text);
    QString dataStructureToText_withCount(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition);
    QString dataStructureToText_withoutCount(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition);

    //自选组合Tab
    QVector<QList<quint8>> selectCombine(int rowCount);

    //数字华容道:表中数据转二维数组,获得变换后的二维数组和期数列表
    void shufflingByCol(QVector<QString> &issue_num,QVector<QVector<quint8>> &prize2DArray);
    void shuffleSelectedColumns(QTableWidget *dataTable, const QList<int> &selectedColumns);
    QVector<QList<quint8>> getSelectedCol(QTableWidget *dataTable);

    ///tableWidget相关成员
    SimulateLotteryDialog* simulateLotteryDlg = nullptr;

    //重边号相同项Tab--相关
    QList<int> sameNum;

    ///成员:
    //radiobtn的起始值和结束值
    int startNum = 2;
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
//    QPushButton *searchBtn;
//    QMenu *searchMenu;
    QPushButton *repeatSearchBtn;
    QPushButton *neighborSearchBtn;
    QPushButton *mixSearchBtn;

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
    QWidget* pgTbw; //pageTableWidget
    QWidget* pgTbv; //pageTableView

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
    QPushButton *includeBtn;
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
    QPushButton *newestRepeatPrize;
    QPushButton *copyUnDeletePrize;
    //2025年4月9日 新增按钮:表格排序 暂且放在这一行
    QPushButton *btn_sortTableElementsByCount;

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
    //计算线程
    CompareThread compareThread;
    QThread thread;
    QMap<QList<quint8>,QPair<int,QString>> *NewRes = nullptr;

    QWidget *comparePage;
    QVBoxLayout *layV_comparePage;
    QHBoxLayout *layH_compare;
    QHBoxLayout *layH_compare_condition_btn;
    QVBoxLayout *layV_compare_condition;
    QHBoxLayout *layH_compare_btn;
    QVBoxLayout *layV_compare;
    QHBoxLayout *layH_table;
    QPlainTextEdit *leftTable;
    QPlainTextEdit *rightTable;
    QPushButton *compareBtn_condition;
    QPushButton *compareBtn;
    QTextEdit *compare_text;
    QTextEdit *compare_condition_text;
    QSpinBox *condition_spin;
    QPushButton *copy_condition;
    QPushButton *copy;
    QPushButton *checkoutBtn;
    QProgressBar *compareProgressBar;
    QPushButton *twoStepVerificationBtn;
    QPointer<TwoStepVerificationWgt> twoStepVerificationWgt = nullptr;
    QPointer<CheckoutWgt> checkoutWgt = nullptr;
    QPointer<SortTableElementsByCountWgt> sortTableElementsByCountWgt = nullptr;

    ///自选组合页面
    QWidget *selfSelectCombine;
    QVBoxLayout *layV_selfSelectCombine;
    QHBoxLayout *layH_copy_selfSelectCombine;
    //左侧复制数据
    QVBoxLayout *layV_copy_L_selfSelectCombine;
    QHBoxLayout *layH_copyBtn_L_selfSelectCombine;
    QPushButton *copyBtn_L_selfSelectCombine;
    QSpinBox *spinBox_L_selfSelectCombine;
    QPlainTextEdit *text_copy_L_selfSelectCombine;
    //右侧复制数据
    QVBoxLayout *layV_copy_R_selfSelectCombine;
    QHBoxLayout *layH_copyBtn_R_selfSelectCombine;
    QPushButton *copyBtn_R_selfSelectCombine;
    QSpinBox *spinBox_R_selfSelectCombine;
    QPlainTextEdit *text_copy_R_selfSelectCombine;
    //复制数据部分
    QVBoxLayout *layV_combine_selfSelectCombine;
    //组合部分
    QHBoxLayout *layH_combineBtn_selfSelectCombine;
    QPushButton *combine_btn;
    QPushButton *filter_btn;
    QSpinBox *filter_spinBox;
    QPlainTextEdit *combine_Res;
    QVector<QList<quint8>> combine_res_data;
    //暂时存放被复制的数据的数据结构
    //QVector<QList<quint8>> tmp_L_data;
    //QVector<QList<quint8>> tmp_R_data;

    ///数字华容道(随机乱序)
    QWidget *randomshuffling;
    QVBoxLayout *vlay_randomshuffling;
    QHBoxLayout *hlay_getInfo_randomshuffling;
    QSpinBox *spinbox_randomshuffling;
    QPushButton *getInfo_randomshuffling;
    QPushButton *getInfo_selectedRows;
    QHBoxLayout *hlay_shufflingitem_randomshuffling;
    QPushButton *shufflingitem_btn_mark;
    QPushButton *shufflingitem_randomshuffling;
    QPushButton *btn_moveSelectedLeft_randomshuffling;
    NumLineEdit *inputEdt_randomshuffling;
    QPushButton *btn_columnsSwap;
    TableWithCopy *dataTable_randomshuffling;
    QPushButton *btn_export_list;
    QPointer<MultiListWidget> multiListWgt;

    ///剔除页面
    QWidget *tab_NumberExclusion;

    QVBoxLayout *vlay_tab_NumberExclusion;  //总纵向布局
    QHBoxLayout *hlay1_tab_NumberExclusion;  //第一行
    QHBoxLayout *hlay2_tab_NumberExclusion;  //第二行
    QHBoxLayout *hlay3_tab_NumberExclusion;  //第三行
    QPushButton *tab_NumberExclusion_func_numberExclusion; //剔除页面下的数字剔除功能按钮
    QPushButton *tab_NumberExclusion_copy;  //剔除页面下的复制按钮
    QPushButton *tab_NumberExclusion_btn_filter;  //剔除页面下的筛选按钮，筛选元素为n的数组并显示
    QSpinBox *tab_NumberExclusion_spinbox_filter; //剔除页面下的筛选spinbox，输入n
    QPlainTextEdit *tab_NumberExclusion_plainText_originNumbers;    //用于装原始数据
    QPlainTextEdit *tab_NumberExclusion_plainText_numbersToBeExcluded;    //用于装原始数据
    QPlainTextEdit *tab_NumberExclusion_plainText_res;    //用于装原始数据

    QVector<QList<quint8>> tab_NumberExclusion_lastRes;


private slots:
    void addNumToExcludeList(int num);

};
#endif // WIDGET_H
