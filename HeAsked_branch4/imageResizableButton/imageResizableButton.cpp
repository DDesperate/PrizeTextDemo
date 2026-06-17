#include "imageResizableButton.h"
void ImageResizableButton::setPixmap(const QString &filename)
{
    pic.load(filename);
}

void ImageResizableButton::paintEvent(QPaintEvent *event)
{

    QPushButton::paintEvent(event);

    QPainter painter(this);

    //图片抗锯齿
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

    //获取按钮位置和大小信息
    QRect btnRect = painter.viewport();

    //获取资源图片大小
    QSize pixSize = pic.size();

    //计算出 widthRatio = 按钮宽/图片宽  heightRatio = 按钮高/图片高，取其中的较小值
    qreal widthRatio = static_cast<qreal>(btnRect.width()) / static_cast<qreal>(pixSize.width());
    qreal heightRatio = static_cast<qreal>(btnRect.height()) / static_cast<qreal>(pixSize.height());
    qreal ratio = qMin(widthRatio, heightRatio);

    //将图片大小按照比例缩小

    //按照下述方式，图片的宽高和按钮宽高的较小值对齐

    //如果直接和较小值对其会显得图片在按钮中比较挤，所以此处设置一个0.7
    pixSize.setWidth(qRound(pixSize.width() * ratio * 0.7));
    pixSize.setHeight(qRound(pixSize.height() * ratio *0.7));


    //(设置图片位于按钮中的位置和大小)
    QRect targetRect(0, 0, pixSize.width(), pixSize.height());

    //将targetRect的位置修改到按钮的中心

    //(将图片的位置设置到按钮的中心)
    targetRect.moveCenter(btnRect.center());

    //将targetRect的位置大小应用于图片上
    painter.drawPixmap(targetRect, pic);

}

void ImageResizableButton::resizeEvent(QResizeEvent *event)
{
    QPushButton::resizeEvent(event);
}
