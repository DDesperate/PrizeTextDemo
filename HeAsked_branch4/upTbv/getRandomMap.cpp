#include "upTbv.h"
#include <QDateTime>
#include <QRandomGenerator>
void UpTableView::getRandomMap(int n)
{
    QList<QString> keys = dataMap.keys();

    //随机数取值范围
    int range = dataMap.size();

    QByteArray seedData = QByteArray::number(QDateTime::currentMSecsSinceEpoch()); // 使用当前时间作为种子数据
    QRandomGenerator gen(seedData.toULongLong()); // 使用不同的种子值初始化随机数生成器

    QList<int> numbers;
    for (int i = 0; i < range; ++i) {
        numbers.append(i); // 填充1到n的整数
    }

    std::random_shuffle(numbers.begin(), numbers.end(), [&gen](int i) {
        return gen.bounded(i); // 使用Qt的界限函数生成随机数
    });

    QList<int> randomNumbers = numbers.mid(0, n);

    // 根据随机索引获取键值并添加到QList<QString>中
    // 获取到随机键值randomKeys
    QList<QString> randomKeys;
    for (int index: randomNumbers) {
        randomKeys.append(keys.at(index));
    }

    for(auto date:randomKeys)
    {
        //加入选中集合
        selectedSet.insert(date);

        emit insertToDownTbv(date,dataMap[date].getPrizeList());

        //如果数据结构中该期被选中则将其标记为未选中，如果该期未选中则将其标记为选中
        dataMap[date].isSelected = !dataMap[date].isSelected;

        refreshOneRowByDate(date);
    }

    return;
}
