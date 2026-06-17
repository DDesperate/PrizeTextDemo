#ifndef MODEWIDGET_H
#define MODEWIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QButtonGroup>

//用在下表中的子窗口
//当中有三个QRadioButton
//用于选择三种模式
class ModeWidget:public QWidget
{
public:
    ModeWidget(QWidget *parent = nullptr);
    QButtonGroup* group;
    QRadioButton* mixMode;
    QRadioButton* repeatMode;
    QRadioButton* neighborMode;

private:
    QVBoxLayout *vLay;
};

#endif // MODEWIDGET_H
