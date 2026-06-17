#include"widget.h"
#include<SimulateLotteryDialog/simulatelotterydialog.h>
#include"ui_simulatelotterydialog.h"
void Widget::SimulateLotteryTable()
{
    //如果已经打开了一个simulateLotteryDlg，就把之前的关闭
    if(simulateLotteryDlg!=nullptr)
        simulateLotteryDlg->close();
    int selectNum = group->checkedButton()->text().mid(1).toInt();
    simulateLotteryDlg = new SimulateLotteryDialog(this,winNumLineEdit->text(),selectNumLineEdit->text(),selectNum);
    simulateLotteryDlg->DrawTable();
    simulateLotteryDlg->show();
}
