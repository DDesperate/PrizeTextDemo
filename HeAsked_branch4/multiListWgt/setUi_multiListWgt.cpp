#include "multiListWgt.h"
void MultiListWidget::setUi_multiListWgt(QWidget *widget)
{
    // 创建一个QScrollArea对象
    QScrollArea *scrollArea = new QScrollArea(widget);
    scrollArea->setWidgetResizable(true); // 设置滚动区域的大小可变

    // 创建一个内部QWidget用于存放表格
    QWidget *scrollAreaWidgetContents = new QWidget();
    scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));

    // 设置布局到scrollAreaWidgetContents
    layV_multiListWgt = new QVBoxLayout(scrollAreaWidgetContents);

    // 表格数量固定为10
    int list_count = 10;

    // 向窗口中插入10个表格
    for(int i = 0; i < list_count; ++i) {
        TableWithCopy* p_table_multiList = new TableWithCopy(this);
        p_table_multiList->setEnableItemColorChange(false); // 关闭选中单元格变色功能
        p_table_multiList->setEnableCopySelectedColumns(false); // 关闭"复制选中项"选项卡
        initTableWidget(p_table_multiList);
        insertEmptyRow(p_table_multiList);
        p_table_multiList->adjustHeightBasedOnRowCount();   //通过数据数量自适应size
        layV_multiListWgt->addWidget(p_table_multiList);    //表格加入布局
        tableWidgets.append(p_table_multiList); //表格指针加入指针数组，便于后续操作
    }

    // 将scrollAreaWidgetContents添加到scrollArea
    scrollArea->setWidget(scrollAreaWidgetContents);

    // 将scrollArea添加到传入的widget的布局中
    QVBoxLayout *mainLayout = new QVBoxLayout(widget);
    mainLayout->addWidget(scrollArea);

    btn_getData = new QPushButton("获取数据",this);
    mainLayout->addWidget(btn_getData);

}
