#ifndef TWOSTEPVERIFICATIONWGT_H
#define TWOSTEPVERIFICATIONWGT_H

#include <QtCore/QVariant>
#include <comparethread.h>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QDebug>
class TwoStepVerificationWgt: public QWidget
{
    Q_OBJECT
signals:
    void sendInput(const QVector<QList<quint8>> &left,const QVector<QList<quint8>> &right);
private slots:
    void recvProgressSlot(int totalCount,int count){
        progressBar->setMaximum(totalCount);
        progressBar->setValue(count);
    }
public:
    explicit TwoStepVerificationWgt(QWidget *parent);
    ~TwoStepVerificationWgt();
    void setUi_twoStepVerificationWgt(QWidget* widget);
    void getData(const QMap<QList<quint8>,QPair<int,QString>> &res);
    QString dataStructureToText_withCount(const QMap<QList<quint8>,QPair<int,QString>> &res,int num,bool condition);
    QPair<int,QString> textToDataStructure(QVector<QList<quint8>> &data, const QString &text);
    void copy_onlyPrize(const QString &text);
//    void copyWithoutCount();
private:
    CompareThread compareThread;
    QThread thread;
    QMap<QList<quint8>,QPair<int,QString>> *NewRes = nullptr;

    QVBoxLayout *main_VLayout;
    QHBoxLayout *input_HLayout;
    QVBoxLayout *leftInput_VLayout;
    QVBoxLayout *rightInput_VLayout;
    QHBoxLayout *leftInput_setting_HLayout;
    QHBoxLayout *rightInput_setting_HLayout;
    QSpinBox *leftInput_setting_spinBox;
    QPushButton *leftInput_setting_confirmBtn;
    QPlainTextEdit *leftInput_text;
    QSpinBox *rightInput_setting_spinBox;
    QPushButton *rightInput_setting_confirmBtn;
    QPlainTextEdit *rightInput_text;
    QProgressBar *progressBar;
    QHBoxLayout *output_HLayout;
    QVBoxLayout *output_limitQuantity_VLayout;
    QVBoxLayout *output_allResult_VLayout;
    QHBoxLayout *output_limitQuantity_setting_HLayout;
    QHBoxLayout *output_allResult_setting_HLayout;
    QSpinBox *output_limitQuantity_spinBox;
    QPushButton *output_limitQuantity_confirmBtn;
    QPushButton *output_limitQuantity_copyBtn;
    QPushButton *output_allResult_copyBtn;
    QPlainTextEdit *output_limitQuantity_text;
    QPlainTextEdit *output_allResult_text;

    QMap<QList<quint8>,QPair<int,QString>> recv_res;
    QMap<QList<quint8>,QPair<int,QString>> res_samePrizes;
};

#endif // TWOSTEPVERIFICATIONWGT_H


