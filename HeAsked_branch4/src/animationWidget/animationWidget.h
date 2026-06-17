#ifndef BTNANIMATIONWIDGET_H
#define BTNANIMATIONWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPropertyAnimation>
#include "topbottomwidget/topBottomwidget.h"


class AnimationWidget:public QWidget
{
    Q_OBJECT
public:
    AnimationWidget(QWidget* parent,QWidget* widget);
    ~AnimationWidget() override;
    int getWidth(){return  wgtWidth;}

protected:
    void resizeEvent(QResizeEvent* event) override;
    void enterEvent(QEvent *event) override { Q_UNUSED(event) emit mouseIn();}
    void leaveEvent(QEvent *event) override { Q_UNUSED(event) emit mouseOut();}
private:
    int wgtWidth;   //宽度
    QPoint hidePos;
    QPoint showPos;
    QWidget* subWgt;
    QPropertyAnimation *animation;

    void popup();
    void collapse();
signals:
    void mouseIn();
    void mouseOut();
};

#endif // BTNANIMATIONWIDGET_H
