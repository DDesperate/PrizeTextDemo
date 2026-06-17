#include "colSortTbv_3mode.h"

//构造函数：初始化成员变量
ColSortTbv_3Mode::ColSortTbv_3Mode(QWidget *parent)
    : ColSortTbv(parent), m_currentMode(ModType::ModeNormal) // 在初始化列表中设置默认模式
{
    // 构造函数体可以为空
}

ColSortTbv_3Mode::~ColSortTbv_3Mode() {
    // 析构函数
}

void ColSortTbv_3Mode::setMode(ModType newMode) {
    m_currentMode = newMode; // 将传入的值赋给成员变量
    qDebug() << "模式已切换至:" << static_cast<int>(m_currentMode); // 可选：用于调试
}

ModType ColSortTbv_3Mode::getMode() const {
    return m_currentMode; // 返回成员变量的当前值
}

void ColSortTbv_3Mode::inputAndSortData_3Mode(const QVector<slctTbRow> &dataNormal,
                                              const QVector<slctTbRow> &dataNeighbor,
                                              const QVector<slctTbRow> &dataMix)
{
    // switch (m_currentMode) { // 使用 switch 语句比 if-else 链更清晰
    // case ModType::ModeNormal:
    //     qDebug() << "ColSortTbv_3Mode: 使用 ModeNormal 处理数据";
    //     ColSortTbv::inputAndSortData(dataNormal); // 调用父类逻辑处理普通数据
    //     break;

    // case ModType::ModeNeighbor:
    //     qDebug() << "ColSortTbv_3Mode: 使用 ModeNeighbor 处理数据";
    //     ColSortTbv::inputAndSortData(dataNeighbor); // 调用父类逻辑处理邻居数据
    //     break;

    // case ModType::ModeMix:
    //     qDebug() << "ColSortTbv_3Mode: 使用 ModeMix 处理数据";
    //     ColSortTbv::inputAndSortData(dataMix); // 调用父类逻辑处理混合数据
    //     break;

    // default:
    //     qWarning() << "ColSortTbv_3Mode: 未知的模式，将使用默认模式处理";
    //     ColSortTbv::inputAndSortData(dataNormal);
    //     break;
    // }
}

