#include <QSize>
#include "topBottomwidget.h"


//TopBottomWidget中放置一个垂直布局
//其中设置两个正方形的按钮
//由于按钮放置于布局中，所以大小随窗口变而变化
TopBottomWidget::TopBottomWidget(QWidget *parent) : QWidget(parent)
{
    //设置布局
    vLay = new QVBoxLayout(this);
    btnUp = new ImageResizableButton(this);
    btnDown = new ImageResizableButton(this);
    vLay->addWidget(btnUp);
    vLay->addWidget(btnDown);

    //设置样式表
    QString btnStyle =
            "QPushButton {"
            "border-radius: 5px;"   //如果设置得过大，也会变成直角
            "}"
            "QPushButton {"
            "background-color: #ffffff;"
            "border: 1px solid #008CBA;"
            "color: white;"
            "}"

            "QPushButton:hover {"
            "background-color: #e0eef9;"
            "border: 1px solid #00595e;"
            "color: white;"
            "}"

            "QPushButton:pressed {"
            "background-color: #cce4f7;"
            "border: 1px solid #002433;"
            "color: white;"
            "}";
    btnUp->setStyleSheet(btnStyle);
    btnDown->setStyleSheet(btnStyle);

    //设置图片
    btnUp->setPixmap(":/images/up-arrow_32-32.png");
    btnDown->setPixmap(":/images/down-arrow_32-32.png");


}

//保证按钮为正方形
void TopBottomWidget::resizeEvent(QResizeEvent *event){
    QWidget::resizeEvent(event);

    btnUp->setFixedSize(this->width()-15,this->width()-15);
    btnDown->setFixedSize(this->width()-15,this->width()-15);
}
