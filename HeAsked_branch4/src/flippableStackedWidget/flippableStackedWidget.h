#ifndef FLIPPABLESTACKEDWIDGET_H
#define FLIPPABLESTACKEDWIDGET_H

#include <QWidget>
#include <QStackedWidget>

class FlippableStackedWidget : public QStackedWidget
{
    Q_OBJECT

    Q_PROPERTY(float RotateValue READ getfRotateValue WRITE setRotateValue)
    //解释:
    //float: 指定属性的类型为float。
    //RotateValue: 属性的名称。
    //READ getfRotateValue: 定义了一个成员函数getfRotateValue()，该函数用于读取属性值。
    //WRITE setRotateValue: 定义了一个成员函数setRotateValue()，该函数用于设置属性值。
    //通过添加这个Q_PROPERTY宏，我们可以在FlippableStackedWidget的实例上使用RotateValue属性，通过调用setRotateValue()函数设置属性值，以及使用getfRotateValue()函数读取属性值。
    //这使得我们可以通过属性操作机制来控制旋转角度m_fRotateValue的值，并进一步与动画效果相关联。

    //FlippableStackedWidget::animation函数中有下述语句
    //QPropertyAnimation* pAnimation=new QPropertyAnimation(this,"RotateValue",this);
    //其中的RotateValue就是这里定义的
public:
    FlippableStackedWidget(QWidget *parent = nullptr);
    ~FlippableStackedWidget();
    //动画效果
    void animation(int currentIndex,int nextIndex);

    //设置角度
    inline void setRotateValue(float fRotateValue){m_fRotateValue=fRotateValue;}

    //读取角度
    inline float getfRotateValue(){return m_fRotateValue;}

    //设置缩放到最小时的角度
    inline void setMinScale(float minScale){m_minScale = minScale;}

    //设置开始角度与结束角度
    inline void setStartValue(float fStart){m_fStart=fStart;}
    inline void setEndValue(float fEnd){m_fEnd=fEnd;}
private:
    //页面1截图
    QPixmap m_page1;

    //页面2截图
    QPixmap m_page2;

    //旋转角度
    float m_fRotateValue;

    //开始角度，结束角度
    float m_fStart,m_fEnd;

    //图片缩放到最小时的比例(初始化为0.7)
    float m_minScale = 0.7f;

    //当前的页面索引(初始化为0)
    int cIndex = 0;

    //下一页面索引(初始化为1)
    int nIndex = 1;

private slots:
    //角度变化时触发
    void onValueChanged(const QVariant &value);

    //动画完成时触发
    void onFinished();
protected:
    //动画触发时每转过一定角度触发
    void paintEvent(QPaintEvent*evt);
};

#endif // FLIPPABLESTACKEDWIDGET_H
