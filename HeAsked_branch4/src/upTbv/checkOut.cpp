#include "upTbv.h"
int UpTableView::checkDate(const QString &date)
{
    QRegularExpression dateRegex("^\\d{4}-\\d{3}$");

    QRegularExpressionMatch dateMatch = dateRegex.match(date);

    if(!dateMatch.hasMatch()){
        return -1;
    }
}

int UpTableView::checkPrizes(const QString &date,QList<quint8> prizes){
    QStringList prizeStrList = date.split(" ");
    int col = 1;
    for(QString prizeStr:prizeStrList){
        bool ok;
        quint8 num = static_cast<quint8>(prizeStr.toUInt(&ok));
        if(ok) {
            prizes.append(num);
        } else {
            return col;
        }
        col++;
    }
    if(col != 21)
    {
        return -1;
    }
}
