#ifndef COMPARETHREAD_H
#define COMPARETHREAD_H

#include <QObject>
#include <QThread>
#include "genericfunc.h"
#include <QDebug>

class CompareThread:public QThread
{
    Q_OBJECT
public:
    explicit CompareThread(QThread *parent = nullptr);
    QMap<QList<quint8>,QPair<int,QString>> res_samePrizes;
signals:
    void sendResult(QMap<QList<quint8>,QPair<int,QString>> *res);
    void sendProgressSignal(int,int);
public slots:
    void calCompare(const QVector<QList<quint8>> &left,const QVector<QList<quint8>> &right);
};

#endif // COMPARETHREAD_H
