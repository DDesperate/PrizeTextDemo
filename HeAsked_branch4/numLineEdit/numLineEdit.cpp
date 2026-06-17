#include "numLineEdit.h"
#include <QKeyEvent>
#include <QRegExp>

NumLineEdit::NumLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setClearButtonEnabled(true);
}

void NumLineEdit::fmtNum()
{
    QString text = this->text(); // 获取QLineEdit中的文本

    //过滤掉字符串中非数字的字符(通过正则)
    text.remove(QRegExp("[^0-9]"));

    //如果字符串size为奇数，最后一位前自动补零
    if (text.size() % 2 != 0)
    {
        text.insert(text.size() - 1, "0");
    }

    //每一个prize作为一个元素放进QStringList中
    QStringList textList;
    for (int i = 0; i < text.size(); i += 2){
        textList.append(text.mid(i,2));
    }

    //排序，去重
    textList.sort();
    textList.removeDuplicates();//注意:此函数只能去重相邻元素，所以需要先排序

    //过滤掉小于0或大于80的元素并在每个元素之间加空格
    text.clear();
    for(auto iter:textList){
        if(iter.toInt() >0 && iter.toInt()<=80)
            text += iter + " ";
    }

    //trimmed():去掉QString两端的\r\n空格等
    this->setText(text.trimmed());
}

QList<quint8> NumLineEdit::strToList()
{
    QList<quint8> numList;

    if(this->text().isEmpty()){
        return numList;
    }
    else{
        QStringList prizes = this->text().split(" ");

        for(QString prize:prizes)
        {
            numList.append(static_cast<quint8>(prize.toInt()));
        }
        return numList;
    }
}

void NumLineEdit::setListIn(const QList<quint8> numList)
{
    QString text;
    for(quint8 num:numList){
        text +=+" "+QString::number(num).rightJustified(2,'0');
    }
    this->setText(text.trimmed());
}

void NumLineEdit::addNum(int num)
{
    if(1 <= num && num <= 80)
    {
        QString strNum = QString::number(num).rightJustified(2,'0');
        this->setText(this->text().append(" "+strNum));
    }
}


void NumLineEdit::keyPressEvent(QKeyEvent *event)
{
    QLineEdit::keyPressEvent(event);
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) { // 检查是否按下回车键
        fmtNum();
    }
}
