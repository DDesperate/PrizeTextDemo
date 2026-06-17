#include "mainwindow.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include <QHBoxLayout>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUI();
    generateTestData();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // ========== 顶部标题 ==========
    QLabel *titleLabel = new QLabel(QStringLiteral("🎱 奖注绘制测试 Demo"), this);
    titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #333; padding: 5px;");
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    // ========== 表格区域 ==========
    tableView = new PrizeTableView(this);

    delegate = new SelectDataDelegate(this);
    delegate->setSelectData(&selectDataVec);
    tableView->setItemDelegate(delegate);
    tableView->setPrizeData(&selectDataVec);

    tableView->setColumnCount(81);

    connect(tableView, &PrizeTableView::cellClicked, this, &MainWindow::onCellClicked);

    mainLayout->addWidget(tableView, 1);

    // ========== 状态栏 ==========
    statusLabel = new QLabel(QStringLiteral("请点击表格单元格"), this);
    statusLabel->setStyleSheet("padding: 5px; background: #f0f0f0; border-radius: 3px;");
    mainLayout->addWidget(statusLabel);

    // ========== 按钮区域 ==========
    QHBoxLayout *btnLayout = new QHBoxLayout();

    QPushButton *btnAddRow = new QPushButton(QStringLiteral("➕ 添加一行"), this);
    QPushButton *btnRandom = new QPushButton(QStringLiteral("🎲 随机生成3-5行数据"), this);
    QPushButton *btnSelect = new QPushButton(QStringLiteral("✅ 切换选中"), this);
    QPushButton *btnDelete = new QPushButton(QStringLiteral("❌ 切换划掉"), this);
    QPushButton *btnRowSelect = new QPushButton(QStringLiteral("🎨 整行选中"), this);
    QPushButton *btnRandomMark = new QPushButton(QStringLiteral("🎯 随机标记10个数字"), this);  // 新增
    QPushButton *btnClear = new QPushButton(QStringLiteral("🗑️ 清空数据"), this);
    QPushButton *btnNewWin = new QPushButton(QStringLiteral("🖼️ 打开新窗口"), this);

    QString btnStyle = R"(
        QPushButton {
            padding: 8px 16px;
            font-size: 14px;
            border-radius: 4px;
            border: 1px solid #ccc;
            background: #fff;
        }
        QPushButton:hover {
            background: #e0e0e0;
        }
        QPushButton:pressed {
            background: #d0d0d0;
        }
    )";
    btnAddRow->setStyleSheet(btnStyle);
    btnRandom->setStyleSheet(btnStyle);
    btnSelect->setStyleSheet(btnStyle);
    btnDelete->setStyleSheet(btnStyle);
    btnRowSelect->setStyleSheet(btnStyle);
    btnRandomMark->setStyleSheet(btnStyle);  // 新增
    btnClear->setStyleSheet(btnStyle);
    btnNewWin->setStyleSheet(btnStyle);

    connect(btnAddRow, &QPushButton::clicked, this, &MainWindow::onAddRow);
    connect(btnRandom, &QPushButton::clicked, this, &MainWindow::onRandomGenerateRows);
    connect(btnSelect, &QPushButton::clicked, this, &MainWindow::onToggleSelect);
    connect(btnDelete, &QPushButton::clicked, this, &MainWindow::onToggleDelete);
    connect(btnRowSelect, &QPushButton::clicked, this, &MainWindow::onToggleRowSelect);
    connect(btnRandomMark, &QPushButton::clicked, this, &MainWindow::onRandomMarkNumbers);  // 新增
    connect(btnClear, &QPushButton::clicked, this, &MainWindow::onClearAll);
    connect(btnNewWin, &QPushButton::clicked, this, &MainWindow::onOpenNewWindow);

    btnLayout->addWidget(btnAddRow);
    btnLayout->addWidget(btnRandom);
    btnLayout->addWidget(btnSelect);
    btnLayout->addWidget(btnDelete);
    btnLayout->addWidget(btnRowSelect);
    btnLayout->addWidget(btnRandomMark);  // 新增
    btnLayout->addWidget(btnClear);
    btnLayout->addStretch();
    btnLayout->addWidget(btnNewWin);

    mainLayout->addLayout(btnLayout);

    setCentralWidget(centralWidget);
    resize(900, 500);
    setWindowTitle(QStringLiteral("奖注绘制测试 Demo - Qt 5.15.0"));
}

