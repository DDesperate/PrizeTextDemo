#include "widget.h"
#include <QHeaderView>
#include "importDialog/importDialog.h"
#include "qss.h"
#include <QMap>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setUi(this);


    ///tableWidget页面相关操作
    initTableWidget(dataTable);

    //设置整体样式表
    this->setStyleSheet(buttonStyle+lineEdtStyle+spinBoxStyle+lcdStyle);

    //tableView双击上表选中一行，该行变红
    connect(upTbv,&QTableView::doubleClicked,[=](QModelIndex const &Index){
        upTbv->dbClkDate(Index);
    });

    //przTbv发送一行数据给inputEdt
    connect(upTbv,&UpTableView::insertToInputEdt,[=](const QList<quint8> prizes){
        inputEdt->setListIn(prizes);
    });

    //przTbv发送一行数据给excludeEdtline
    connect(upTbv,&UpTableView::insertToInputEdt,[=](const QList<quint8> prizes){
        excludeEdtline->setListIn(prizes);
    });

    //上表选中一行,下表该行被插入
    connect(upTbv, &UpTableView::insertToDownTbv,[=](QString date, QList<quint8> prizes){
        downTbv->insertRow(date,prizes);
    });

    //取消上表选中，下表对应数据删除一行
    connect(upTbv,&UpTableView::cancelInsert,[=](QString date){
        downTbv->deleteOneRow_passive(date);
    });


    //导入数据:
    connect(importTxt,&QAction::triggered,[=]{
        //txt中数据转成stringList
        QStringList data = fileToStrList();

        //tableView
        if(stackedWidget->currentIndex() == 0){
            //导入前先清空下表对应的数据结构
            downTbv->clearAllDate();
            upTbv->import(data);
        }

        //tableWidget
        if(stackedWidget->currentIndex() == 1){
            import(data);
            initBackGround();
        }

    });

    //弹出"插入一行"窗口
    connect(importOneRow,&QAction::triggered,this,[=]{
            importDialog->exec();
    });

    //根据当前所在的页面，决定将数据插入哪张表
    connect(importDialog,&ImportDialog::sendData,this,[=](const QString& date,const QList<quint8>& prizes){
        if(stackedWidget->currentIndex() == 0){

            int r = upTbv->insertOneRow(date,prizes);

            if(r == 1)
            {
                QMessageBox::warning(nullptr,tr("成功"),tr("插入成功"));
                upTbv->viewport()->update();
                importDialog->hide();
            }else if(r == 0){
                QMessageBox::warning(nullptr,tr("成功"),tr("覆盖成功"));
                upTbv->viewport()->update();
                importDialog->hide();
            }else{

            }
        }
        else{
            int r = insertLineData(date,prizes);
            if(r == 1)
            {
                QMessageBox::warning(nullptr,tr("成功"),tr("插入成功"));
                upTbv->viewport()->update();
                importDialog->hide();
            }else if(r == 0){
                QMessageBox::warning(nullptr,tr("成功"),tr("覆盖成功"));
                upTbv->viewport()->update();
                importDialog->hide();
            }else{

            }
            initBackGround();
            dataTable->sortByColumn(0,Qt::DescendingOrder);//按照第0列的规则，倒序排列
        }
    });


    //重号查询:
    connect(repeatSearchBtn,&QAction::triggered,[=]{
        inputEdt->fmtNum();
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->searchRepeat(inputEdt->strToList(),analysisNumSpinBox->value());
            upTbv->viewport()->update();
        }

        if(stackedWidget->currentIndex() == 1){
            //清除高亮
            initBackGround();
            searchRepeat();
        }

    });

    //邻号查询:
    connect(neighborSearchBtn,&QAction::triggered,[=]{
        inputEdt->fmtNum();
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->searchNeighbor(inputEdt->strToList(),analysisNumSpinBox->value());
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            //清除高亮
            initBackGround();
            searchNeighbor();
        }
    });

    //混合查询:
    connect(mixSearchBtn,&QAction::triggered,[=]{
        inputEdt->fmtNum();
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->searchMix(inputEdt->strToList(),analysisNumSpinBox->value());
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            //清除高亮
            initBackGround();
            searchMix();
        }
    });

    //清除高亮:
    connect(clearSearchBtn,&QAction::triggered,[=]{
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            initBackGround();
        }
    });

    //清除选中行高亮
    connect(clearRowBtn,&QAction::triggered,[=]{
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSelectedRowHighLight();
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            //
        }
    });

    //删除上表选中行数据
    connect(deleteBtn,&QPushButton::clicked,[=]{
        if(stackedWidget->currentIndex() == 0){
              upTbv->deleteSelectedRow();
//            //samePrizeLineEdit->clear();
//            //selfSelectedPrizeLineEdit->clear();
//            przTbv->viewport()->update();

        }
        if(stackedWidget->currentIndex() == 1){
            //获取被选取的行号
            QList<int> selectList = requestRowId();
            qDebug() << "selectList" << selectList;

            //将selectList从大到小排序，然后依次删除(因为每次删除一行后，后面的行会向上移动)
            std::sort(selectList.begin(), selectList.end(), std::greater<int>());
            for (int i = 0; i < selectList.count(); ++i) {
                int rowIndex = selectList.at(i);
                dataTable->removeRow(rowIndex);
            }
        }
    });


    //切换视图
    connect(changeViewPortBtn, &QPushButton::clicked, stackedWidget,[=]{
        if(stackedWidget->currentIndex() == 0)
        {
            //把dataMap转换成QStringList，导入另外一张表

            import(upTbv->turnDataToStringList());

            dataTable->sortByColumn(0,Qt::DescendingOrder);//按照第0列的规则，倒序排列

            initBackGround();

            //

            stackedWidget->setStartValue(0);
            stackedWidget->setEndValue(180);
            stackedWidget->animation(0,1);
//                        stackedWidget->setCurrentIndex(1);
//                        stackedWidget->repaint();
        }
        else if(stackedWidget->currentIndex() == 1)
        {
            stackedWidget->setStartValue(0);
            stackedWidget->setEndValue(-180);
            stackedWidget->animation(1,0);

            QStringList strList = turnTableWidgetDataToStrList();
            qDebug() << strList;
            upTbv->import(strList);
//                        stackedWidget->setCurrentIndex(0);
//                        stackedWidget->repaint();
        }
    });


    //获取下表中的相同项，发送数据给samePrizeLineEdit
    connect(downTbv, &DownTableView::sendSamePrizeList,[=](QList<quint8> prizeList){
        samePrizeLineEdit->setListIn(prizeList);});

    //随机从上表选n行到下表
    connect(okBtn_randomSelectRows,&QPushButton::clicked,[=]{

        //获取spinBox和当前上表行数中的较小值
        int rowCount = upTbv->przModel.rowCount();
        int num = spinBox_randomSelectRows->value()<rowCount?spinBox_randomSelectRows->value():rowCount;
        spinBox_randomSelectRows->setValue(num);

        //每次重新随机之前,上表中被选中的高亮清除，下表数据清除
        upTbv->clearSelectedRowHighLight();

        //随机获取上表n
        upTbv->getRandomMap(num);
    });

    ///功能:随机从下表的每一行中选取n个数字----功能开始
    //计时器
    randomSelectTimer = new QTimer();
    randomSelectTimer->setInterval(500);
    QObject::connect(randomSelectTimer, &QTimer::timeout, [&]() {
            downTbv->randomSelectPrizes(randomSelectSpinBox1->value());
        });

    //开始随机
    connect(randomSelectStart,&QPushButton::clicked,[=]{
        randomSelectTimer->start();
    });

    //停止随机
    connect(randomSelectEnd,&QPushButton::clicked,[=]{
        randomSelectTimer->stop();

        //获取每一个行被标记的奖注，放到一个数据结构中
        QList<QList<quint8>> list =  downTbv->getSelectedPrize();

        //先判断有没有数据需要显示
        randomSelectListWgt = new RandomSelectListWidget(this,list);
        //randomSelectResWgt->setWindowFlags(Qt::Window);
        randomSelectListWgt->show();
    });
    ///功能:随机从下表的每一行中选取n个数字----功能开始

    ///功能:从表中划掉excludeEdtline中的项
    connect(excludeBtn,&QPushButton::clicked,[=]{
        downTbv->exclude(excludeEdtline->strToList());
    });
    ///功能:剔除lineEdit中的项----功能结束


    //下表清除一行，上表响应的行取消标记
    connect(downTbv,&DownTableView::deleteOneRow,[&](const QString &date){
        upTbv->unMarkOneRow(date);
    });

    //随机删除
    connect(deleteBtn_randomDeleteOneRow,&QPushButton::clicked,this,[=]{
        downTbv->randomClearOneRow();
    });

    //tableView双击下表选中一行，该行变红
    connect(downTbv,&QTableView::doubleClicked,[=](QModelIndex const &Index){
        downTbv->dbClkDate(Index);
    });

    //下表数据全部清除，上表高亮全部清除
    connect(clearAllDateBtn_downTbv,&QPushButton::clicked,[=]{
        upTbv->clearSelectedRowHighLight();
        downTbv->clearAllDate();
    });

    //下表中的选中行清除，对应上表中的数据清除选中高亮
    connect(clearSelectedRowBtn_downTbv,&QPushButton::clicked,[=]{
        downTbv->deleteSelectedRow();
    });

    //划掉选中项
    connect(strikeItemBtn_downTbv,&QPushButton::clicked,[=]{
        downTbv->strikeItem();
    });

    //划掉多行数据中相同的项
    connect(strikeSameItemBtn_downTbv,&QPushButton::clicked,[=]{
        downTbv->strikeSameItem();
    });

    //清除下表中的高亮
    connect(clearHighLight_downTbv,&QPushButton::clicked,[=]{
        downTbv->clearHighLight();
        samePrizeLineEdit->clear();
    });

    ///tbw相关
    //双击弹出该行奖注
    connect(dataTable->verticalHeader(),&QHeaderView::sectionDoubleClicked,this,[=](){
        copyRow(dataTable,inputEdt,winNumLineEdit,cmnLineEdt);
    });

    //重号分析
    connect(repeatAnalysisBtn,&QPushButton::clicked,this,[=]{
        repeatAnalysis(dataTable,inputEdt,repeatAnalysisText);
    });

    //边号分析
    connect(neighborAnalysisBtn,&QPushButton::clicked,this,[=]{
        neighborAnalysis(dataTable,inputEdt,neighborAnalysisText);
    });


    //混合分析
    connect(mixAnalysisBtn,&QPushButton::clicked,this,[=]{
        mixAnalysis(dataTable,inputEdt,mixAnalysisText);
    });

    //排列组合
    connect(cmnBtn,&QPushButton::clicked,this,[=]{
        cmnAnalysis(cmnLineEdt, cmnText);
    });


    //模拟开奖
    connect(startTestBtn,&QPushButton::clicked,this,[=]{
        SimulatedLottery(winNumLineEdit,selectNumLineEdit,detailText);
    });

    //详情按钮
    connect(detailInfoBtn,&QPushButton::clicked,this,[=]{
        SimulateLotteryTable();
    });


    //获取相同项
    connect(getSamePrizeBtn,&QPushButton::clicked,this,[=]{
        getTbwSamePrize(dataTable);
    });

    //相同项排列组合
    connect(samePrizeCmnBtn,&QPushButton::clicked,this,[=]{
        samePrizeCmn();
    });

    //比较Tab
    connect(compareBtn_condition,&QPushButton::clicked,this,[=]{

        //每次比较都需要清空上一次的数据
        //为什么res_samePrizes不在connect中定义？
        //因为checkoutWgt需要获取到数据res_samePrizes
        res_samePrizes.clear();

        QVector<QList<quint8>> left = textToDataStructure(leftTable->toPlainText());
        qDebug() << "left" << left;
        QVector<QList<quint8>> right = textToDataStructure(rightTable->toPlainText());
        qDebug() << "right" << right;

        //左表遍历

        //左表计数(行数)
        int leftCount = 0;
        for(const QList<quint8> &leftRow:left){
            leftCount++;
            //右表遍历

            //右表计数(行数)
            int rightCount = 0;
            for(const QList<quint8> &rightRow:right){
                rightCount++;

                //如果左表某一行和右表某一行有相同的值
                if(!getCommonItems(leftRow,rightRow).isEmpty()){

                    //打印相同的值
                    //qDebug() << getCommonItems(leftRow,rightRow);

                    //如果结果中已经有这一行，次数+1
                    if(res_samePrizes.contains(getCommonItems(leftRow,rightRow))){

                        //map:res当中key值为getCommonItems(leftRow,rightRow)的value++
                        res_samePrizes[getCommonItems(leftRow,rightRow)].first++;

                        //打印次数
                        //qDebug() << res[getCommonItems(leftRow,rightRow)];

                        res_samePrizes[getCommonItems(leftRow,rightRow)].second +="左" + QString::number(leftCount) + ":" + prizeListToString(leftRow) + " " + "右" + QString::number(rightCount) + ":" + prizeListToString(rightRow) + "\n";

                    }
                    else{
                        QString str = "左" + QString::number(leftCount) + ":" + prizeListToString(leftRow) + " " + "右" + QString::number(rightCount) + ":" + prizeListToString(rightRow) + "\n";
                        QPair<int,QString> pair(1,str);
                        res_samePrizes.insert(getCommonItems(leftRow,rightRow),pair);
                    }
                }
            }
        }
        qDebug() << res_samePrizes;
        compare_condition_text->setText(dataStructureToText(res_samePrizes,condition_spin->value(),true));
        compare_text->setText(dataStructureToText(res_samePrizes,0,false));

        if(checkoutWgt){
            checkoutWgt->clearAll();
            checkoutWgt->getDate(res_samePrizes);
        }
    });

    connect(checkoutBtn,&QPushButton::clicked,[=]{
        if(checkoutWgt != nullptr){
            checkoutWgt->show();
            checkoutWgt->raise();
        }
        else{
            checkoutWgt = new CheckoutWgt(comparePage);
            checkoutWgt->getDate(res_samePrizes);
            checkoutWgt->setAttribute(Qt::WA_DeleteOnClose);
            checkoutWgt->show();
        }
    });




}

Widget::~Widget()
{
    delete simulateLotteryDlg;
}

