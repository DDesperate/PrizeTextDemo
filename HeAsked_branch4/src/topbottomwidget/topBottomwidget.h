#ifndef TOPBOTTOMWIDGET_H
#define TOPBOTTOMWIDGET_H

#include <QDebug>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include "imageResizableButton/imageResizableButton.h"

//一个Widget，其中包含两个btn
class TopBottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopBottomWidget(QWidget *parent = nullptr);
    ImageResizableButton *btnUp;
    ImageResizableButton *btnDown;
    QVBoxLayout *vLay;
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // TOPBOTTOMWIDGET_H