void MainWindow::generateTestData()
{
    selectDataVec.clear();

    for (int i = 0; i < 5; ++i) {
        slctTbRow row;
        row.date = QDate(2024, 1, i + 1).toString("yyyy-MM-dd");
        row.isSelected = false;

        int prizeCount = 20;
        QSet<int> usedPrizes;

        for (int j = 0; j < prizeCount; ++j) {
            slcInfo info;

            int prizeNum;
            do {
                prizeNum = QRandomGenerator::global()->bounded(1, 81);
            } while (usedPrizes.contains(prizeNum));

            usedPrizes.insert(prizeNum);

            info.prize = static_cast<quint8>(prizeNum);
            info.color = Qt::blue;
            info.isSelect = false;
            info.isDeleted = false;
            row.prizes.append(info);
        }

        selectDataVec.append(row);
    }

    if (!selectDataVec.isEmpty()) {
        if (!selectDataVec[0].prizes.isEmpty()) {
            selectDataVec[0].prizes[0].isSelect = true;
        }
        if (selectDataVec.size() > 1 && selectDataVec[1].prizes.size() > 1) {
            selectDataVec[1].prizes[1].isDeleted = true;
        }
        if (selectDataVec.size() > 2) {
            selectDataVec[2].isSelected = true;
        }
    }

    tableView->refreshModel();
}

void MainWindow::onCellClicked(int row, int col)
{
    currentRow = row;
    currentCol = col;
    updateStatusLabel();
}

void MainWindow::updateStatusLabel()
{
    QString status;

    if (currentRow < 0 || currentCol < 0) {
        status = QStringLiteral("请点击表格单元格");
    }
    else if (currentCol == 0) {
        status = QStringLiteral("当前: 第 %1 行 (日期列)").arg(currentRow + 1);
    }
    else {
        bool hasPrize = false;
        if (currentRow < selectDataVec.size()) {
            for (const auto &prize : selectDataVec[currentRow].prizes) {
                if (prize.prize == currentCol) {
                    hasPrize = true;
                    QString state;
                    if (prize.isSelect) state = QStringLiteral("🟢 已选中");
                    else if (prize.isDeleted) state = QStringLiteral("❌ 已划掉");
                    else state = QStringLiteral("⚪ 普通");

                    status = QStringLiteral("第 %1 行, 列 %2 | 奖注: %3 | 状态: %4")
                                 .arg(currentRow + 1)
                                 .arg(currentCol)
                                 .arg(QString::number(prize.prize).rightJustified(2, '0'))
                                 .arg(state);
                    break;
                }
            }
        }

        if (!hasPrize) {
            status = QStringLiteral("第 %1 行, 列 %2 | 该位置无奖注")
                         .arg(currentRow + 1)
                         .arg(currentCol);
        }
    }

    statusLabel->setText(status);
}

void MainWindow::onRandomGenerateRows()
{
    selectDataVec.clear();

    int rowCount = QRandomGenerator::global()->bounded(3, 6);  // 3, 4 或 5 行

    for (int i = 0; i < rowCount; ++i) {
        slctTbRow row;
        row.date = QDate(2024, 1, i + 1).toString("yyyy-MM-dd");
        row.isSelected = false;

        QSet<int> usedPrizes;
        for (int j = 0; j < 20; ++j) {
            slcInfo info;
            int prizeNum;
            do {
                prizeNum = QRandomGenerator::global()->bounded(1, 81);  // 1-80 闭区间
            } while (usedPrizes.contains(prizeNum));

            usedPrizes.insert(prizeNum);
            info.prize = static_cast<quint8>(prizeNum);
            info.color = Qt::blue;
            info.isSelect = false;
            info.isDeleted = false;
            row.prizes.append(info);
        }

        selectDataVec.append(row);
    }

    tableView->refreshModel();
    statusLabel->setText(QStringLiteral("✅ 已随机生成 %1 行数据，每行 20 个数 (1-80)").arg(rowCount));
}

void MainWindow::onAddRow()
{
    slctTbRow newRow;
    newRow.date = QDate::currentDate().toString("yyyy-MM-dd");
    newRow.isSelected = false;

    QList<QColor> colors = {Qt::red, Qt::blue, Qt::green, Qt::magenta, Qt::cyan};
    QSet<int> usedPrizes;

    int count = QRandomGenerator::global()->bounded(3, 6);
    for (int i = 0; i < count; ++i) {
        slcInfo info;
        do {
            info.prize = static_cast<quint8>(QRandomGenerator::global()->bounded(1, 81));
        } while (usedPrizes.contains(info.prize));

        usedPrizes.insert(info.prize);
        info.color = colors[QRandomGenerator::global()->bounded(colors.size())];
        newRow.prizes.append(info);
    }

    selectDataVec.append(newRow);
    tableView->refreshModel();

    statusLabel->setText(QStringLiteral("✅ 已添加新行"));
}

