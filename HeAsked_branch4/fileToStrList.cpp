#include "widget.h"
#include <QFileDialog>
QStringList Widget::fileToStrList()
{
    QStringList strListData;
    //文件名
    QString fileName;
    fileName = QFileDialog::getOpenFileName(nullptr, "Open txt", QDir::homePath(), "Txt (*.txt)");
    //打开文件（导入文件能否为gbk）
    QFile File(fileName);
    //判断文件是否存在,是否打开成功
    if ( ! File.exists() ||! File.open(QIODevice::ReadOnly | QIODevice::Text)) { //QIODevice::Text会导致所有的换行符被转换为'\n'，即'\r','\r\n'等都会被转换为\n
        //qDebug() << "files doesn't exist or open file failed";
        return strListData;
    }

    //读取txt中的数据为字节码放到byteData中
    QByteArray byteData = File.readAll();

    //关闭文件
    File.close();

    //强转字节码为QString
    QString strData(byteData);

    //将表中的数据掐头去尾空格后通过"\n"分割开
    strListData = strData.trimmed().split("\n");//trimmed导致最后多有几个换行也不会导入失败

    return strListData;
}
