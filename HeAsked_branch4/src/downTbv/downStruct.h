#ifndef DOWNSTRUCT_H
#define DOWNSTRUCT_H

#include<QString>
#include<QColor>

typedef struct {
    QColor color;
    quint8 prize;
    bool isSelect;
    bool isDeleted;

    void setSelected(){
        //只有该项没有被划掉时才能被选中
        if(isDeleted != true)
            isSelect = true;
    }

    void switchSelect() {
        isSelect = !isSelect;
        if (isSelect) {
            isDeleted = false;
        }
    }

    void setDeleted(bool value) {
        isDeleted = value;
        if (isDeleted) {
            isSelect = false;
        }
    }
}slcInfo;

typedef struct{
    bool isSelected;
    QString date;
    QList<slcInfo> prizes;
}slctTbRow;

#endif
