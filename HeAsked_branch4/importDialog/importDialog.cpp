#include "importDialog.h"
#include "qss.h"
extern QFont aliFont;
ImportDialog::ImportDialog(Widget* parent):QDialog(parent)
{
    this->setFixedSize(800,70);

    this->setFont(aliFont);

    //layout
    gridLayout = new QGridLayout(this);

    //label
    date = new QLabel(tr("年份"),this);
    periods = new QLabel(tr("期数"),this);
    line = new QLabel(tr("-"),this);
    prizes = new QLabel(tr("奖注"),this);

    //lineEdit
    leDate = new QLineEdit(this);
    lePeriods = new QLineEdit(this);
    lePrizes = new NumLineEdit(this);

    //others
    numCounter = new QLCDNumber(this);
    ok = new QPushButton(tr(" 确定 "),this);
    ok->setObjectName(tr("ok"));


    date->setMaximumSize(QSize(40, 20));
    date->setAlignment(Qt::AlignCenter);
    periods->setMaximumSize(QSize(40, 20));
    periods->setAlignment(Qt::AlignCenter);
    prizes->setAlignment(Qt::AlignCenter);


    leDate->setFixedSize(40,20);
    leDate->setMaxLength(4);
    lePeriods->setFixedSize(40,20);
    lePeriods->setMaxLength(3);
    numCounter->setSegmentStyle(QLCDNumber::Flat);

    //lineEdit文本发生变化，把其中数字个数送给LcdNumber
    connect(lePrizes,&NumLineEdit::textChanged,this,[=](){
        if(lePrizes->text().isEmpty())
            numCounter->display(0);
        else{
            QStringList strList = lePrizes->text().trimmed().split(" ");
            numCounter->display(lePrizes->text().trimmed().split(" ").length());
        }
    });

    //gridLayout的addWidget的后两个参数m,n的含义是占用m行n列个单元格
    //例如后面的ok占用2行1列
    gridLayout->addWidget(date,0,0,1,1);
    gridLayout->addWidget(periods,0,2,1,1);
    gridLayout->addWidget(prizes,0,3,1,1);

    gridLayout->addWidget(leDate,1,0,1,1);
    gridLayout->addWidget(line,1,1,1,1);
    gridLayout->addWidget(lePeriods,1,2,1,1);
    gridLayout->addWidget(lePrizes,1,3,1,1);
    gridLayout->addWidget(numCounter,1,4,1,1);


    //okBtn样式单独设设置
    QString okBtnStyle =
            "QPushButton {"
            "min-width: 30px;"
            "border: 2px solid #717171;"
            "padding: -2px 10px;"
            "margin: 0px;"
            "font-size: 12px;"       // 设置字体大小为12像素
            "}";
    ok->setStyleSheet(okBtnStyle);
    gridLayout->addWidget(ok,1,5,1,1);

    //检查格式并发送一期奖注
    connect(ok,&QPushButton::clicked,this,&ImportDialog::detectAndSend);
}

ImportDialog::~ImportDialog()
{

}

void ImportDialog::detectAndSend()
{
    //输入的必须为四个数字
    QRegularExpression dateRegex("^\\d{4}$");
    QRegularExpressionMatch dateMatch = dateRegex.match(leDate->text().trimmed());
    if(!dateMatch.hasMatch()){
        QMessageBox::warning(nullptr,tr("警告"),tr("日期输入错误"));
        return;
    }

    //输入的必须为1-3个数字
    QRegularExpression periodsRegex("\\d{3}");
    QRegularExpressionMatch periodsMatch = periodsRegex.match(lePeriods->text().trimmed());
    if(!periodsMatch.hasMatch()){
        QMessageBox::warning(nullptr,tr("警告"),tr("期数输入错误"));
        return;
    }

    if(lePrizes->text().split(" ").length() != 20){
        QMessageBox::warning(nullptr,tr("警告"),tr("奖注输入数量错误"));
        return;
    }
    emit sendData(leDate->text()+"-"+lePeriods->text(),lePrizes->strToList());
}

