#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QPoint>

class MyTableWidget : public QTableWidget {
    Q_OBJECT
public:
    explicit MyTableWidget(QWidget *parent = nullptr);

private slots:
    void showContextMenu(const QPoint &pos);
    void copyAllData();  // 新的复制全部数据槽函数
};


#endif // MYTABLEWIDGET_H
