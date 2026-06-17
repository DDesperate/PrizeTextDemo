QT       += core gui
CONFIG += c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PrizeTestDemo5
TEMPLATE = app

HEADERS += \
    downstruct.h \
    sparsestruct.h \
    dataconverter.h \
    selectdatadelegate.h \
    sparsedatadelegate.h \
    prizetableview.h \
    dataprocessdialog.h \
    mainwindow.h

SOURCES += \
    main.cpp \
    dataconverter.cpp \
    selectdatadelegate.cpp \
    sparsedatadelegate.cpp \
    prizetableview.cpp \
    dataprocessdialog.cpp \
    mainwindow.cpp
