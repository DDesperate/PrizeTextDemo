#ifndef TOOLBUTTONAUTOPOPUP_H
#define TOOLBUTTONAUTOPOPUP_H

#include <QDebug>
#include <QToolButton>
#include <QMenu>
#include <QMouseEvent>
class ToolButtonAutoPopup:public QToolButton
{
public:
    ToolButtonAutoPopup(QWidget *parent = nullptr) : QToolButton(parent)
    {
        setPopupMode(QToolButton::InstantPopup);
        setMouseTracking(true);

    }
protected:
    void leaveEvent(QEvent *event) override
    {
        QToolButton::leaveEvent(event);
        QMenu *menu = QToolButton::menu();
        if (menu && menu->isVisible()) {
            menu->hide();
        }
        qDebug() << "leave";
    }
};

#endif // TOOLBUTTONAUTOPOPUP_H
