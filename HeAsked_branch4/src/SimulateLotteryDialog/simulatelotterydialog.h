#ifndef SIMULATELOTTERYDIALOG_H
#define SIMULATELOTTERYDIALOG_H

#include <QDialog>
#include <QTableWidget>

namespace Ui {
class SimulateLotteryDialog;
}

class SimulateLotteryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SimulateLotteryDialog(QWidget *parent = nullptr,const QString winPrize= "",const QString selectPrize = "",const int = 0);
    void InitDialog();
    void DrawTable();
    void CopySelectFromTable(QTableWidget*);
    ~SimulateLotteryDialog();

private:
    QString prize;
    QString selectPrize;
    int selectNum;
    Ui::SimulateLotteryDialog *ui;
};

#endif // SIMULATELOTTERYDIALOG_H
