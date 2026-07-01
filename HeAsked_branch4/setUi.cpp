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
//    searchBtn = new QPushButton(widget);
//    searchMenu = new QMenu(widget);
//    repeatSearchBtn = new QAction(widget);
//    neighborSearchBtn = new QAction(widget);
//    mixSearchBtn = new QAction(widget);
//    searchBtn->setText(" 标记 ");
//    repeatSearchBtn = searchMenu->addAction(QIcon(QPixmap::fromImage(im_greenCircle())),tr("重号查询"));
//    neighborSearchBtn = searchMenu->addAction(QIcon(QPixmap::fromImage(im_redCircle())),tr("邻号查询"));
//    mixSearchBtn = searchMenu->addAction(QIcon(QPixmap::fromImage(im_MixCircle())),tr("混合查询"));
//    searchBtn->setMenu(searchMenu);
//    searchMenu->setFont(aliFont);

    repeatSearchBtn = new QPushButton(tr("重号查询"),widget);
    neighborSearchBtn = new QPushButton(tr("邻号查询"),widget);
    mixSearchBtn = new QPushButton(tr("混合查询"),widget);



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
    layH_prztb_multiFuncBtns->addWidget(clearBtn);
    layH_prztb_multiFuncBtns->addWidget(deleteBtn);
    layH_prztb_multiFuncBtns->addWidget(changeViewPortBtn);
    layH_prztb_multiFuncBtns->addWidget(repeatSearchBtn);
    layH_prztb_multiFuncBtns->addWidget(neighborSearchBtn);
    layH_prztb_multiFuncBtns->addWidget(mixSearchBtn);
    layH_prztb_multiFuncBtns->addStretch();
//    layH_prztb_multiFuncBtns->addWidget(repeatMode);
//    layH_prztb_multiFuncBtns->addWidget(neighborMode);
//    layH_prztb_multiFuncBtns->addWidget(mixMode);
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
    includeBtn = new QPushButton(tr("反选剔除"),this);
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
    layH_randomSelect->addWidget(includeBtn);
    layH_randomSelect->addStretch();
    layV_page1->addLayout(layH_randomSelect);

    //lineEdit中的文本发生变化，发送信号给lcdNumber，使其计数改变
    connect(excludeEdtline,&NumLineEdit::textChanged,this,[=](){
        if(excludeEdtline->text().isEmpty())
            lcdNumber_exclude->display(0);
        else{
            //QStringList strList = samePrizeLineEdit->text().trimmed().split(" ");
            lcdNumber_exclude->display(excludeEdtline->text().trimmed().split(" ").length());
        }
    });


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
    repeatMode->setChecked(true);

    //下表的清除和划掉功能
    layH_strike_clear = new QHBoxLayout();
    clearAllDateBtn_downTbv = new QPushButton(tr("全部清除"),widget);
    clearSelectedRowBtn_downTbv = new QPushButton(tr("清除选中行"),widget);
    strikeItemBtn_downTbv = new QPushButton(tr("划掉一项"),widget);
    //strikeSameItemBtn_downTbv = new QPushButton(tr("划掉相同项"),widget);
    clearHighLight_downTbv = new QPushButton(tr("清除高亮"),widget);
    newestRepeatPrize = new QPushButton(tr("最新重号"),widget);
    copyUnDeletePrize = new QPushButton(tr("复制未划掉号码"),widget);
    btn_sortTableElementsByCount = new QPushButton(tr("表格排序"),widget);
    layH_strike_clear->addWidget(clearAllDateBtn_downTbv);
    layH_strike_clear->addWidget(clearSelectedRowBtn_downTbv);
    layH_strike_clear->addWidget(strikeItemBtn_downTbv);
    //layH_strike_clear->addWidget(strikeSameItemBtn_downTbv);
    layH_strike_clear->addWidget(clearHighLight_downTbv);
    layH_strike_clear->addWidget(newestRepeatPrize);
    layH_strike_clear->addWidget(copyUnDeletePrize);
    layH_strike_clear->addWidget(repeatMode);
    layH_strike_clear->addWidget(neighborMode);
    layH_strike_clear->addWidget(mixMode);
    layH_strike_clear->addStretch();
    layH_strike_clear->addWidget(btn_sortTableElementsByCount);
    layV_page1->addLayout(layH_strike_clear);

    //表格排序
    //btn_sortTableElementsByCount = new QPushButton(tr("表格排序"),widget);
    //layH_strike_clear->addWidget(btn_sortTableElementsByCount);


    layH_page2 = new QHBoxLayout(pgTbw);
    dataTable = new QTableWidget(pgTbw);
    tabWidget = new QTabWidget(pgTbw);
    layH_page2->addWidget(dataTable);
    layH_page2->addWidget(tabWidget);
    tabWidget->setStyleSheet(tabWidgetQss);
    initTableWidget(dataTable);


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
    leftTable = new QPlainTextEdit(comparePage);
    leftTable->setWordWrapMode(QTextOption::NoWrap);
    rightTable = new QPlainTextEdit(comparePage);
    rightTable->setWordWrapMode(QTextOption::NoWrap);
    layH_compare = new QHBoxLayout();
    layV_compare_condition = new QVBoxLayout();
    layV_compare = new QVBoxLayout();
    layH_compare_condition_btn = new QHBoxLayout();
    compareBtn_condition = new QPushButton(tr(" 对比(限定元素个数) "),comparePage);
    layH_compare_btn = new QHBoxLayout();
