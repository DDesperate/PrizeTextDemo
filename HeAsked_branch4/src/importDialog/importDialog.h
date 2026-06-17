#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H
#include <QDebug>
#include <QDialog>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QLCDNumber>
#include <QRegularExpression>
#include <QMessageBox>
#include "widget.h"
#include "numLineEdit/numLineEdit.h"
class ImportDialog:public QDialog
{
    Q_OBJECT
public:
    ImportDialog(Widget *parent = nullptr);
    ~ImportDialog();

private:
    void detectAndSend();

    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *date;
    QLabel *periods;
    QLabel *prizes;
    QLineEdit *leDate;
    QLineEdit *lePeriods;
    NumLineEdit *lePrizes;
    QLCDNumber *numCounter;
    QLabel *line;
    QPushButton *ok;

signals:
    void sendData(const QString& date,const QList<quint8>& prizes);


};

#endif
