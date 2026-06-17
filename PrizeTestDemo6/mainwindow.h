#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QDialog>
#include <QPointer>
#include "prizetableview.h"
#include "selectdatadelegate.h"
#include "dataprocessdialog.h"

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
    void onRandomGenerateRows();
    void onRandomMarkNumbers();  // 新增：随机标记10个数字

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
