#pragma once
#include "colSortTbv/colSortTbv.h"

//枚举类型放到单独头文件中增加可复用性
#include "ModType.h"

class ColSortTbv_3Mode:public ColSortTbv{
    Q_OBJECT
public:

    ColSortTbv_3Mode(QWidget *parent = nullptr);
    ~ColSortTbv_3Mode();

    //修改成员变量 m_currentMode
    void setMode(ModType newMode);

    // 返回成员变量 m_currentMode
    ModType getMode() const;

    // // 重写数据输入函数，根据模式处理
    void inputAndSortData_3Mode(const QVector<slctTbRow> &dataNormal,
                                 const QVector<slctTbRow> &dataNeighbor,
                                 const QVector<slctTbRow> &dataMix);


private:
    ModType m_currentMode;

};