void MainWindow::onToggleSelect()
{
    if (currentRow < 0 || currentCol <= 0) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请先点击一个奖注单元格（非日期列）"));
        return;
    }

    if (currentRow >= selectDataVec.size())
        return;

    for (auto &prize : selectDataVec[currentRow].prizes) {
        if (prize.prize == currentCol) {
            prize.switchSelect();
            tableView->refreshModel();
            updateStatusLabel();
            return;
        }
    }

    QMessageBox::information(this, QStringLiteral("提示"),
                             QStringLiteral("该单元格没有奖注数据"));
}

void MainWindow::onToggleDelete()
{
    if (currentRow < 0 || currentCol <= 0) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请先点击一个奖注单元格（非日期列）"));
        return;
    }

    if (currentRow >= selectDataVec.size())
        return;

    for (auto &prize : selectDataVec[currentRow].prizes) {
        if (prize.prize == currentCol) {
            prize.setDeleted(!prize.isDeleted);
            tableView->refreshModel();
            updateStatusLabel();
            return;
        }
    }

    QMessageBox::information(this, QStringLiteral("提示"),
                             QStringLiteral("该单元格没有奖注数据"));
}

void MainWindow::onToggleRowSelect()
{
    if (currentRow < 0) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("请先点击表格中的某一行"));
        return;
    }

    if (currentRow >= selectDataVec.size())
        return;

    selectDataVec[currentRow].isSelected = !selectDataVec[currentRow].isSelected;
    tableView->refreshModel();
    updateStatusLabel();
}

void MainWindow::onClearAll()
{
    auto reply = QMessageBox::question(this, QStringLiteral("确认"),
                                       QStringLiteral("确定要清空所有数据吗？"),
                                       QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        selectDataVec.clear();
        currentRow = -1;
        currentCol = -1;
        tableView->refreshModel();
        statusLabel->setText(QStringLiteral("🗑️ 已清空所有数据"));
    }
}

void MainWindow::onOpenNewWindow()
{
    DataProcessDialog *dialog = new DataProcessDialog(this);
    dialog->setAttribute(Qt::WA_DeleteOnClose);

    connect(dialog, &DataProcessDialog::requestDataSync, this, [this, dialog](){
        if (!this->selectDataVec.isEmpty()) {
            dialog->updateData(this->selectDataVec);
        }
    });

    dialog->showMaximized();
}

void MainWindow::onRandomMarkNumbers()
{
    if (selectDataVec.isEmpty()) {
        QMessageBox::information(this, QStringLiteral("提示"),
                                 QStringLiteral("暂无数据，请先生成数据"));
        return;
    }

    // 1. 先清除所有已有的选中状态
    for (slctTbRow &row : selectDataVec) {
        for (slcInfo &prize : row.prizes) {
            prize.isSelect = false;
        }
    }

    // 2. 随机选择10个不重复的数字（1-80）
    QSet<int> numbersToMark;
    while (numbersToMark.size() < 10) {
        int num = QRandomGenerator::global()->bounded(1, 81);  // 1-80
        numbersToMark.insert(num);
    }

    // 3. 在所有行中，将这10个数字标记为选中状态
    int markedCount = 0;
    for (slctTbRow &row : selectDataVec) {
        for (slcInfo &prize : row.prizes) {
            if (numbersToMark.contains(prize.prize)) {
                prize.isSelect = true;
                prize.isDeleted = false;  // 确保不被划掉
                markedCount++;
            }
        }
    }

    // 4. 刷新显示
    tableView->refreshModel();

    // 5. 显示选中的数字列表
    QString numbersStr;
    QList<int> sortedNumbers = numbersToMark.values();
    std::sort(sortedNumbers.begin(), sortedNumbers.end());
    for (int num : sortedNumbers) {
        numbersStr += QString::number(num).rightJustified(2, '0') + " ";
    }

    statusLabel->setText(QStringLiteral("🎯 已随机标记10个数字: %1 | 共标记了 %2 个奖注")
                             .arg(numbersStr.trimmed())
                             .arg(markedCount));
}

