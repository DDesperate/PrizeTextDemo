#include "widget.h"
QString Widget::prizeListToString(const QList<quint8> &list)
{
    QStringList stringList;
    for (quint8 value : list) {
        stringList.append(QString::number(value).rightJustified(2,'0'));
    }
    QString result = stringList.join(" ");
    return result;
}