//    compareBtn = new QPushButton(tr("对比"),comparePage);
    compare_text = new QTextEdit(comparePage);
    compare_text->setWordWrapMode(QTextOption::NoWrap);
    compare_text->setReadOnly(true);
    compare_condition_text = new QTextEdit(comparePage);
    compare_condition_text->setWordWrapMode(QTextOption::NoWrap);
    compare_condition_text->setReadOnly(true);
    condition_spin = new QSpinBox(comparePage);
    copy_condition = new QPushButton(tr("复制"),comparePage);
    copy = new QPushButton(tr("复制"),comparePage);
    checkoutBtn = new QPushButton(tr("验证"),comparePage);
    compareProgressBar = new QProgressBar(comparePage); //进度条
    twoStepVerificationBtn = new QPushButton(tr("二次对比"),comparePage);


    //布局
    layV_comparePage->addLayout(layH_table);
    layH_table->addWidget(leftTable);
    layH_table->addWidget(rightTable);
    layV_comparePage->addWidget(compareProgressBar);
    layV_comparePage->addLayout(layH_compare);
    layH_compare->addLayout(layV_compare_condition);
    layH_compare->addLayout(layV_compare);

    layV_compare_condition->addLayout(layH_compare_condition_btn);
    layV_compare->addLayout(layH_compare_btn);
    layH_compare_condition_btn->addWidget(compareBtn_condition);
    layH_compare_condition_btn->addWidget(condition_spin);
    layH_compare_condition_btn->addStretch();
