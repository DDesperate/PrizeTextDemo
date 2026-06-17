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
        const QList<quint8> &row = list.at(i);
        for (int j = 0; j < row.size(); j++) {
            const quint8 col = row.at(j);
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
