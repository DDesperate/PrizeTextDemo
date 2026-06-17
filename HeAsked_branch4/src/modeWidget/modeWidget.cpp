#include "modeWidget.h"
#include "widget.h"
ModeWidget::ModeWidget(QWidget* parent):QWidget(parent)
{

    //设置modeWidget中的radioBtn的布局和样式表
    vLay = new QVBoxLayout(this);

    group = new QButtonGroup(this);
    repeatMode = new QRadioButton("重号模式",this);
    neighborMode = new QRadioButton("边号模式",this);
    mixMode = new QRadioButton("混合模式",this);

    group->addButton(repeatMode);
    group->addButton(neighborMode);
    group->addButton(mixMode);

    vLay->addWidget(repeatMode);
    vLay->addWidget(neighborMode);
    vLay->addWidget(mixMode);

    //初始化为重号模式
    repeatMode->setChecked(true);

    QString radioBtnStyle =
            "QRadioButton{"
            "spacing: 5px;"
            "border: 0px;"
            "color: black;"
            "}"
            "QRadioButton::indicator {"
            "width: 20;"
            "height: 20px;"
            "}"
            "QRadioButton::indicator:checked {"
            "image: url(:/images/radioBtn-on.png);"
            "}"
            "QRadioButton::indicator:unchecked {"
            "image: url(:/images/radioBtn-off.png);"
            "}";

    QString modeWidgetStyle =
            "QWidget {"
            "border-radius: 10px;"
            "border: 2px solid grey;"
            "background-color: #F5F5F5;"
            "}";

    //这里应该还可以优化

    this->setStyleSheet(modeWidgetStyle+radioBtnStyle);
}