//    layH_compare_btn->addWidget(compareBtn);
    layH_compare_btn->addStretch();
    layV_compare->addWidget(compare_text);
    layV_compare_condition->addWidget(compare_condition_text);
    layH_compare_condition_btn->addWidget(copy_condition);
    layH_compare_condition_btn->addWidget(twoStepVerificationBtn);
    layH_compare_btn->addWidget(copy);
    layV_comparePage->addWidget(checkoutBtn);
    tabWidget->addTab(comparePage, QString("对比"));

    //设置样式表
    comparePage->setStyleSheet(comparePageButtonStyle);
    compareProgressBar->setStyleSheet(progressBarQss);


    ///自选组合

    //创建对象
    selfSelectCombine = new QWidget(tabWidget);
    layV_selfSelectCombine = new QVBoxLayout(selfSelectCombine);
    layH_copy_selfSelectCombine = new QHBoxLayout(selfSelectCombine);
    //左侧复制数据
    layV_copy_L_selfSelectCombine = new QVBoxLayout(selfSelectCombine);
    layH_copyBtn_L_selfSelectCombine = new QHBoxLayout(selfSelectCombine);
    copyBtn_L_selfSelectCombine =  new QPushButton("复制",selfSelectCombine);
    spinBox_L_selfSelectCombine = new QSpinBox(selfSelectCombine);
    text_copy_L_selfSelectCombine = new QPlainTextEdit(selfSelectCombine);
    //设置只读
    //text_copy_L_selfSelectCombine->setReadOnly(true);

    //右侧复制数据
    layV_copy_R_selfSelectCombine = new QVBoxLayout(selfSelectCombine);
    layH_copyBtn_R_selfSelectCombine = new QHBoxLayout(selfSelectCombine);
    copyBtn_R_selfSelectCombine =  new QPushButton("复制",selfSelectCombine);
    spinBox_R_selfSelectCombine = new QSpinBox(selfSelectCombine);
    text_copy_R_selfSelectCombine = new QPlainTextEdit(selfSelectCombine);
    //设置只读
    //text_copy_R_selfSelectCombine->setReadOnly(true);
    //复制数据部分
    layV_combine_selfSelectCombine = new QVBoxLayout(selfSelectCombine);
    //组合部分
    layH_combineBtn_selfSelectCombine = new QHBoxLayout(selfSelectCombine);
    combine_btn = new QPushButton("组合",selfSelectCombine);
    filter_btn = new QPushButton("筛选",selfSelectCombine);
    filter_spinBox = new QSpinBox(selfSelectCombine);
    layH_combineBtn_selfSelectCombine->addWidget(combine_btn);
    layH_combineBtn_selfSelectCombine->addWidget(filter_btn);
    layH_combineBtn_selfSelectCombine->addWidget(filter_spinBox);
    layH_combineBtn_selfSelectCombine->addStretch();
    combine_Res = new QPlainTextEdit(selfSelectCombine);
    combine_Res->setReadOnly(true);

    //布局
    layV_selfSelectCombine->addLayout(layH_copy_selfSelectCombine);
    layH_copy_selfSelectCombine->addLayout(layV_copy_L_selfSelectCombine);
    //左侧复制数据
    layV_copy_L_selfSelectCombine->addLayout(layH_copyBtn_L_selfSelectCombine);
    layH_copyBtn_L_selfSelectCombine->addWidget(copyBtn_L_selfSelectCombine);
    layH_copyBtn_L_selfSelectCombine->addWidget(spinBox_L_selfSelectCombine);
    layH_copyBtn_L_selfSelectCombine->addStretch();
    layV_copy_L_selfSelectCombine->addWidget(text_copy_L_selfSelectCombine);
    layH_copy_selfSelectCombine->addLayout(layV_copy_L_selfSelectCombine);
    //右侧复制数据
    layV_copy_R_selfSelectCombine->addLayout(layH_copyBtn_R_selfSelectCombine);
    layH_copyBtn_R_selfSelectCombine->addWidget(copyBtn_R_selfSelectCombine);
    layH_copyBtn_R_selfSelectCombine->addWidget(spinBox_R_selfSelectCombine);
    layH_copyBtn_R_selfSelectCombine->addStretch();
    layV_copy_R_selfSelectCombine->addWidget(text_copy_R_selfSelectCombine);
    layH_copy_selfSelectCombine->addLayout(layV_copy_R_selfSelectCombine);
    //复制数据部分
    layV_selfSelectCombine->addLayout(layV_combine_selfSelectCombine);
    //组合部分
    layV_selfSelectCombine->addLayout(layH_combineBtn_selfSelectCombine);
    layV_selfSelectCombine->addWidget(combine_Res);

    tabWidget->addTab(selfSelectCombine, QString("自选组合"));

    ///数字华容道(随机乱序)
    // 创建对象
    randomshuffling = new QWidget(tabWidget);
    vlay_randomshuffling = new QVBoxLayout(randomshuffling);
    hlay_getInfo_randomshuffling = new QHBoxLayout(randomshuffling);
    getInfo_randomshuffling = new QPushButton("获取信息",randomshuffling);
    hlay_shufflingitem_randomshuffling = new QHBoxLayout(randomshuffling);
    getInfo_selectedRows = new QPushButton("获取选中行");
    btn_moveSelectedLeft_randomshuffling = new QPushButton("选中项目靠边");
    shufflingitem_btn_mark = new QPushButton("标记",randomshuffling);
    shufflingitem_randomshuffling = new QPushButton("乱序",randomshuffling);
    inputEdt_randomshuffling =  new NumLineEdit(randomshuffling);
    spinbox_randomshuffling = new QSpinBox(randomshuffling);
    spinbox_randomshuffling->setRange(0, 1000); // 设置范围
    btn_columnsSwap = new QPushButton("列交换",randomshuffling);
    dataTable_randomshuffling = new TableWithCopy(randomshuffling);
    btn_export_list = new QPushButton("导出列表",randomshuffling);

    //布局
    vlay_randomshuffling->addWidget(shufflingitem_randomshuffling);
    vlay_randomshuffling->addLayout(hlay_getInfo_randomshuffling);
    hlay_getInfo_randomshuffling->addWidget(spinbox_randomshuffling);
    hlay_getInfo_randomshuffling->addWidget(getInfo_randomshuffling);
    vlay_randomshuffling->addLayout(hlay_shufflingitem_randomshuffling);
    vlay_randomshuffling->addWidget(getInfo_selectedRows);
    vlay_randomshuffling->addWidget(btn_moveSelectedLeft_randomshuffling);
    hlay_shufflingitem_randomshuffling->addWidget(inputEdt_randomshuffling);
    hlay_shufflingitem_randomshuffling->addWidget(shufflingitem_btn_mark);
    vlay_randomshuffling->addWidget(shufflingitem_randomshuffling);
    vlay_randomshuffling->addWidget(btn_columnsSwap);
    vlay_randomshuffling->addWidget(dataTable_randomshuffling);
    vlay_randomshuffling->addWidget(btn_export_list);
    initTableWidget(dataTable_randomshuffling);

    tabWidget->addTab(randomshuffling, QString("数字华容道"));

    //剔除页面
    tab_NumberExclusion = new QWidget(tabWidget);
    vlay_tab_NumberExclusion = new QVBoxLayout(tab_NumberExclusion);
    hlay1_tab_NumberExclusion = new QHBoxLayout(tab_NumberExclusion);
    hlay2_tab_NumberExclusion = new QHBoxLayout(tab_NumberExclusion);
    hlay3_tab_NumberExclusion = new QHBoxLayout(tab_NumberExclusion);
    tab_NumberExclusion_func_numberExclusion = new QPushButton("剔除",tab_NumberExclusion);
    tab_NumberExclusion_copy = new QPushButton("复制",tab_NumberExclusion);
    tab_NumberExclusion_btn_filter = new QPushButton("筛选",tab_NumberExclusion);
    tab_NumberExclusion_spinbox_filter = new QSpinBox(tab_NumberExclusion);
    tab_NumberExclusion_plainText_originNumbers = new QPlainTextEdit(tab_NumberExclusion);
    tab_NumberExclusion_plainText_numbersToBeExcluded = new QPlainTextEdit(tab_NumberExclusion);
    tab_NumberExclusion_plainText_res = new QPlainTextEdit(tab_NumberExclusion);
    tab_NumberExclusion_plainText_res->setReadOnly(true);

    //布局
    vlay_tab_NumberExclusion->addLayout(hlay1_tab_NumberExclusion);
    vlay_tab_NumberExclusion->addLayout(hlay2_tab_NumberExclusion);
    vlay_tab_NumberExclusion->addLayout(hlay3_tab_NumberExclusion);
    hlay1_tab_NumberExclusion->addWidget(tab_NumberExclusion_plainText_originNumbers);
    hlay1_tab_NumberExclusion->addWidget(tab_NumberExclusion_plainText_numbersToBeExcluded);
    hlay2_tab_NumberExclusion->addWidget(tab_NumberExclusion_func_numberExclusion);
    hlay2_tab_NumberExclusion->addStretch();
    hlay2_tab_NumberExclusion->addWidget(tab_NumberExclusion_btn_filter);
    hlay2_tab_NumberExclusion->addWidget(tab_NumberExclusion_spinbox_filter);
    hlay2_tab_NumberExclusion->addStretch();
    hlay2_tab_NumberExclusion->addWidget(tab_NumberExclusion_copy);
    hlay3_tab_NumberExclusion->addWidget(tab_NumberExclusion_plainText_res);

    tabWidget->addTab(tab_NumberExclusion, QString("剔除"));












}
