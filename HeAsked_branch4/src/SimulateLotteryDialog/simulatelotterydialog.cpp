#include "simulatelotterydialog.h"
#include "ui_simulatelotterydialog.h"

SimulateLotteryDialog::SimulateLotteryDialog(QWidget *parent,const QString winPrize,const QString selectPrize,const int selectNum) :
    QDialog(parent),
    prize(winPrize),
    selectPrize(selectPrize),
    selectNum(selectNum),
    ui(new Ui::SimulateLotteryDialog)
{
    ui->setupUi(this);

    //美化列表
    InitDialog();

    //复制
    connect(ui->copy,&QPushButton::clicked,this,[=]{
        CopySelectFromTable(ui->detail);
    });
}

SimulateLotteryDialog::~SimulateLotteryDialog()
{
    delete ui;
}



