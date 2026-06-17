#include "randomshufflewgt.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

//遍历表中前rowCount行数据转化为一个一维数组(期数)和一个二维数组(奖注数据)
void TraversalTable(QVector<QString> &issue_num,QVector<QVector<quint8>> &prize2DArray,QTableWidget *dataTable,int rowCount) {

    for(int row = 0; row <rowCount; row++)
    {
        issue_num << dataTable->item(row, 0)->text();
        QVector<quint8> rowData;
        for(int col = 1; col <= 20; col++)
        {
            rowData.append(dataTable->item(row,col)->text().toUInt());
        }
        prize2DArray << rowData;
    }
}

//判断容器中是否有两个相同元素(需要元素和容器支持sort，unique)
template <typename T, typename Container>
bool hasDuplicates(const Container& container) {
    // 创建容器的副本并进行排序
    Container sortedContainer = container;
    std::sort(sortedContainer.begin(), sortedContainer.end());

    // 使用std::unique重排容器，并得到不重复元素的末尾迭代器
    auto uniqueEnd = std::unique(sortedContainer.begin(), sortedContainer.end());

    // 如果重排后的末尾迭代器不等于容器的末尾，则表示有重复元素
    return uniqueEnd != sortedContainer.end();
}

// 函数用于将QVector<quint8>的内容写入到文本文件
bool writeQVectorToTextFile(const QVector<quint8>& vector, const QString& filename, bool judgmentResult) {
    QFile file(filename);
    QIODevice::OpenMode mode = QIODevice::WriteOnly | QIODevice::Text;

    // 检查文件是否存在
    if (QFileInfo::exists(filename)) {
        // 如果文件存在，则设置为追加模式
        mode |= QIODevice::Append;
    }

    if (!file.open(mode)) {
        qWarning("Failed to open file for writing.");
        return false;
    }

    QTextStream out(&file);

    // 如果是追加模式，并且文件不为空，则在开头添加一个换行符
    if (mode & QIODevice::Append && file.size() > 0) {
        out << "\n";
    }

    out << "judgmentResult:" << (judgmentResult ? "true" : "false") << "\n";
    for (quint8 value : vector) {
        out << value << " ";
    }

    file.close();
    return true;
}

bool appendTextToFile(const QString& filename, const QString& textToAppend) {
    QFile file(filename);

    // 检查文件是否存在
    if (!QFileInfo::exists(filename)) {
        // 如果文件不存在，则创建一个新文件
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qWarning("Failed to create file for writing.");
            return false;
        }
    } else {
        // 如果文件存在，则以只读模式打开文件以检查其内容
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qWarning("Failed to open file for reading.");
            return false;
        }

        // 读取文件内容
        QString content = file.readAll();
        // 关闭文件，以便重新以追加模式打开
        file.close();

        // 以追加模式打开文件
        if (!file.open(QIODevice::Append | QIODevice::Text)) {
            qWarning("Failed to open file for appending.");
            return false;
        }

        // 如果文件不是空的，添加一个换行符
        if (!content.isEmpty() && !content.endsWith('\n')) {
            QTextStream out(&file);
            out << "\n";
        }
    }

    // 将新文本追加到文件
    QTextStream out(&file);
    out << textToAppend;

    // 关闭文件
    file.close();
    return true;
}

//对二维数组洗牌(每一列中的各个元素随机调换)
void shuffling2DArrayByCol(QVector<QVector<quint8>>& prize2DArray,const QList<quint8> fixedNum) {
    if (prize2DArray.isEmpty()) {
        return;
    }

    // 获取列数
    int colCount = prize2DArray[0].size();

    //遍历2维数组中的每一列
    for (int col = 0; col < colCount;) {
        // 获取当前列的元素数量
        int rowCount = prize2DArray.size();

        //用于记录被交换的元素的行索引
        int rowIndex_1;
        int rowIndex_2;

        // 对当前列的每个元素进行洗牌
        for (int row = rowCount - 1; row > 0; --row) {
            // 生成一个随机索引
            int randomIndex = QRandomGenerator::global()->bounded(rowCount);

            // 检查随机索引和当前行的元素是否在fixedNum中
            if (!fixedNum.contains(prize2DArray[randomIndex][col]) &&
                    !fixedNum.contains(prize2DArray[row][col])) {
                // 如果不在fixedNum中，则交换当前元素和随机索引处的元素
                quint8 temp = prize2DArray[randomIndex][col];
                prize2DArray[randomIndex][col] = prize2DArray[row][col];
                prize2DArray[row][col] = temp;
            }

            rowIndex_1 = row;
            rowIndex_2 = randomIndex;
        }

        //如果交换的两行中有一行其中有重复元素,那么需要“回退之前的交换动作”,并且再次随机交换。
        //为什么?
        //因为随机出的行数randomIndex可能和row相同。
        //那么可能出现
        //1.两行数字交换后，出现某一行中有两个相同数字,通过函数检测出randomIndex和row行中有相同的数字
        //2.此时再次进入循环,随机出的randomIndex和row已经和原来不同,此时可能检测不出原本的randomIndex和row行有相同数字
        bool row1Duplicate = hasDuplicates<QVector<quint8>>(prize2DArray[rowIndex_1]);
        bool row2Duplicate = hasDuplicates<QVector<quint8>>(prize2DArray[rowIndex_2]);
        if(row1Duplicate || row2Duplicate){
            quint8 temp = prize2DArray[rowIndex_1][col];
            prize2DArray[rowIndex_1][col] = prize2DArray[rowIndex_2][col];
            prize2DArray[rowIndex_2][col] = temp;
            continue;
        }


        //否则对下一行进行检查
        else{
            qDebug() << "序号:" << rowIndex_1 << " " << rowIndex_2 << "\n";
            writeQVectorToTextFile(prize2DArray[rowIndex_1],"log_findError",row1Duplicate);
            writeQVectorToTextFile(prize2DArray[rowIndex_2],"log_findError",row2Duplicate);
            appendTextToFile("log_findError","No one row has Duplicate");
            col++;
        }

    }
}


void RandomShuffleWgt::shuffleByCol(int rowCount,const QList<quint8> fixedNum,QVector<QString> &issue_num,QVector<QVector<quint8>> &prize2DArray)
{
    //检验表中是否有数据
    if (p_parentDataTable->rowCount() == 0 || p_parentDataTable->columnCount() == 0) {
        QMessageBox::warning(nullptr, tr("警告"), tr("表中无数据"));
    }

    //遍历表中数据转化为一个一维数组(期数)和一个二维数组(奖注数据)
    TraversalTable(issue_num,prize2DArray,p_parentDataTable,rowCount);

    //对二维数组洗牌(每一列中的各个元素随机调换)
    shuffling2DArrayByCol(prize2DArray,fixedNum);
}
