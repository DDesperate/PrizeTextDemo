#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include "prizetableview.h"
#include "selectdatadelegate.h"
#include "dataprocessdialog.h"

/**
 * @brief 主窗口
 * 
 * 使用原始数据格式（slctTbRow）
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onCellClicked(int row, int col);
    void onAddRow();
    void onToggleSelect();
    void onToggleDelete();
    void onToggleRowSelect();
    void onClearAll();
    void onOpenNewWindow();

private:
    void setupUI();
    void generateTestData();
    void updateStatusLabel();

    PrizeTableView *tableView;
    SelectDataDelegate *delegate;
    QVector<slctTbRow> selectDataVec;

    QLabel *statusLabel;
    int currentRow = -1;
    int currentCol = -1;
};

#endif // MAINWINDOW_H
