#include "widget.h"

void Widget::showContextMenu(const QPoint &pos){
    QMenu menu(dataTable);
    QAction *action_copy = menu.addAction("复制选中项");

    //connect(action_copy,&QAction::triggered,this,&Widget::copySelectedItem);
    connect(action_copy,&QAction::triggered,[=]{
        copySelectedItem(dataTable);
    });

    menu.exec(dataTable->viewport()->mapToGlobal(pos));


}
