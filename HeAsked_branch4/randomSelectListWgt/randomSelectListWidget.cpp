#include "randomSelectListWidget.h"

RandomSelectListWidget::RandomSelectListWidget(QWidget *parent,const QList<QList<quint8>> &list) :
    QWidget(parent)
{
    setWindowFlags(Qt::Window);
    layV_main = new QVBoxLayout(this);
    randomSelectedPrizesList = new QTextEdit(this);
    layV_main->addWidget(randomSelectedPrizesList);
    randomSelectedPrizesList->setReadOnly(true);
    QString str;
    for (int i = 0; i < list.size(); i++) {
        //排序(因为未知原因，又是送进来的数据list可能是乱序)
        QList<quint8> mutableRow = list.at(i);
        std::sort(mutableRow.begin(), mutableRow.end());

        for (int j = 0; j < mutableRow.size(); j++) {
            const quint8 col = mutableRow.at(j);
            str += QString::number(col).rightJustified(2,'0') + " ";
            qDebug() << str;
        }

        str = str.trimmed();
        str += '\n';
    }
    randomSelectedPrizesList->setText(str);

}

RandomSelectListWidget::~RandomSelectListWidget()
{
}
