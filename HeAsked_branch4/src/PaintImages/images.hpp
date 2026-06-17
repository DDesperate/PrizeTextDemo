#include <QtWidgets>
#include <QColor>
QImage im_greenCircle()
{
    //设置图像分辨率12*12
    QImage image(12, 12, QImage::Format_ARGB32);
    QPainter painter(&image);

    // 设置绘制属性
    painter.setRenderHint(QPainter::Antialiasing, true);    //透明
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::green);

    // 绘制圆形
    QRectF rect(0, 0, 12, 12);
    painter.drawEllipse(rect);

    return image;
}

//红色圆
QImage im_redCircle()
{
    //设置图像分辨率12*12
    QImage image(12, 12, QImage::Format_ARGB32);
    QPainter painter(&image);

    // 设置绘制属性
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::red);

    // 绘制圆形
    QRectF rect(0, 0, 12, 12);
    painter.drawEllipse(rect);

    return image;

}

//红绿渐变圆
QImage im_MixCircle()
{
    QImage image(12, 12, QImage::Format_ARGB32);
    QPainter painter(&image);

    // 创建渐变
    painter.setRenderHint(QPainter::Antialiasing, true);

    // 绘制左上角圆
    QLinearGradient gradient(0, 0, 0, 12);
    gradient.setColorAt(0.0, Qt::green);
    gradient.setColorAt(1.0, Qt::red);

    painter.setPen(Qt::NoPen);
    painter.setBrush(gradient);

    QRectF rect(0, 0, 12, 12);
    painter.drawEllipse(rect);

    return image;

}

QImage im_ClearhighLight()
{
    QImage image(20, 20, QImage::Format_ARGB32);
    QPainter painter(&image);

    // 创建渐变
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::blue);

    // 绘制左上角圆
    {
        QRectF rect(0, 0, 5, 5);
        painter.drawEllipse(rect);
    }

    // 绘制左上角圆
    {
        QRectF rect(10, 0, 5, 5);
        painter.drawEllipse(rect);
    }

    {
        QRectF rect(5, 10, 5, 5);
        painter.drawEllipse(rect);
    }

    {
        QRectF rect(15, 10, 5, 5);
        painter.drawEllipse(rect);
    }

    return image;
}
