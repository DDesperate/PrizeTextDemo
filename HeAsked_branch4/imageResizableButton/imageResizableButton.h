#ifndef IMAGERESIZABLEBUTTON_H
#define IMAGERESIZABLEBUTTON_H

#include <QDebug>
#include <QPushButton>
#include <QPainter>

//按钮(其中资源图片可以随按钮大小随意缩放)
class ImageResizableButton :public QPushButton
{
    Q_OBJECT
public:
    explicit ImageResizableButton(QWidget* parent = nullptr)
        : QPushButton(parent)
    {
        setStyleSheet("background: transparent;");
        setAttribute(Qt::WA_TranslucentBackground);
    }

    //设置btn中的图片
    void setPixmap(const QString& filename);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    QPixmap pic;  //image resize pixmap
};

#endif // IMAGERESIZABLEBUTTON_H
