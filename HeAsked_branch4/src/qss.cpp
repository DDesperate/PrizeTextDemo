#include "qss.h"

QString radioBtnStyle =
        "QRadioButton{"
        "spacing: 5px;"
        "border: 0px;"
        "color: black;"
        "}"
        "QRadioButton::indicator {"
        "width: 20;"
        "height: 20px;"
        "}"
        "QRadioButton::indicator:checked {"
        "image: url(:/images/radioBtn-on.png);"
        "}"
        "QRadioButton::indicator:unchecked {"
        "image: url(:/images/radioBtn-off.png);"
        "}";

QString lcdStyle =
        "QLCDNumber{"
        "background-color: rgb(255, 255, 255);"
        "border: 2px solid rgb(113, 113, 113);"
        "border-radius: 5px;"
        "color: rgb(255, 0, 0);"
        "}";

QString lineEdtStyle =
        "QLineEdit {"
        "border: 2px solid gray;"
        "border-radius: 5px;"
        "selection-background-color: darkgray;"
        "}";

QString spinBoxStyle =
        "QSpinBox {"
        "padding-right: 15px;"
        "border:2px solid grey;"
        "border-radius:5px;"
        "}"

        "QSpinBox::up-button {"
        "border-image:url(:/images/black-triangle-up.png)"
        "}"

        "QSpinBox::up-button:hover {"
        "border-image:url(:/images/grey-triangle-up.png)"
        "}"

        "QSpinBox::up-button:pressed {"
        "border-image:url(:/images/red-triangle-up.png)"
        "}"

        "QSpinBox::down-button {"
        "border-image:url(:/images/black-triangle-down.png)"
        "}"

        "QSpinBox::down-button:hover {"
        "border-image:url(:/images/grey-triangle-down.png)"
        "}"

        "QSpinBox::down-button:pressed {"
        "border-image:url(:/images/red-triangle-down.png)"
        "}";

QString buttonStyle =
        "QPushButton {"
        "min-width: 100px;"
        "min-height: 23px;"
        "border: 2px solid #8f8f91;"
        "border-radius: 5px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                  stop: 0 #f6f7fa, stop: 1 #dadbde);"
        "}"
        "QPushButton:pressed {"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                  stop: 0 #dadbde, stop: 1 #f6f7fa);"
        "}"
        "QPushButton:flat {"
        "border: none;"
        "}"
        "QPushButton:default {"
        "border-color: navy;"
        "}";

QString comparePageButtonStyle =
        "QPushButton {"
        "min-width: 50px;"
        "min-height: 16px;"
        "border: 2px solid #8f8f91;"
        "border-radius: 5px;"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                  stop: 0 #f6f7fa, stop: 1 #dadbde);"
        "}"
        "QPushButton:pressed {"
        "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                  stop: 0 #dadbde, stop: 1 #f6f7fa);"
        "}"
        "QPushButton:flat {"
        "border: none;"
        "}"
        "QPushButton:default {"
        "border-color: navy;"
        "}";

QString toolBtnStyle =
        "QToolButton {"
        "    min-width: 100px;"
        "    min-height: 23px;"
        "    border: 2px solid #8f8f91;"
        "    border-radius: 5px;"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                      stop: 0 #f6f7fa, stop: 1 #dadbde);"
        "}"
        "QToolButton:pressed {"
        "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                      stop: 0 #dadbde, stop: 1 #f6f7fa);"
        "}"
        "QToolButton:flat {"
        "    border: none;"
        "}"
        "QToolButton:default {"
        "    border-color: navy;"
        "}"
        "QToolButton#inputEdt {"
        "    /* 使用空样式以排除该控件 */"
        "}";

QString modeWidgetStyle =
        "QWidget {"
        "border-radius: 10px;"
        "border: 2px solid grey;"
        "background-color: #F5F5F5;"
        "}";

QString tabWidgetStyle=
        "QTabWidget::pane {"
        "   border-top: 2px solid #C2C7CB;"
        "}"

        "QTabWidget::tab-bar {"
        "    left: 5px;"
        "}"


        "QTabBar::tab {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,"
        "                                stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);"
        "    border: 2px solid #C4C4C3;"
        "    border-bottom-color: #C2C7CB; /* same as the pane color */"
        "    border-top-left-radius: 4px;"
        "    border-top-right-radius: 4px;"
        "    min-width: 8ex;"
        "    padding: 2px;"
        "}"

        "QTabBar::tab:selected, QTabBar::tab:hover {"
        "    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
        "                                stop: 0 #fafafa, stop: 0.4 #f4f4f4,"
        "                                stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);"
        "}"

        "QTabBar::tab:selected {"
        "    border-color: #9B9B9B;"
        "    border-bottom-color: #C2C7CB; /* same as pane color */"
        "}"

        "QTabBar::tab:!selected {"
        "    margin-top: 2px;"
        "}"

        "QTabBar::tab:selected {"
        "    margin-left: -4px;"
        "    margin-right: -4px;"
        "}"

        "QTabBar::tab:first:selected {"
        "    margin-left: 0; "
        "}"

        "QTabBar::tab:last:selected {"
        "    margin-right: 0; "
        "}"

        "QTabBar::tab:only-one {"
        "    margin: 0; "
        "}";

QString tabWidgetQss =
        "QTabWidget {"
        "    background-color: #F5F5F5;"
        "    border-radius: 8px;"
        "}"

        "QTabBar::tab {"
        "    background-color: #E0E0E0;"
        "    color: #333333;"
        "    border: 1px solid #AAAAAA;"
        "    border-top-left-radius: 8px;"
        "    border-top-right-radius: 8px;"
        "    padding: 8px;"
        "}"

        "QTabBar::tab:selected {"
        "    background-color: #D1D1D1;"
        "    border-bottom: 1px solid #D1D1D1;"
        "}"

        "QTabBar::tab:!selected:hover {"
        "    background-color: #D1D1D1;"
        "}"

        "QTabWidget::pane {"
        "    border: 1px solid #AAAAAA;"
        "    background-color: #F5F5F5;"
        "    border-bottom-left-radius: 8px;"
        "    border-bottom-right-radius: 8px;"
        "}"
        ;

