#include "widget.h"
#include <QHeaderView>
#include "importDialog/importDialog.h"
#include "qss.h"
#include "genericfunc.h"
#include <QMap>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    setUi(this);

    this->update();

    //是否可以在点击按钮时启动线程，工作结束后终止线程？
    compareThread.moveToThread(&thread);
    thread.start();


    ///tableWidget页面相关操作

    //设置整体样式表
    this->setStyleSheet(buttonStyle+lineEdtStyle+spinBoxStyle+lcdStyle);

    //使得右键dataTable可以弹出菜单的前置条件
    dataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(dataTable,&QTableWidget::customContextMenuRequested,this,&Widget::showContextMenu);

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

    //切换模式
    connect(modeGroup,SIGNAL(buttonClicked(int)),this,SLOT(handleModeChange(int)));

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
            initBackGround(dataTable);
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
            initBackGround(dataTable);
            dataTable->sortByColumn(0,Qt::DescendingOrder);//按照第0列的规则，倒序排列
        }
    });


    //重号查询:
    connect(repeatSearchBtn,&QPushButton::clicked,[=]{
        inputEdt->fmtNum();
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->searchRepeat(inputEdt->strToList(),analysisNumSpinBox->value());
            upTbv->viewport()->update();
        }

        if(stackedWidget->currentIndex() == 1){
            //清除高亮
            initBackGround(dataTable);
            searchRepeat(dataTable);

            if(!randomshuffling->isHidden()){
                initBackGround(dataTable_randomshuffling);
                searchRepeat(dataTable_randomshuffling);
            }
        }

    });

    //邻号查询:
    connect(neighborSearchBtn,&QPushButton::clicked,[=]{
        inputEdt->fmtNum();
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->searchNeighbor(inputEdt->strToList(),analysisNumSpinBox->value());
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            //清除高亮
            initBackGround(dataTable);
            searchNeighbor(dataTable);
            if(!randomshuffling->isHidden()){
                initBackGround(dataTable_randomshuffling);
                searchNeighbor(dataTable_randomshuffling);
            }
        }
    });

    //混合查询:
    connect(mixSearchBtn,&QPushButton::clicked,[=]{
        inputEdt->fmtNum();
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->searchMix(inputEdt->strToList(),analysisNumSpinBox->value());
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            //清除高亮
            initBackGround(dataTable);
            searchMix(dataTable);
            if(!randomshuffling->isHidden()){
                initBackGround(dataTable_randomshuffling);
                searchMix(dataTable_randomshuffling);
            }
            QApplication::clipboard()->setText(mixAnalysis_data2Bcopy);
            QMessageBox::information(this, tr("复制成功"), tr("选中文本已复制到剪切板"));
        }
    });

    //清除高亮:
    connect(clearSearchBtn,&QAction::triggered,[=]{
        if(stackedWidget->currentIndex() == 0){
            upTbv->clearSearchHighLight();
            upTbv->viewport()->update();
        }
        if(stackedWidget->currentIndex() == 1){
            initBackGround(dataTable);
            if(!randomshuffling->isHidden())
                initBackGround(dataTable_randomshuffling);
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
            QList<int> selectList = getSelectedIndices(dataTable,false);
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
            if(!randomSelectStart->isEnabled()){
                randomSelectTimer->stop();
                randomSelectStart->setEnabled(true);
                randomSelectSpinBox1->setEnabled(true);
            }

            //把dataMap转换成QStringList，导入另外一张表

            import(upTbv->turnDataToStringList());

            dataTable->sortByColumn(0,Qt::DescendingOrder);//按照第0列的规则，倒序排列

            initBackGround(dataTable);

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

    //点击下表中的一项，该项跳到排除列表中
    connect(downTbv,SIGNAL(sendNum(int)),this,SLOT(addNumToExcludeList(int)));

    //获取下表中的相同项，发送数据给samePrizeLineEdit
    connect(downTbv, &DownTableView::sendSamePrizeList,[=](QList<quint8> prizeList){
        samePrizeLineEdit->setListIn(prizeList);});

    //随机从上表选n行到下表
    connect(okBtn_randomSelectRows,&QPushButton::clicked,[=]{

        if(spinBox_randomSelectRows->value() == 0)
            QMessageBox::warning(nullptr,"警告","请选择大于0行数字");
        else{
            //获取spinBox和当前上表行数中的较小值
            int rowCount = upTbv->przModel.rowCount();
            int num = spinBox_randomSelectRows->value()<rowCount?spinBox_randomSelectRows->value():rowCount;
            spinBox_randomSelectRows->setValue(num);

            //每次重新随机之前,上表中被选中的高亮清除，下表数据清除
            upTbv->clearSelectedRowHighLight();

            //随机获取上表n
            upTbv->getRandomMap(num);

        }

        // 同步downTbv数据到SortTableElementsByCountWgt
        if (sortTableElementsByCountWgt != nullptr) {
            sortTableElementsByCountWgt->updateData(downTbv->outputRepeatData(),
                                                      downTbv->outputNeighborData(),
                                                      downTbv->outputMixData());
        }

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
        if(randomSelectSpinBox1->value() == 0)
            QMessageBox::warning(nullptr,"警告","请选择大于0个数字");
        else{
            randomSelectTimer->start();
            randomSelectStart->setEnabled(false);
            randomSelectSpinBox1->setEnabled(false);
        }
    });

    //停止随机
    connect(randomSelectEnd,&QPushButton::clicked,[=]{
        randomSelectTimer->stop();
        randomSelectStart->setEnabled(true);
        randomSelectSpinBox1->setEnabled(true);

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
        excludeEdtline->fmtNum();
        downTbv->exclude(excludeEdtline->strToList());

    });
    ///功能:剔除lineEdit中的项----功能结束

    ///功能:反选剔除:从表中划掉除了excludeEdtline中以外的项
    connect(includeBtn,&QPushButton::clicked,[=]{
        excludeEdtline->fmtNum();
        downTbv->include(excludeEdtline->strToList());

    });
    ///功能:反选剔除：从表中划掉除了excludeEdtline中以外的项

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


    //清除下表中的高亮
    connect(clearHighLight_downTbv,&QPushButton::clicked,[=]{
        downTbv->clearHighLightAndDeleted();
        samePrizeLineEdit->clear();

    });

    //标记下表中最后一行的重号
    connect(newestRepeatPrize,&QPushButton::clicked,[=]{
        downTbv->clearHighLight();
        QList<quint8> list = upTbv->getLastRow();
        downTbv->selectListItem(list);
    });

    //复制未被划掉的号码
    connect(copyUnDeletePrize,&QPushButton::clicked,[=]{
        downTbv->copyUnDeleteNum();
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

    //双击tbw单元格
    //connect(ui->dataTableWidget_1,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(getItemValuePurple(QTableWidgetItem*)));
    connect(dataTable,SIGNAL(itemDoubleClicked(QTableWidgetItem*)),this,SLOT(getItemValuePurple(QTableWidgetItem*)));

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
        compareThread.res_samePrizes.clear();


        //获取左表和右表的值转成数据结构
        //如果数据正确返回值为1
        //数据为空，返回值为0
        //数据错误，返回值为-1
        QVector<QList<quint8>> left;
        QPair<int,QString> leftRes = textToDataStructure(left,leftTable->toPlainText());
        QVector<QList<quint8>> right;
        QPair<int,QString> rightRes = textToDataStructure(right,rightTable->toPlainText());

        if(leftRes.first == 0 || rightRes.first == 0)
        {
            QMessageBox::warning(nullptr,
                                 "警告",
                                 "输入为空");
        }

        if(leftRes.first == -1)
        {
            QMessageBox::warning(nullptr,
                                 "左表输入",
                                 leftRes.second + "\n");
        }
        if(rightRes.first == -1)
        {
            QMessageBox::warning(nullptr,
                                 "右表输入",
                                 rightRes.second + "\n");
        }


        if(leftRes.first == 1 && rightRes.first == 1)
        {
            emit sendInput(left,right);
        }


    });

    //连接两张表的输入值与计算线程中的计算函数
    qRegisterMetaType<QVector<QList<quint8>>>("QVector<QList<quint8>>");
    connect(this,SIGNAL(sendInput(const QVector<QList<quint8>>,const QVector<QList<quint8>>)),&compareThread,SLOT(calCompare(const QVector<QList<quint8>>,const QVector<QList<quint8>>)));

    //连接计算进度与进度条
    connect(&compareThread,SIGNAL(sendProgressSignal(int,int)),this,SLOT(recvProgressSlot(int,int)));

    //连接计算线程中计算出的结果与刷新前端界面出现结果
    qRegisterMetaType<QMap<QList<quint8>,QPair<int,QString>>>("QMap<QList<quint8>,QPair<int,QString>>");
    connect(&compareThread, &CompareThread::sendResult, this,[=](QMap<QList<quint8>,QPair<int,QString>> *res) {
        NewRes = res;
        compare_condition_text->setText(dataStructureToText_withCount(*NewRes,condition_spin->value(),true));
        compare_text->setText(dataStructureToText_withCount(*NewRes,0,false));
        //为了防止验证功能出错
        //当计算时如果验证窗口存在，那么清空其中的数据
        if(checkoutWgt){
            checkoutWgt->clearAll();
            checkoutWgt->getDate(compareThread.res_samePrizes);
        }
    });

    //弹出检查结果窗口
    connect(checkoutBtn,&QPushButton::clicked,[=]{
        if(checkoutWgt != nullptr){
            checkoutWgt->show();
            checkoutWgt->raise();
        }
        else{
            checkoutWgt = new CheckoutWgt(comparePage);
            checkoutWgt->getDate(compareThread.res_samePrizes);
            checkoutWgt->setAttribute(Qt::WA_DeleteOnClose);
            checkoutWgt->show();
        }
    });

    //复制不带计数(带条件)
    connect(copy_condition,&QPushButton::clicked,[=]{
        copy_onlyPrize(compare_condition_text->toPlainText()," 出现次数");
    });

    //复制
    connect(copy,&QPushButton::clicked,[=]{
        copy_onlyPrize(compare_text->toPlainText()," 出现次数");
    });

    //二次比较
    connect(twoStepVerificationBtn,&QPushButton::clicked,[=]{

        if(NewRes == nullptr){
            QMessageBox::warning(nullptr,tr("警告"),tr("请先进行一次比较"));
            return ;
        }

        if(twoStepVerificationWgt != nullptr){
            twoStepVerificationWgt->show();
            twoStepVerificationWgt->raise();
        }
        else{
            twoStepVerificationWgt = new TwoStepVerificationWgt(comparePage);
            twoStepVerificationWgt->getData(*NewRes);
            twoStepVerificationWgt->setAttribute(Qt::WA_DeleteOnClose);
            twoStepVerificationWgt->show();
        }


//        twoStepVerificationWgt->show();
    });

    //自选组合
    //左框复制
    connect(copyBtn_L_selfSelectCombine,&QPushButton::clicked,[=]{

        QString resultText;
        QVector<QList<quint8>> tmp_L_data = selectCombine(spinBox_L_selfSelectCombine->value());

        // 将结果设置为 QPlainTextEdit 的文本内容
        text_copy_L_selfSelectCombine->setPlainText(formatQVectorQListToString(tmp_L_data));
    });

    //右框复制
    connect(copyBtn_R_selfSelectCombine,&QPushButton::clicked,[=]{
        QString resultText;
        QVector<QList<quint8>> tmp_R_data = selectCombine(spinBox_R_selfSelectCombine->value());

        // 将结果设置为 QPlainTextEdit 的文本内容
        text_copy_R_selfSelectCombine->setPlainText(formatQVectorQListToString(tmp_R_data));
    });

    connect(combine_btn,&QPushButton::clicked,[=]{
        QVector<QList<quint8>> res;

        //parseStringToQVectorQList函数可以过滤掉文本中所有超出quint范围的字符，所以类似于xxxx-xxx的日期类字符可以被过滤，但是超出1-80的字符并不会被过滤掉
        //而且说过滤就过滤掉了，也不会说明到底是哪一行有问题
        QVector<QList<quint8>> tmp_L_data = parseStringToQVectorQList(text_copy_L_selfSelectCombine->toPlainText());
        QVector<QList<quint8>> tmp_R_data = parseStringToQVectorQList(text_copy_R_selfSelectCombine->toPlainText());

        QString resultText;
        for(const QList<quint8>& row_L : tmp_L_data)
        {
            for(const QList<quint8>& row_R : tmp_R_data)
            {
                QList<quint8> Union_list = getUnion(row_L,row_R);
                qSort(Union_list.begin(), Union_list.end());
                res.append(Union_list);
            }
        }

        res = removeDuplicates(res);

        //排序
        std::sort(res.begin(), res.end(), customSort);

        combine_res_data = res;



//        for (const QList<quint8>& row : res) {
//            for (quint8 value : row) {
//                resultText += QString::number(value).rightJustified(2,'0') + " ";
//            }
//            resultText += "\n";
//        }

        QString rowCount = "总行数:"+QString::number(res.size())+"\n";

        // 将结果设置为 QPlainTextEdit 的文本内容
        combine_Res->setPlainText(rowCount+formatQVectorQListToString(res));


    });

    connect(filter_btn,&QPushButton::clicked,[=]{
        int num = filter_spinBox->value();
        QVector<QList<quint8>> filtered;
        for(const QList<quint8>& row : combine_res_data)
        {
            if(row.size() == num)
                filtered.append(row);
        }

        if(filtered.isEmpty())
        {
            QMessageBox::warning(nullptr, tr("警告"), tr("没有符合的结果"));
            return;
        }

        QDialog *dlg = new QDialog(this);
        dlg->setWindowTitle(tr("筛选结果 — %1个元素").arg(num));
        QVBoxLayout *lay = new QVBoxLayout(dlg);
        QPlainTextEdit *pte = new QPlainTextEdit(dlg);
        pte->setReadOnly(true);
        QString rowCount = "总行数:" + QString::number(filtered.size()) + "\n";
        pte->setPlainText(rowCount + formatQVectorQListToString(filtered));
        lay->addWidget(pte);
        dlg->setLayout(lay);
        dlg->setAttribute(Qt::WA_DeleteOnClose);
        dlg->show();
    });

    //把左表dataTable中的数据前n行放到dataTable_randomshuffling当中
    connect(getInfo_randomshuffling,&QPushButton::clicked,[=]{
        clearData(dataTable_randomshuffling);

        //检验原表中是否有数据
        if (dataTable->rowCount() == 0 || dataTable->columnCount() == 0) {
            QMessageBox::warning(nullptr, tr("警告"), tr("表中无数据"));
        }
        int n = qMin(spinbox_randomshuffling->value(),dataTable->rowCount());

        // 遍历dataTable的前n行
        for (int row = 0; row < n; ++row) {
            // 在dataTable_randomshuffling中创建新行
            int newRow = dataTable_randomshuffling->rowCount();
            dataTable_randomshuffling->insertRow(newRow);

            // 遍历当前行的所有列
            for (int column = 0; column < dataTable->columnCount(); ++column) {
                // 复制每个单元格的数据到新表中
                QTableWidgetItem *item = dataTable->item(row, column);
                if (item) {
                    dataTable_randomshuffling->setItem(newRow, column, new QTableWidgetItem(item->text()));
                }
            }
        }

        initBackGround(dataTable_randomshuffling);

    });

    //把原表中被选中的行放到新表中
    connect(getInfo_selectedRows,&QPushButton::clicked,[=]{
        //清空新表
        clearData(dataTable_randomshuffling);

        //QString copiedText;
        QList<int> selectedRows = getSelectedIndices(dataTable,false);
        std::sort(selectedRows.begin(),selectedRows.end());

        //检验是否选中原表中的某些行
        if(selectedRows.isEmpty()){
            QMessageBox::warning(nullptr, tr("警告"), tr("未选中任何行"));
        }

        //用于设置旧表中的数据插入到新表中的哪一行
        int newRow = 0;

        // 遍历dataTable的前n行
        for(int row : selectedRows){

            insertEmptyRow(dataTable_randomshuffling);

            // 遍历当前行的所有列selectMode
            for (int column = 0; column <= 20; ++column) {
                // 复制每个单元格的数据到新表中
                QTableWidgetItem *item = dataTable->item(row, column);
                if (item) {
                    dataTable_randomshuffling->setItem(newRow, column, new QTableWidgetItem(item->text()));
                }
            }
            newRow ++;
//            //copiedText += rowData.join(" ") + "\n";  // 以" "分隔每个单元格，并换行分隔每行
        }
        // 将整个表格内容复制到剪贴板
        //QClipboard *clipboard = QApplication::clipboard();
        //clipboard->setText(copiedText);

          initBackGround(dataTable_randomshuffling);
    });

    //按钮-选中项目靠边（将绿色标记项左靠）
    connect(btn_moveSelectedLeft_randomshuffling, &QPushButton::clicked, [=]{
        const QColor selectedGreen(0, 255, 0);
        int rowCount = dataTable_randomshuffling->rowCount();
        int colCount = dataTable_randomshuffling->columnCount();
        if (rowCount == 0 || colCount <= 1) {
            return;
        }

        for (int row = 0; row < rowCount; ++row) {
            struct CellData {
                QString text;
                QColor bg;
            };

            QVector<CellData> greenCells;
            QVector<CellData> otherCells;

            for (int col = 1; col < colCount; ++col) {
                QTableWidgetItem *item = dataTable_randomshuffling->item(row, col);
                if (!item) {
                    continue;
                }

                const QString text = item->text().trimmed();
                if (text.isEmpty()) {
                    continue;
                }

                const QColor bg = item->background().color();
                if (bg == selectedGreen) {
                    greenCells.append({text, bg});
                } else {
                    otherCells.append({text, bg});
                }
            }

            QVector<CellData> merged = greenCells;
            merged += otherCells;

            for (int col = 1; col < colCount; ++col) {
                QTableWidgetItem *item = dataTable_randomshuffling->item(row, col);
                if (!item) {
                    item = new QTableWidgetItem();
                    dataTable_randomshuffling->setItem(row, col, item);
                }

                int idx = col - 1;
                if (idx < merged.size()) {
                    item->setText(merged[idx].text);
                    item->setBackground(merged[idx].bg);
                } else {
                    item->setText("");
                    item->setBackground(Qt::white);
                }
            }
        }
    });


    //按钮-乱序
    connect(shufflingitem_randomshuffling,&QPushButton::clicked,[=]{
        QVector<QString> dateList;
        QVector<QVector<quint8>> prize2DArray;

        //获取表中的数据，打乱顺序,获得一个日期列表和一个二维数组
        shufflingByCol(dateList,prize2DArray);

//        QVector<QString> issue_num;
//        QVector<QVector<quint8>> prize2DArray;
//        QList<quint8> fixedNum = inputEdt_randomshuffling->strToList();
//        shufflingByCol(spinbox_randomshuffling->value(),fixedNum,issue_num,prize2DArray);


        //清除表中的数据
        clearData(dataTable_randomshuffling);

        //将二维数组和日期列表组成的新表放到dataTable_randomshuffling中
        for (int row = 0; row < dateList.size(); ++row) {
            dataTable_randomshuffling->insertRow(row);
            QTableWidgetItem *item = new QTableWidgetItem(dateList[row]);
            dataTable_randomshuffling->setItem(row, 0, item); // 第一列填充期号

            for (int col = 0; col < prize2DArray[row].size(); ++col) {
                quint8 prize = prize2DArray[row][col];
                QTableWidgetItem *prizeItem = new QTableWidgetItem(QString::number(prize).rightJustified(2,'0'));
                dataTable_randomshuffling->setItem(row, col + 1, prizeItem); // 从第二列开始填充奖项
            }
        }

        //初始化表背景颜色
        initBackGround(dataTable_randomshuffling);


//        //清除上一次得表中数据

    });

    //标记列出的数字
    connect(shufflingitem_btn_mark,&QPushButton::clicked,[=]{
        QList<quint8> fixedNum = inputEdt_randomshuffling->strToList();
        //标记选出的数字
        markFixedNum(dataTable_randomshuffling,fixedNum);
    });

    //按钮-列交换
    connect(btn_columnsSwap,&QPushButton::clicked,[=]{
        QList<int> res = getSelectedIndices(dataTable_randomshuffling,true);

        //注意，第0列为日期，故提前把第0列移除
        //void shuffleSelectedColumns(QTableWidget *dataTable, const QList<int> &selectedColumns)
        //参数2为const修饰，不能在函数中改变selectedColumns
        res.removeAll(0);

        shuffleSelectedColumns(dataTable_randomshuffling,res);
    });

    //按钮-导出多列表
    //二次比较
    connect(btn_export_list,&QPushButton::clicked,[=]{

        if(multiListWgt != nullptr){
            multiListWgt->show();
            multiListWgt->raise();
        }
        else{
            multiListWgt = new MultiListWidget(randomshuffling);
            multiListWgt->getPointer_OriginTable(dataTable_randomshuffling);
            multiListWgt->setAttribute(Qt::WA_DeleteOnClose);
            multiListWgt->show();
        }


//        twoStepVerificationWgt->show();
    });


    //剔除指定元素
    connect(tab_NumberExclusion_func_numberExclusion,&QPushButton::clicked,[=]{
       QVector<QList<quint8>> dataStruct_originNum = parseStringToQVectorQList(tab_NumberExclusion_plainText_originNumbers->toPlainText());
       QVector<QList<quint8>> dataStruct_numToBeExcluded = parseStringToQVectorQList(tab_NumberExclusion_plainText_numbersToBeExcluded->toPlainText());
       tab_NumberExclusion_lastRes = excludeElements(dataStruct_originNum,dataStruct_numToBeExcluded);
       QString rowCount = QString::number(tab_NumberExclusion_lastRes.size());
       tab_NumberExclusion_plainText_res->setPlainText("总行数:" + rowCount + "\n" +formatQVectorQListToStringWithCounts(tab_NumberExclusion_lastRes));
    });

    //过滤元素为n的行(n为tab_NumberExclusion_spinbox_filter的value)
    connect(tab_NumberExclusion_btn_filter,&QPushButton::clicked,[=]{
        QVector<QList<quint8>> tab_NumberExclusion_lastRes_filtered;

        // 遍历原始数据结构
        for (const auto& list : tab_NumberExclusion_lastRes) {
            // 检查当前列表的元素个数是否为 n
            if (list.size() == tab_NumberExclusion_spinbox_filter->value()) {
                // 如果是，添加到过滤后的数据结构中
                tab_NumberExclusion_lastRes_filtered.append(list);
            }
        }

        QString rowCount = QString::number(tab_NumberExclusion_lastRes_filtered.size());
        tab_NumberExclusion_plainText_res->setPlainText("总行数:" + rowCount + "\n" +formatQVectorQListToStringWithCounts(tab_NumberExclusion_lastRes_filtered));
    });

    //
    connect(tab_NumberExclusion_copy,&QPushButton::clicked,[=]{
        //QClipboard *clipboard = QApplication::clipboard();
        //clipboard->setText(tab_NumberExclusion_plainText_res->toPlainText());
        QApplication::clipboard()->setText(tab_NumberExclusion_plainText_res->toPlainText());
        copy_onlyPrize(tab_NumberExclusion_plainText_res->toPlainText()," 元素个数");
    });


    //弹出表格排序窗口（窗口内点击按钮后，从 downTbv 拉取数据）
    connect(btn_sortTableElementsByCount,&QPushButton::clicked,[=]{

        //使新弹出的窗口与上表对齐
        QRect tbvAGlobalRect = upTbv->geometry();
        tbvAGlobalRect.moveTopLeft(upTbv->mapToGlobal(tbvAGlobalRect.topLeft()));

        //如果窗口指针不为空，则将窗口显示在最上方
        if (sortTableElementsByCountWgt!= nullptr) {
            // 如果窗口最小化了，恢复正常状态
            if (sortTableElementsByCountWgt->isMinimized()) {
                sortTableElementsByCountWgt->setWindowState(
                    (sortTableElementsByCountWgt->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
            }

            sortTableElementsByCountWgt->show();   // 显示窗口
            sortTableElementsByCountWgt->raise();  // 提到最前面
            sortTableElementsByCountWgt->activateWindow(); // 激活窗口（获得焦点）
        }
        //否则new这个窗口
        else{
            //参数1:父窗口
            //参数2:使新弹出的窗口与上表对齐
            sortTableElementsByCountWgt = new SortTableElementsByCountWgt(pgTbv,tbvAGlobalRect);
            connect(sortTableElementsByCountWgt, &SortTableElementsByCountWgt::requestDataSync, this, [=]{
                sortTableElementsByCountWgt->updateData(downTbv->outputRepeatData(),
                                                      downTbv->outputNeighborData(),
                                                      downTbv->outputMixData());
            });
            connect(sortTableElementsByCountWgt, &SortTableElementsByCountWgt::requestLatestRepeatPrize, this, [=]{
                QList<quint8> list = upTbv->getLastRow();
                sortTableElementsByCountWgt->markLatestRepeatPrize(list);
            });
            sortTableElementsByCountWgt->setAttribute(Qt::WA_DeleteOnClose);
            sortTableElementsByCountWgt->show();
        }
    });

    //复制框选区域
    //connect()
}

Widget::~Widget()
{
    thread.wait();
    thread.quit();
    delete simulateLotteryDlg;
}

