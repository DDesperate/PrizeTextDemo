#include "TwoStepVerificationWgt.h"
#include "qss.h"
void TwoStepVerificationWgt::setUi_twoStepVerificationWgt(QWidget *Widget)
{
    if (Widget->objectName().isEmpty())
        Widget->setObjectName(QString::fromUtf8("二次对比"));

    Widget->resize(800, 600);

    //new
    main_VLayout = new QVBoxLayout(Widget);
    input_HLayout = new QHBoxLayout();
    leftInput_VLayout = new QVBoxLayout();
    rightInput_VLayout = new QVBoxLayout();
    leftInput_setting_HLayout = new QHBoxLayout();
    rightInput_setting_HLayout = new QHBoxLayout();
    leftInput_setting_spinBox = new QSpinBox(Widget);
    leftInput_setting_confirmBtn = new QPushButton("确定",Widget);
    leftInput_text = new QPlainTextEdit(Widget);
    rightInput_setting_spinBox = new QSpinBox(Widget);
    rightInput_setting_confirmBtn = new QPushButton("确定",Widget);
    rightInput_text = new QPlainTextEdit(Widget);
    progressBar = new QProgressBar(Widget);
    output_HLayout = new QHBoxLayout();
    output_limitQuantity_VLayout = new QVBoxLayout();
    output_allResult_VLayout = new QVBoxLayout();
    output_limitQuantity_setting_HLayout = new QHBoxLayout();
    output_allResult_setting_HLayout = new QHBoxLayout();
    output_limitQuantity_spinBox = new QSpinBox(Widget);
    output_limitQuantity_confirmBtn = new QPushButton("确定",Widget);
    output_limitQuantity_copyBtn = new QPushButton("复制",Widget);
    output_allResult_copyBtn = new QPushButton("复制",Widget);
    output_limitQuantity_text = new QPlainTextEdit(Widget);
    output_allResult_text = new QPlainTextEdit(Widget);

    //布局
    main_VLayout->addLayout(input_HLayout);
    input_HLayout->addLayout(leftInput_VLayout);
    input_HLayout->addLayout(rightInput_VLayout);
    leftInput_VLayout->addLayout(leftInput_setting_HLayout);
    rightInput_VLayout->addLayout(rightInput_setting_HLayout);
    leftInput_setting_HLayout->addWidget(leftInput_setting_spinBox);
    leftInput_setting_HLayout->addWidget(leftInput_setting_confirmBtn);
    leftInput_setting_HLayout->addStretch();
    leftInput_VLayout->addWidget(leftInput_text);
    rightInput_setting_HLayout->addWidget(rightInput_setting_spinBox);
    rightInput_setting_HLayout->addWidget(rightInput_setting_confirmBtn);
    rightInput_VLayout->addWidget(rightInput_text);
    rightInput_setting_HLayout->addStretch();
    main_VLayout->addWidget(progressBar);
    progressBar->setStyleSheet(progressBarQss);
    main_VLayout->addLayout(output_HLayout);
    output_HLayout->addLayout(output_limitQuantity_VLayout);
    output_HLayout->addLayout(output_allResult_VLayout);
    output_limitQuantity_VLayout->addLayout(output_limitQuantity_setting_HLayout);
    output_limitQuantity_setting_HLayout->addWidget(output_limitQuantity_spinBox);
    output_limitQuantity_setting_HLayout->addWidget(output_limitQuantity_confirmBtn);
    output_limitQuantity_setting_HLayout->addStretch();
    output_limitQuantity_setting_HLayout->addWidget(output_limitQuantity_copyBtn);
    output_limitQuantity_VLayout->addWidget(output_limitQuantity_text);
    output_allResult_VLayout->addLayout(output_allResult_setting_HLayout);
    output_allResult_setting_HLayout->addWidget(output_allResult_copyBtn);
    output_allResult_setting_HLayout->addStretch();
    output_allResult_VLayout->addWidget(output_allResult_text);




//    gridLayout = new QGridLayout(Widget);
//    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
//    verticalLayout = new QVBoxLayout();
//    verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
//    horizontalLayout = new QHBoxLayout();
//    horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
//    leftGridLayout = new QGridLayout();
//    leftGridLayout->setObjectName(QString::fromUtf8("leftGridLayout"));
//    leftHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

//    leftGridLayout->addItem(leftHorizontalSpacer, 0, 2, 1, 1);

//    leftSpinBox = new QSpinBox(Widget);
//    leftSpinBox->setObjectName(QString::fromUtf8("leftSpinBox"));

//    leftGridLayout->addWidget(leftSpinBox, 0, 0, 1, 1);

//    leftTextEdit = new QTextEdit(Widget);
//    leftTextEdit->setReadOnly(true);
//    leftTextEdit->setObjectName(QString::fromUtf8("leftTextEdit"));

//    leftGridLayout->addWidget(leftTextEdit, 1, 0, 1, 3);

//    leftConfirmBtn = new QPushButton(Widget);
//    leftConfirmBtn->setObjectName(QString::fromUtf8("leftConfirmBtn"));

//    leftGridLayout->addWidget(leftConfirmBtn, 0, 1, 1, 1);


//    horizontalLayout->addLayout(leftGridLayout);

//    rightGridLayout = new QGridLayout();
//    rightGridLayout->setObjectName(QString::fromUtf8("rightGridLayout"));
//    rightSpinBox = new QSpinBox(Widget);
//    rightSpinBox->setObjectName(QString::fromUtf8("rightSpinBox"));

//    rightGridLayout->addWidget(rightSpinBox, 0, 0, 1, 1);

//    rightConfirmBtn = new QPushButton(Widget);
//    rightConfirmBtn->setObjectName(QString::fromUtf8("rightConfirmBtn"));

//    rightGridLayout->addWidget(rightConfirmBtn, 0, 1, 1, 1);

//    rightHorizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

//    rightGridLayout->addItem(rightHorizontalSpacer, 0, 2, 1, 1);

//    rightTextEdit = new QTextEdit(Widget);
//    rightTextEdit->setReadOnly(true);
//    rightTextEdit->setObjectName(QString::fromUtf8("rightTextEdit"));

//    rightGridLayout->addWidget(rightTextEdit, 1, 0, 1, 3);


//    horizontalLayout->addLayout(rightGridLayout);


//    verticalLayout->addLayout(horizontalLayout);

//    progressBar = new QProgressBar(Widget);
//    progressBar->setObjectName(QString::fromUtf8("progressBar"));
//    progressBar->setStyleSheet(progressBarQss);

//    verticalLayout->addWidget(progressBar);

//    OkBtn = new QPushButton(Widget);
//    OkBtn->setObjectName(QString::fromUtf8("OkBtn"));

//    verticalLayout->addWidget(OkBtn);

//    resultTextEdit = new QTextEdit(Widget);
//    resultTextEdit->setReadOnly(true);
//    resultTextEdit->setObjectName(QString::fromUtf8("resultTextEdit"));

//    verticalLayout->addWidget(resultTextEdit);


//    gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

//    leftConfirmBtn->setText(QCoreApplication::translate("Widget", "确定", nullptr));
//    rightConfirmBtn->setText(QCoreApplication::translate("Widget", "确定", nullptr));
//    OkBtn->setText(QCoreApplication::translate("Widget", "二次对比", nullptr));

}
