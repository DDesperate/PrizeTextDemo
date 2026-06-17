#ifndef COLSORTTBVSTRUCT_H
#define COLSORTTBVSTRUCT_H
#include<QString>
#include<QVector>

typedef struct {
    QString date;
    QVector<quint8> prizes;
} PrizeRowWithDate;

#endif // COLSORTTBVSTRUCT_H
