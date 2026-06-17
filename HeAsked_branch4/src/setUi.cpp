#include "widget.h"
#include "qss.h"
#include "PaintImages/images.hpp"
#include "importDialog/importDialog.h"
void Widget::setUi(QWidget* widget)
{
    //设置初始大小
    widget->resize(1750,850);

    //设置字体
    extern QFont aliFont;
    widget->setFont(aliFont);

    //最外层布局
    layV = new QVBoxLayout(widget);
    widget->setLayout(layV);

    ///共享栏

    //第一行:spinbox
    layH_radioBtn_spinBox  = new QHBoxLayout();
    analysisNumLabel = new QLabel(tr("统计数量"));
    analysisNumSpinBox = new QSpinBox(widget);
    layH_radioBtn_spinBox->addWidget(analysisNumLabel);
    layH_radioBtn_spinBox->addWidget(analysisNumSpinBox);
    analysisNumSpinBox->setRange(0, 1000); // 设置范围
    analysisNumSpinBox->setValue(50); // 设置初始值


    //第一行:radioBtn
    group = new QButtonGroup(widget);
    for (int i = startNum; i <= endNum; i++)
    {
        auto radioBtn = new QRadioButton(QString::fromUtf8("选") + QString::number(i),widget);
        radioBtn->setFont(aliFont);
        radioBtn->setStyleSheet(radioBtnStyle);
        group->addButton(radioBtn);
        layH_radioBtn_spinBox->addWidget(radioBtn);
        if (i == startNum)
        {
            radioBtn->setChecked(true);
        }
    }
    layH_radioBtn_spinBox->addStretch();

    //modeGroup
    modeGroup = new QButtonGroup(widget);
    repeatMode = new QRadioButton(tr("重号模式"),widget);
    neighborMode = new QRadioButton(tr("边号模式"),widget);
    mixMode = new QRadioButton(tr("混合模式"),widget);
    repeatMode->setFont(aliFont);
    neighborMode->setFont(aliFont);
    mixMode->setFont(aliFont);
    modeGroup->addButton(repeatMode);
    modeGroup->addButton(neighborMode);
    modeGroup->addButton(mixMode);
    layH_radioBtn_spinBox->addWidget(repeatMode);
    layH_radioBtn_spinBox->addWidget(neighborMode);
    layH_radioBtn_spinBox->addWidget(mixMode);

    layV->addLayout(layH_radioBtn_spinBox);

    //第二行:numLineEdit+lcd
    layH_lineEdit_lcd = new QHBoxLayout();
    inputEdt = new NumLineEdit(widget);
    inputEdt->setObjectName("inputEdt");
    inputLcd = new QLCDNumber(widget);
    inputLcd->setSegmentStyle(QLCDNumber::Flat);
    layH_lineEdit_lcd->addWidget(inputEdt);
    layH_lineEdit_lcd->addWidget(inputLcd);
    layV->addLayout(layH_lineEdit_lcd);

    //lineEdit中的文本发生变化，发送信号给lcdNumber，使其计数改变
    connect(inputEdt,&NumLineEdit::textChanged,this,[=](){
        if(inputEdt->text().isEmpty())
            inputLcd->display(0);
        else{
            //QStringList strList = inputEdt->text().trimmed().split(" ");
            inputLcd->display(inputEdt->text().trimmed().split(" ").length());
        }
    });

    //第三行:button
    layH_prztb_multiFuncBtns  = new QHBoxLayout();

    //导入按钮
    importBtn = new QPushButton(widget);
    importMenu = new QMenu(widget);
    importTxt = new QAction(widget);
    importOneRow = new QAction(widget);
    importBtn->setText(" 导入 ");
    importTxt = importMenu->addAction(QIcon(":/images/txt-file-symbol.png"),tr("导入文本"));
    importOneRow = importMenu->addAction(QIcon(":/images/row.png"),tr("导入一期"));
    importBtn->setMenu(importMenu);
    importMenu->setFont(aliFont);

    importDialog = new ImportDialog(this);

    //查询按钮
    searchBtn = new QPushButton(widget);
    searchMenu = new QMenu(widget);
    repeatSearchBtn = new QAction(widget);
    neighborSearchBtn = new QAction(widget);
    mixSearchBtn = new QAction(widget);
    searchBtn->setText(" 标记 ");
    repeatSearchBtn = searchMenu->addAction(QIcon(QPixmap::fromImage(im_greenCircle())),tr("重号查询"));
    neighborSearchBtn = searchMenu->addAction(QIcon(QPixmap::fromImage(im_redCircle())),tr("邻号查询"));
    mixSearchBtn = searchMenu->addAction(QIcon(QPixmap::fromImage(im_MixCircle())),tr("混合查询"));
    searchBtn->setMenu(searchMenu);
    searchMenu->setFont(aliFont);

    //清除按钮
    clearBtn = new QPushButton(widget);
    clearMenu = new QMenu(widget);
    clearSearchBtn = new QAction(widget);
    clearRowBtn = new QAction(widget);
    clearBtn->setText(" 取消 ");
    clearSearchBtn = clearMenu->addAction(QIcon(QPixmap::fromImage(im_ClearhighLight())),tr("取消标记"));
    clearRowBtn = clearMenu->addAction(QIcon(":/images/menu.png"),tr("取消选中"));
    clearBtn->setMenu(clearMenu);
    clearMenu->setFont(aliFont);

    //删除按钮
    deleteBtn = new QPushButton(tr(" 删除 "),widget);

    //切换视图按钮
    changeViewPortBtn = new QPushButton(tr("切换视图"),widget);

    //按钮加入第三行的水平布局
    layH_prztb_multiFuncBtns->addWidget(importBtn);
    layH_prztb_multiFuncBtns->addWidget(searchBtn);
    layH_prztb_multiFuncBtns->addWidget(clearBtn);
    layH_prztb_multiFuncBtns->addWidget(deleteBtn);
    layH_prztb_multiFuncBtns->addWidget(changeViewPortBtn);
    layH_prztb_multiFuncBtns->addStretch();
    layV->addLayout(layH_prztb_multiFuncBtns);

    ///堆叠窗口，用于设置两种页面
    stackedWidget = new FlippableStackedWidget(widget);
    // 创建两个 QWidget 并添加到 stackWidget 中
    pgTbw = new QWidget(widget);
    pgTbv = new QWidget(widget);
    stackedWidget->addWidget(pgTbv);
    stackedWidget->addWidget(pgTbw);
    layV->addWidget(stackedWidget);

    ///tbv窗口
    layV_page1 = new QVBoxLayout(pgTbv);

    //分裂布局和两个tableView
    splitter = new QSplitter(pgTbv);
    upTbv = new UpTableView(pgTbv);
    downTbv = new DownTableView(pgTbv);
    splitter->setOrientation(Qt::Vertical);
    splitter->addWidget(upTbv);
    splitter->addWidget(downTbv);
    splitter->setHandleWidth(5);
    splitter->setStyleSheet("QSplitter::handle { background-color: red; }");
    layV_page1->addWidget(splitter);

    //相同项
    layH_repeatPrize_selectRows = new QHBoxLayout();
    label_randomSelectRows = new QLabel(tr("随机选"),widget);
    spinBox_randomSelectRows = new QSpinBox(widget);
    label_row = new QLabel(tr("行"));
    okBtn_randomSelectRows = new QPushButton(tr("确定"),widget);
    deleteBtn_randomDeleteOneRow = new QPushButton(tr("随机删除一行"),widget);
    lineV_repeatPrize_selectRows = new QFrame(widget);
    samePrizeLabel = new QLabel(tr("相同项"),widget);
    samePrizeLineEdit = new NumLineEdit(widget);
    samePrizeLcdNum = new QLCDNumber(widget);
    samePrizeLcdNum->setSegmentStyle(QLCDNumber::Flat);
    samePrizeLineEdit->setReadOnly(true);
    lineV_repeatPrize_selectRows->setFrameShape(QFrame::VLine);
    layH_repeatPrize_selectRows->addWidget(label_randomSelectRows);
    layH_repeatPrize_selectRows->addWidget(spinBox_randomSelectRows);
    layH_repeatPrize_selectRows->addWidget(label_row);
    layH_repeatPrize_selectRows->addWidget(okBtn_randomSelectRows);
    layH_repeatPrize_selectRows->addWidget(deleteBtn_randomDeleteOneRow);
    layH_repeatPrize_selectRows->addWidget(lineV_repeatPrize_selectRows);
    layH_repeatPrize_selectRows->addWidget(samePrizeLabel);
    layH_repeatPrize_selectRows->addWidget(samePrizeLineEdit);
    layH_repeatPrize_selectRows->addWidget(samePrizeLcdNum);
    layH_repeatPrize_selectRows->addStretch();
    layV_page1->addLayout(layH_repeatPrize_selectRows);

    //lineEdit中的文本发生变化，发送信号给lcdNumber，使其计数改变
    connect(samePrizeLineEdit,&NumLineEdit::textChanged,this,[=](){
        if(samePrizeLineEdit->text().isEmpty())
            samePrizeLcdNum->display(0);
        else{
            //QStringList strList = samePrizeLineEdit->text().trimmed().split(" ");
            samePrizeLcdNum->display(samePrizeLineEdit->text().trimmed().split(" ").length());
        }
    });


    //随机选
    layH_randomSelect = new QHBoxLayout();
    randomSelectLabel1 = new QLabel(tr("随机选"),this);
    randomSelectSpinBox1 = new QSpinBox(this);
    rowLabel1 = new QLabel(tr("个数字"),this);
    randomSelectStart = new QPushButton(tr("开始"),this);
    randomSelectEnd = new QPushButton(tr("停止"),this);
    lineV1 = new QFrame(this);
    label_exclude = new QLabel(tr("剔除项"),this);
    excludeEdtline = new NumLineEdit(this);
    lcdNumber_exclude = new QLCDNumber(this);
    excludeBtn = new QPushButton(tr("剔除"),this);
    layH_randomSelect->addWidget(randomSelectLabel1);
    layH_randomSelect->addWidget(randomSelectSpinBox1);
    layH_randomSelect->addWidget(rowLabel1);
    layH_randomSelect->addWidget(randomSelectStart);
    layH_randomSelect->addWidget(randomSelectEnd);
    layH_randomSelect->addWidget(lineV1);
    lineV1->setFrameShape(QFrame::VLine);
    layH_randomSelect->addWidget(lineV1);
    layH_randomSelect->addWidget(label_exclude);
    layH_randomSelect->addWidget(excludeEdtline);
    layH_randomSelect->addWidget(lcdNumber_exclude);
    lcdNumber_exclude->setSegmentStyle(QLCDNumber::Flat);
    layH_randomSelect->addWidget(excludeBtn);
    layH_randomSelect->addStretch();
    layV_page1->addLayout(layH_randomSelect);

    //lineEdit中的文本发生变化，发送信号给lcdNumber，使其计数改变
    connect(excludeEdtline,&NumLineEdit::textChanged,this,[=](){
        if(excludeEdtline->text().isEmpty())
            lcdNumber_exclude->display(0);
        else{
            //QStringList strList = samePrizeLineEdit->text().trimmed().split(" ");
            lcdNumber_exclude->display(samePrizeLineEdit->text().trimmed().split(" ").length());
        }
    });


    //下表的清除和划掉功能
    layH_strike_clear = new QHBoxLayout();
    clearAllDateBtn_downTbv = new QPushButton(tr("全部清除"),widget);
    clearSelectedRowBtn_downTbv = new QPushButton(tr("清除选中行"),widget);
    strikeItemBtn_downTbv = new QPushButton(tr("划掉一项"),widget);
    strikeSameItemBtn_downTbv = new QPushButton(tr("划掉相同项"),widget);
    clearHighLight_downTbv = new QPushButton(tr("清除高亮"),widget);
    layH_strike_clear->addWidget(clearAllDateBtn_downTbv);
    layH_strike_clear->addWidget(clearSelectedRowBtn_downTbv);
    layH_strike_clear->addWidget(strikeItemBtn_downTbv);
    layH_strike_clear->addWidget(strikeSameItemBtn_downTbv);
    layH_strike_clear->addWidget(clearHighLight_downTbv);
    layH_strike_clear->addStretch();
    layV_page1->addLayout(layH_strike_clear);



    layH_page2 = new QHBoxLayout(pgTbw);
    dataTable = new QTableWidget(pgTbw);
    tabWidget = new QTabWidget(pgTbw);
    layH_page2->addWidget(dataTable);
    layH_page2->addWidget(tabWidget);
    tabWidget->setStyleSheet(tabWidgetQss);


    //tab窗口一
    analysis1 = new QWidget(tabWidget);
    layV_analysis1 = new QVBoxLayout(analysis1);
    layH1_analysis1 = new QHBoxLayout(analysis1);
    layH2_analysis1 = new QHBoxLayout(analysis1);
    repeatAnalysisBtn = new QPushButton(tr(" 重号分析 "),analysis1);
    repeatAnalysisText = new QTextBrowser(analysis1);
    neighborAnalysisBtn = new QPushButton(tr(" 边号分析 "),analysis1);
    neighborAnalysisText = new QTextBrowser(analysis1);
    layV_analysis1->addLayout(layH1_analysis1);
    layH1_analysis1->addWidget(repeatAnalysisBtn);
    layH1_analysis1->addStretch();
    layV_analysis1->addWidget(repeatAnalysisText);
    layV_analysis1->addLayout(layH2_analysis1);
    layH2_analysis1->addWidget(neighborAnalysisBtn);
    layH2_analysis1->addStretch();
    layV_analysis1->addWidget(neighborAnalysisText);
    tabWidget->addTab(analysis1, QString("重号/边号分析"));
    analysis2 = new QWidget(tabWidget);
    layV_analysis2 = new QVBoxLayout(analysis2);
    layH1_analysis2 = new QHBoxLayout();
    mixAnalysisBtn = new QPushButton(tr(" 混合分析 "),analysis2);
    mixAnalysisText = new QTextBrowser(analysis2);
    layV_analysis2->addLayout(layH1_analysis2);
    layH1_analysis2->addWidget(mixAnalysisBtn);
    layH1_analysis2->addStretch();
    layV_analysis2->addWidget(mixAnalysisText);
    tabWidget->addTab(analysis2, QString("混合分析"));
    cmn = new QWidget(tabWidget);
    layV_cmn = new QVBoxLayout(cmn);
    layH_cmn = new QHBoxLayout();
    cmnLineEdt = new NumLineEdit(cmn);
    cmnLcd = new QLCDNumber(cmn);
    cmnLcd->setSegmentStyle(QLCDNumber::Flat);
    cmnLcd->setStyleSheet(lcdStyle);
    cmnBtn = new QPushButton(tr("排列组合"),cmn);
    cmnText = new QTextBrowser(cmn);
    layV_cmn->addLayout(layH_cmn);
    layH_cmn->addWidget(cmnLineEdt);
    layH_cmn->addWidget(cmnLcd);
    layV_cmn->addWidget(cmnBtn);
    layV_cmn->addWidget(cmnText);
    tabWidget->addTab(cmn, QString("排列组合"));

    ///中奖检验
    winningTest = new QWidget(tabWidget);
    layV_winTest = new QVBoxLayout(winningTest);
    layH_win = new QHBoxLayout();
    winNumLabel = new QLabel(tr("开奖号码"),winningTest);
    winNumLineEdit = new NumLineEdit(winningTest);
    selectNumLabel = new QLabel(tr("选中号码"),winningTest);
    selectNumLineEdit = new NumLineEdit(winningTest);
    selectNumLcd = new QLCDNumber(winningTest);
    selectNumLcd->setSegmentStyle(QLCDNumber::Flat);
    winRes = new QLabel(tr("中奖结果"),winningTest);
    startTestBtn = new QPushButton(tr("开始检验"),winningTest);
    detailInfoBtn = new QPushButton(tr("详细信息"),winningTest);
    layV_winTest->addLayout(layH_win);
    layH_win->addWidget(winNumLabel);
    layH_win->addWidget(winNumLineEdit);

    //第二行;
    layH_select = new QHBoxLayout();
    layV_winTest->addLayout(layH_select);
    layH_select->addWidget(selectNumLabel);
    layH_select->addWidget(selectNumLineEdit);
    layH_select->addWidget(selectNumLcd);
    tabWidget->addTab(winningTest, QString("中奖检验"));

    //第三行
    layH_btn = new QHBoxLayout();
    layH_btn->addWidget(winRes);
    layH_btn->addWidget(startTestBtn);
    layH_btn->addWidget(detailInfoBtn);
    layV_winTest->addLayout(layH_btn);
    layH_btn->addStretch();
    detailText = new QTextBrowser(winningTest);
    layV_winTest->addWidget(detailText);

    ///重边号相同项
    //创建对象
    samePrizeAnalysis = new QWidget(tabWidget);
    layV_samePrizeAnalysis = new QVBoxLayout(samePrizeAnalysis);
    layH_samePrizeBtn = new QHBoxLayout();
    layH_samePrizeCmnBtn = new QHBoxLayout();;
    getSamePrizeBtn = new QPushButton(tr(" 求相同项 "),samePrizeAnalysis);
    samePrizeCmnBtn = new QPushButton(tr(" 排列组合 "),samePrizeAnalysis);
    samePrizeText = new QTextBrowser(samePrizeAnalysis);
    samePrizeCmnText = new QTextBrowser(samePrizeAnalysis);

    //布局
    layV_samePrizeAnalysis->addLayout(layH_samePrizeBtn);
    layH_samePrizeBtn->addWidget(getSamePrizeBtn);
    layH_samePrizeBtn->addStretch();
    layV_samePrizeAnalysis->addWidget(samePrizeText);
    layV_samePrizeAnalysis->addLayout(layH_samePrizeCmnBtn);
    layH_samePrizeCmnBtn->addWidget(samePrizeCmnBtn);
    layH_samePrizeCmnBtn->addStretch();
    layV_samePrizeAnalysis->addWidget(samePrizeCmnText);
    tabWidget->addTab(samePrizeAnalysis, QString("重边号相同项"));

    ///对比页面
    //创建对象
    comparePage = new QWidget(tabWidget);
    layV_comparePage = new QVBoxLayout(comparePage);
    layH_table = new QHBoxLayout();
    leftTable = new QTextEdit(comparePage);
    rightTable = new QTextEdit(comparePage);
    layH_compare = new QHBoxLayout();
    layV_compare_condition = new QVBoxLayout();
    layV_compare = new QVBoxLayout();
    layH_compare_condition_btn = new QHBoxLayout();
    compareBtn_condition = new QPushButton(tr(" 对比(限定次数) "),comparePage);
    layH_compare_btn = new QHBoxLayout();
    compareBtn = new QPushButton(tr("对比"),comparePage);
    compare_text = new QTextEdit(comparePage);
    compare_condition_text = new QTextEdit(comparePage);
    condition_spin = new QSpinBox(comparePage);
    copy_condition = new QPushButton(tr("复制"),comparePage);
    copy = new QPushButton(tr("复制"),comparePage);
    checkoutBtn = new QPushButton(tr("验证"),comparePage);

    //布局
    layV_comparePage->addLayout(layH_table);
    layH_table->addWidget(leftTable);
    layH_table->addWidget(rightTable);
    layV_comparePage->addLayout(layH_compare);
    layH_compare->addLayout(layV_compare_condition);
    layH_compare->addLayout(layV_compare);
    layV_compare_condition->addLayout(layH_compare_condition_btn);
    layV_compare->addLayout(layH_compare_btn);
    layH_compare_condition_btn->addWidget(compareBtn_condition);
    layH_compare_condition_btn->addWidget(condition_spin);
    layH_compare_condition_btn->addStretch();
    layH_compare_btn->addWidget(compareBtn);
    layH_compare_btn->addStretch();
    layV_compare->addWidget(compare_text);
    layV_compare_condition->addWidget(compare_condition_text);
    layH_compare_condition_btn->addWidget(copy_condition);
    layH_compare_btn->addWidget(copy);
    layV_comparePage->addWidget(checkoutBtn);
    tabWidget->addTab(comparePage, QString("对比"));

    //设置样式表
    comparePage->setStyleSheet(comparePageButtonStyle);









}
