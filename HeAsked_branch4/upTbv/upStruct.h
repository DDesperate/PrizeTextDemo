#ifndef UPSTRUCT_H
#define UPSTRUCT_H

#include<QList>
#include<QColor>
#include<QMessageBox>
#include<array>

typedef struct{
    quint8 num = 0;
    QColor color = QColor(49,102,204);
}prizeInfo;

typedef struct{
    bool isSelected;
    QVector<prizeInfo> prizes;

    QList<quint8> getPrizeList(){
        QList<quint8> prizeList;
        for(auto prize:prizes)
        {
            if(prize.num != 0)
                prizeList.append(prize.num);
        }
        return prizeList;

    }
}tbRow;

typedef struct{
    int row;
    int col;
    QString text;
}coo;

#endif

