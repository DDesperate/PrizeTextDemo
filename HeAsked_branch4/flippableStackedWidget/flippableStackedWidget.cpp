#include "flippableStackedWidget.h"
#include <QPropertyAnimation>
#include <QPainter>

FlippableStackedWidget::FlippableStackedWidget(QWidget *parent):QStackedWidget(parent)
{
}

FlippableStackedWidget::~FlippableStackedWidget()
{

}

void FlippableStackedWidget::animation(int currentIndex,int nextIndex)
{
    cIndex = currentIndex;
    nIndex = nextIndex;

    //翻转动画
    QPropertyAnimation* pAnimation=new QPropertyAnimation(this,"RotateValue",this);

    //设置动画持续时间
    pAnimation->setDuration(700);

    //设置动画的移动曲线
    pAnimation->setEasingCurve(QEasingCurve::Linear);

    //设置动画起始值(旋转角度)
    pAnimation->setStartValue(m_fStart);

    //设置动画终止值(旋转角度)
    pAnimation->setEndValue(m_fEnd);

    //动画启动后的消息绑定
    //每次pAnimation的角度值RotateValue改变时，使用paint重新绘图
    connect(pAnimation,SIGNAL(valueChanged(QVariant)),this,SLOT(onValueChanged(QVariant)));
    connect(pAnimation,SIGNAL(finished()),this,SLOT(onFinished()));

    //定义一个当前页面大小的 QPixmap pix
    QPixmap pix(widget(cIndex)->size());

    //对当前页面截图
    widget(cIndex)->render(&pix);

    //获得图像赋值给m_page1
    m_page1 = pix;

    //重塑下一页面的大小(页面在显示之前默认大小`(100,30)`)
    widget(nIndex)->resize(widget(cIndex)->size());

    //对下一页面截图
    widget(nIndex)->render(&pix);

    //下一页面的图赋值给m_page2
    m_page2 = pix;

    //隐藏当前页面
    widget(cIndex)->hide();

    //开始动画
    pAnimation->start();

    //1.截图当前页面
    //2.resize下一页面
    //3.对下一页面截图
    //4.隐藏下一页面(动画播放结束时显示下一页面)
}

void FlippableStackedWidget::paintEvent(QPaintEvent *event)
{
    QStackedWidget::paintEvent(event);
    QPainter p(this);

    //QTransform是Qt图形库中的一个类，用于进行2D图形的变换和转换操作。
    //它提供了一系列的方法和函数，可以用于平移（translate）、旋转（rotate）、缩放（scale）和倾斜（shear）等操作，从而实现对图形对象的变换。
    QTransform t;

    if(m_fRotateValue>0&&m_fRotateValue<=90 || m_fRotateValue>-90&&m_fRotateValue<=0)
    {

        //设置坐标系中心为QStackedWidget的1/2处
        t.translate(width()/2,0);

        //坐标系的y轴旋转m_fRotateValue度
        t.rotate(m_fRotateValue,Qt::YAxis);

        //根据动画播放的角度调整缩放比例
        qreal scale = m_minScale + (1 - m_minScale) * (90 - qAbs(m_fRotateValue)) / 90;

        // 按照scale缩放图片
        t.scale(scale, scale);

        //把QTransform的效果用QPainter画出来
        p.setTransform(t);

        //按照改变后的坐标系
        //图片位置应位于:(-1*width()/2,0)
        p.drawPixmap(-1*width()/2,0,m_page1);
    }
    else if(m_fRotateValue>90&&m_fRotateValue<=180 || m_fRotateValue>=-180&&m_fRotateValue<-90)
    {
        //同上
        t.translate(width()/2,0);
        t.rotate(m_fRotateValue+180,Qt::YAxis);
        qreal scale = m_minScale + (1 - m_minScale) * (qAbs(m_fRotateValue) - 90) / 90;
        t.scale(scale, scale);
        p.setTransform(t);
        p.drawPixmap(-1*width()/2,0,m_page2);
    }

}


void FlippableStackedWidget::onValueChanged(const QVariant &value)
{
    repaint();
}

void FlippableStackedWidget::onFinished()
{
    //动画播放完成，切换到下一页面
    setCurrentIndex(nIndex);

    // 删除创建的QPropertyAnimation对象，进行内存管理
    QPropertyAnimation* pAnimation = qobject_cast<QPropertyAnimation*>(sender());
    if (pAnimation)
    {
        pAnimation->deleteLater();
    }
}
