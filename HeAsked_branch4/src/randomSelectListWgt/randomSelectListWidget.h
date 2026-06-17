#ifndef RANDOMSELECTLISTWIDGET_H
#define RANDOMSELECTLISTWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDebug>


class RandomSelectListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RandomSelectListWidget(QWidget *parent = nullptr,const QList<QList<quint8>> &list = QList<QList<quint8>>());
    ~RandomSelectListWidget();

private:
    QVBoxLayout *layV_main;
    QTextEdit *randomSelectedPrizesList;
};

#endif // RANDOMSELECTLISTWIDGET_H
