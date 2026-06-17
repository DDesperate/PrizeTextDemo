#include "downTbv.h"
#include <QDateTime>
#include <QRandomGenerator>

void markByList(slctTbRow* row,QList<int> list)
{

    for(auto it_prizeInfo = row->prizes.begin();it_prizeInfo != row->prizes.end();it_prizeInfo++)
    {
        if(list.contains(it_prizeInfo->prize))
        {
            it_prizeInfo->setSelected();
        }
    }
}

void DownTableView::randomSelectPrizesForTbv(int n, QVector<slctTbRow> *list)
{
    clearHighLight();
    QByteArray seedData = QByteArray::number(QDateTime::currentMSecsSinceEpoch()); // 使用当前时间作为种子数据
    QRandomGenerator gen(seedData.toULongLong()); // 使用不同的种子值初始化随机数生成器
    for(auto row = list->begin();row != list->end();row++)
    {
        //遍历第一次，获取未被划掉的一组数字
        QList<int> numbers;
        for(auto col = row->prizes.begin();col != row->prizes.end();col++)
        {
            if(col->isDeleted == false) {
                numbers.append(col->prize); // 填充1到n的整数
            }
        }
        //如果要选出的数字的个数大于本行中未被划掉的数字个数
        if(n >= numbers.size())
        {
            //一行中除了被划掉的数字全部标绿
            markByList(row,numbers);
            continue;//跳过本次循环
        }
        else{
            //洗牌
            std::random_shuffle(numbers.begin(), numbers.end(), [&gen](int i) {
                return gen.bounded(i); // 使用Qt的界限函数生成随机数
            });
            QList<int> randomNumbers = numbers.mid(0, n);
            markByList(row,randomNumbers);
        }
    }
}

void DownTableView::randomSelectPrizes(int n)
{
    qDebug() << "randomSelectPrizes";
    if(mode == repeat){
        qDebug() << "modeWgt->repeatMode->isChecked()";
        //更改数据结构中对应的数据为selected
        randomSelectPrizesForTbv(n,&selectDataVec);
    }
    if(mode == mix){
        qDebug() << "modeWgt->mixMode->isChecked()";
        randomSelectPrizesForTbv(n,&selectMixDataVec);
    }
    if(mode == neighbor){
        qDebug() << "modeWgt->neighborMode->isChecked()";
        randomSelectPrizesForTbv(n,&selectNeighborDataVec);
    }
    this->viewport()->update();
}
