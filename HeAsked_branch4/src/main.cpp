#include "widget.h"
#include <QDesktopWidget>
#include <QFontDatabase>
#include <QStyle>
#include <QApplication>



QFont aliFont;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //加载字体
    int id = QFontDatabase::addApplicationFont(":/AlibabaPuHuiTi-3-55-Regular/AlibabaPuHuiTi-3-55-Regular.ttf");
    if (id != -1) // 如果成功添加了字体文件
    {
        QStringList familyNames = QFontDatabase::applicationFontFamilies(id);
        aliFont =  familyNames.at(0);
        aliFont.setPointSize(10);
    }

    //创建窗口w
    Widget w;

    //将窗口w设置到屏幕中心
    w.setGeometry(
                QStyle::alignedRect(
                    Qt::LeftToRight,
                    Qt::AlignCenter,
                    w.size(),
                    QApplication::desktop()->availableGeometry()
                    )
                );

    //显示窗口w
    w.show();
    return a.exec();
}
