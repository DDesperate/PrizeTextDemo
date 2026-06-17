QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrizeTestDemo5
TEMPLATE = app

HEADERS += \
    mainwindow.h \
    prizetableview.h \
    selectdatadelegate.h \
    dataprocessdialog.h \
    downstruct.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    prizetableview.cpp \
    selectdatadelegate.cpp \
    dataprocessdialog.cpp
