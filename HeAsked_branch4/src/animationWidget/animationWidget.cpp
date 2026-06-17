#include "animationWidget.h"

AnimationWidget::AnimationWidget(QWidget* parent,QWidget* widget):
    QWidget(parent)
    ,subWgt(widget)
{

    //this->setAttribute(Qt::WA_TransparentForMouseEvents);

    //为传入的窗口设置父控件，设置为AnimationWidget
    subWgt->setParent(this);

    //创建动画类
    animation = new QPropertyAnimation(subWgt, "pos");

    //此处不用QVBoxLayout布局，因为subWgt在resizeEvent中用resize和move去确定其位置


    //如果鼠标在右上角,触发mouseEnteredCorner
    connect(this, &AnimationWidget::mouseIn, this, [=]{
        popup();
    });

    //如果鼠标不在右上角,触发mouseLeaveCorner
    connect(this, &AnimationWidget::mouseOut, this, [=](){
        collapse();
    });
}

AnimationWidget::~AnimationWidget()
{
    delete  animation;
}


void AnimationWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    //为了能够从public函数正确获取BtnAnimationWidget的大小
    wgtWidth = this->width();

    //设置topBottomWidget隐藏位置的坐标
    hidePos = QPoint(2*wgtWidth,0);

    //设置topBottomWidget显形位置的坐标
    showPos = QPoint(0,0);

    subWgt->resize(this->size());

    subWgt->move(hidePos);

}

void AnimationWidget::popup()
{

    // 设置动画的起始值和结束值
    animation->setStartValue(hidePos);
    animation->setEndValue(showPos);

    // 设置动画的时长为300ms
    animation->setDuration(400);

    // 开始动画
    animation->start();

}

void AnimationWidget::collapse()
{
    // 设置动画的起始值和结束值
    animation->setStartValue(showPos);
    animation->setEndValue(hidePos);

    // 设置动画的时长为300ms
    animation->setDuration(400);

    // 开始动画
    animation->start();
}


