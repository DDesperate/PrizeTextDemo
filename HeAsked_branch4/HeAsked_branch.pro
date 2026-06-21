QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#使用msvc时采用utf-8字符编码
msvc{
    QMAKE_CXXFLAGS += -utf-8
}

include($$PWD/SimulateLotteryDialog/SimulateLotteryDialog.pri)
include($$PWD/CheckoutWgt/CheckoutWgt.pri)
include($$PWD/randomSelectListWgt/randomSelectListWgt.pri)
include($$PWD/twoStepVerification/twoStepVerificationWgt.pri)
include($$PWD/multiListWgt/multiListWgt.pri)
include($$PWD/sortTableElementsByCountWgt/sortTableElementsByCountWgt.pri)

SOURCES += \
    colSortTbv_3mode/colSortTbv_3mode.cpp \
    addNumToExcludeList.cpp \
    animationWidget/animationWidget.cpp \
    colSortTbv/adjustHeightBasedOnRowCount_colSort.cpp \
    colSortTbv/colSortTbvDelegate.cpp \
    colSortTbv/showContexMenu_colSort.cpp \
    comparethread.cpp \
    downTbv/InsertOneRow_down.cpp \
    downTbv/clearAllDate.cpp \
    downTbv/clearHighLight.cpp \
    downTbv/copyUnDeleteNum.cpp \
    downTbv/dbClkDate_down.cpp \
    downTbv/deleteOneRow_passive.cpp \
    downTbv/deleteSelectedRow.cpp \
    downTbv/deleteVecByDate.cpp \
    downTbv/downTbv.cpp \
    downTbv/exclude.cpp \
    downTbv/getSamePrize.cpp \
    downTbv/getSelectedPrize.cpp \
    downTbv/include.cpp \
    downTbv/listSelectItem.cpp \
    downTbv/outputData.cpp \
    downTbv/outputRepeatData.cpp \
    downTbv/outputNeighborData.cpp \
    downTbv/outputMixData.cpp \
    downTbv/printSelectMixDataVec.cpp \
    downTbv/randomClearOneRow.cpp \
    downTbv/randomSelectPrizes.cpp \
    downTbv/refreshItem.cpp \
    downTbv/selectDataDelegate.cpp \
    downTbv/selectItem.cpp \
    downTbv/selectListItem.cpp \
    downTbv/selectMode.cpp \
    downTbv/showContextMenu_down.cpp \
    downTbv/strikeItem.cpp \
    downTbv/strikeSameItem.cpp \
    downTbv/structSelectedSwitch.cpp \
    fileToStrList.cpp \
    flippableStackedWidget/flippableStackedWidget.cpp \
    genericfunc.cpp \
    imageResizableButton/imageResizableButton.cpp \
    importDialog/importDialog.cpp \
    main.cpp \
    modeWidget/modeWidget.cpp \
    numLineEdit/numLineEdit.cpp \
    przTbv/clearModel.cpp \
    przTbv/prizeTableView.cpp \
    przTbv/refreshOneRow.cpp \
    qss.cpp \
    setUi.cpp \
    tableWidgetFunction/SimulatedLottery.cpp \
    tableWidgetFunction/analysisRes.cpp \
    tableWidgetFunction/checkDataExistenceForDate.cpp \
    tableWidgetFunction/cmnAnalysis.cpp \
    tableWidgetFunction/copyRow.cpp \
    tableWidgetFunction/copySelectedItem.cpp \
    tableWidgetFunction/dataStructureToText.cpp \
    tableWidgetFunction/getItemValuePurple.cpp \
    tableWidgetFunction/getSelectedIndices.cpp \
    tableWidgetFunction/getTbwSamePrize.cpp \
    tableWidgetFunction/handleModeChange.cpp \
    tableWidgetFunction/import_tbwgt.cpp \
    tableWidgetFunction/initBackGround.cpp \
    tableWidgetFunction/insertLineData.cpp \
    tableWidgetFunction/markFixedNum.cpp \
    tableWidgetFunction/mixAnalysis.cpp \
    tableWidgetFunction/neighborAnalysis.cpp \
    tableWidgetFunction/repeatAnalysis.cpp \
    tableWidgetFunction/samePrizeCmn.cpp \
    tableWidgetFunction/searchTbw.cpp \
    tableWidgetFunction/selectCombine.cpp \
    tableWidgetFunction/showContextMenu_tbwgt.cpp \
    tableWidgetFunction/shuffleSelectedColumns.cpp \
    tableWidgetFunction/shufflingByRow.cpp \
    tableWidgetFunction/simulateLotteryTable.cpp \
    tableWidgetFunction/textToDataStructure.cpp \
    tableWidgetFunction/turnTableWidgetDataToStringList.cpp \
    tableWithCopy.cpp \
    topbottomwidget/topbottomwidget.cpp \
    upTbv/checkOut.cpp \
    upTbv/clear.cpp \
    upTbv/count.cpp \
    upTbv/dbClkDate_up.cpp \
    upTbv/delegate_up.cpp \
    upTbv/delete.cpp \
    upTbv/getLastRow.cpp \
    upTbv/getRandomMap.cpp \
    upTbv/import.cpp \
    upTbv/insertOneRow.cpp \
    upTbv/refreshOneRowByDate.cpp \
    upTbv/search.cpp \
    upTbv/showContextMenu_upTbv.cpp \
    upTbv/structTransform.cpp \
    upTbv/turnDataToStringList.cpp \
    upTbv/unMarkRow.cpp \
    upTbv/upTbv.cpp \
    colSortTbv/colSortTbv.cpp\
    widget.cpp

HEADERS += \
    colSortTbv_3mode/colSortTbv_3mode.h \
    PaintImages/images.hpp \
    animationWidget/animationWidget.h \
    cmn.hpp \
    colSortTbv/colSortTbvDelegate.h \
    colSortTbv/colSortTbvStruct.h \
    comparethread.h \
    downTbv/downStruct.h \
    downTbv/downTbv.h \
    downTbv/selectDataDelegate.h \
    flippableStackedWidget/flippableStackedWidget.h \
    genericfunc.h \
    imageResizableButton/imageResizableButton.h \
    importDialog/importDialog.h \
    modType.h \
    modeWidget/modeWidget.h \
    numLineEdit/numLineEdit.h \
    przTbv/prizeTableView.h \
    qss.h \
    tableWithCopy.h \
    topbottomwidget/topBottomwidget.h \
    upTbv/dataTableDelegate.h \
    upTbv/upStruct.h \
    upTbv/upTbv.h \
    colSortTbv/colSortTbv.h\
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    font.qrc \
    images.qrc

DISTFILES += \
    build-NewAnalysis18-Desktop_Qt_5_13_2_MinGW_64_bit-Debug/.qmake.stash \
    build-NewAnalysis18-Desktop_Qt_5_13_2_MinGW_64_bit-Debug/object_script.NewAnalysis18.Debug \
    build-NewAnalysis18-Desktop_Qt_5_13_2_MinGW_64_bit-Debug/object_script.NewAnalysis18.Release \
    multiListWgt/multiList.pri.txt
