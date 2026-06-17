#include "twoStepVerificationWgt.h"
#include "genericfunc.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QClipboard>

TwoStepVerificationWgt::TwoStepVerificationWgt(QWidget *parent) :
    QWidget(parent)
{
    setUi_twoStepVerificationWgt(this);
    setWindowFlags(Qt::Window);

    connect(leftInput_setting_confirmBtn,&QPushButton::clicked,this,[=]{
        leftInput_text->clear();
        leftInput_text->appendPlainText(dataStructureToText_withCount(recv_res,leftInput_setting_spinBox->value(),true));
    });

    connect(rightInput_setting_confirmBtn,&QPushButton::clicked,this,[=]{
        rightInput_text->clear();
        rightInput_text->appendPlainText(dataStructureToText_withCount(recv_res,rightInput_setting_spinBox->value(),true));
    });

    connect(output_limitQuantity_confirmBtn,&QPushButton::clicked,this,[=]{

        //每次比较都需要清空上一次的数据
        //为什么res_samePrizes不在connect中定义？
        //因为checkoutWgt需要获取到数据res_samePrizes
        compareThread.res_samePrizes.clear();

        //获取左表和右表的值转成数据结构
        //如果数据正确返回值为1
        //数据为空，返回值为0
        //数据错误，返回值为-1
        QVector<QList<quint8>> left;
        QPair<int,QString> leftRes = textToDataStructure(left,leftInput_text->toPlainText());
        QVector<QList<quint8>> right;
        QPair<int,QString> rightRes = textToDataStructure(right,rightInput_text->toPlainText());


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
        output_allResult_text->clear();
        output_allResult_text->appendPlainText(dataStructureToText_withCount(*NewRes,0,false));
        output_limitQuantity_text->clear();
        output_limitQuantity_text->appendPlainText(dataStructureToText_withCount(*NewRes,output_limitQuantity_spinBox->value(),true));
//        //为了防止验证功能出错
//        //当计算时如果验证窗口存在，那么清空其中的数据
//        if(checkoutWgt){
//            checkoutWgt->clearAll();
//            checkoutWgt->getDate(compareThread.res_samePrizes);
//        }
    });

    //复制不带计数(带条件)
    connect(output_limitQuantity_copyBtn,&QPushButton::clicked,[=]{
        copy_onlyPrize(output_limitQuantity_text->toPlainText());
    });

    //复制
    connect(output_allResult_copyBtn,&QPushButton::clicked,[=]{
        copy_onlyPrize(output_allResult_text->toPlainText());
    });
}

TwoStepVerificationWgt::~TwoStepVerificationWgt()
{}


//把计算线程计算出的数据根据需求打印成文本，显示计数信息,限定一组数当中的元素个数
QString TwoStepVerificationWgt::dataStructureToText_withCount(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition)
{
    QString resString;
    int count = 0;
    for (auto it = res.constBegin(); it != res.constEnd(); ++it) {
        const QList<quint8>& keyList = it.key();
        const QPair<int, QString>& pairValue = it.value();
        if(condition){
            if (keyList.size() != num)
                continue;
        }
        for(quint8 prize:keyList)
        {
            resString += QString::number(prize).rightJustified(2,'0') + ' ';
        }
        resString += tr("出现次数:") + QString::number(res[keyList].first) + '\n';
        count++;
    }
    QString rowCount = "总行数:"+QString::number(count)+"\n";
    return rowCount+resString;
}

//暂时没有检查每一行的数据是否符合格式
//没有检查数字是否可能超出80
//返回值为 0，代表空值
//返回值为 1，代表正常
//返回值为 -1,代表出现错误
QPair<int,QString> TwoStepVerificationWgt::textToDataStructure(QVector<QList<quint8>> &data, const QString &text)
{

    if (text.isEmpty()) {
            return QPair<int,QString> (0,"输入值为空");
    }

    // 分割字符串并去除首尾空格
    QStringList strList = text.trimmed().split("\n");

    // 遍历导入的txt数据
    int row = 0;
    for (const QString& rowString : strList)
    {
        row++;

        // 跳过空行
        if (rowString.isEmpty())
            continue;

        QList<quint8> dataStructRow;

        // 分割并去除两端可能存在的空格
        QStringList prizeList = rowString.trimmed().split(" ");

        // 将字符串转换为quint8并添加到列表中
        int col = 0;
        for (const QString& prize : prizeList)
        {
            col ++;

            if(!prize.isEmpty())
            {
                QRegularExpression regex1("出现次数:(\\d+)");
                QRegularExpression regex2("总行数:(\\d+)");
                if(regex1.match(prize).hasMatch()||regex2.match(prize).hasMatch())
                {
                    continue;
                }
                else if(prize.toInt()>80 || prize.toInt() <1){
                    QString errorInfo = "超出范围: \n行:" + QString::number(row) + "列:" + QString::number(col) + "\n值:" + prize;//一旦发现数据不对，直接返回空值。
                    return QPair<int,QString> (-1,errorInfo);
                }

                dataStructRow.append(static_cast<quint8>(prize.toInt()));
            }

        }
        if(!dataStructRow.isEmpty())
            data.append(dataStructRow);
    }

    return QPair<int,QString> (1,"");
}

//用于仅复制奖注，不复制其他信息
//处理比较草率
//获取文本，去除第一行，去除每一行的后7个字符
void TwoStepVerificationWgt::copy_onlyPrize(const QString &text)
{
    QStringList lines = text.split('\n');
    lines.removeFirst();
    for (int i = 0; i < lines.size(); ++i) {
        QString trimmedLine = lines[i].trimmed();
        QString truncatedLine = trimmedLine.mid(0, trimmedLine.length() - 7);
        lines[i] = truncatedLine;
    }
    QString modifiedString = lines.join('\n');
    QApplication::clipboard()->setText(modifiedString);
}
