#include "TinyTsTranslate.h"
#include <QFiledialog>
#include <QPushButton>
#include <QMessageBox>
#include <QString>

#include <iostream>
#include "Translate.h"
TinyTsTranslate::TinyTsTranslate(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.languageBox->addItem(QString("English"));
    ui.languageBox->addItem(QString("Chinese"));
    ui.languageBox->addItem(QString("Japanese"));
    ui.languageBox->addItem(QString("French"));
    ui.languageBox->addItem(QString("German"));
    QString pl("Polish");
    ui.languageBox->addItem(pl);
    connect(ui.selectFile, &QPushButton::clicked, [this]() {
        QString file = QFileDialog::getOpenFileName(nullptr, u8"选择文件", "", "所有文件 (*.*)");
        ui.filepath->setText(file);
    });
    connect(ui.generate, &QPushButton::clicked, this, &TinyTsTranslate::generate);
}

TinyTsTranslate::~TinyTsTranslate()
{}

void TinyTsTranslate::generate() {
    if (ui.filepath->text().isEmpty()) {
        QMessageBox::warning(nullptr, u8"警告", u8"文件地址为空！");
        return;
    }
    if (ui.appID->text().isEmpty()) {
        QMessageBox::warning(nullptr, u8"警告", u8"应用ID为空！");
        return;
    }
    if (ui.lineEdit_2->text().isEmpty()) {
        QMessageBox::warning(nullptr, u8"警告", u8"密钥为空！");
        return;
    }
    tw::Translate t(ui.filepath->text().toStdString()
        , ui.appID->text().toStdString()
        , ui.lineEdit_2->text().toStdString()
        , ui.languageBox->currentText().toStdString()
        , true);
    tw::TWResult::emResult twts = t.start();
    switch (twts) {
    case tw::TWResult::RESULT_SUCCESS: {
        int suc = t.getTranslateSuccessCount();
        int fai = t.getTranslateFailCount();
        std::string msg = "success:" + std::to_string(suc) + " fail:" + std::to_string(fai);
        QMessageBox::information(nullptr, u8"成功", QString(msg.c_str()));
        break;
    }
    case tw::TWResult::RESULT_LOADFILEERROR: {
        QMessageBox::warning(nullptr, u8"错误", u8"翻译文件加载错误！");
        break;
    }
    case tw::TWResult::RESULT_SAVETXTFILEERROR: {
        QMessageBox::warning(nullptr, u8"错误", u8"（bug）保存txt地址错误！");
        break;
    }
    case tw::TWResult::RESULT_SAVEFILEERROR: {
        QMessageBox::warning(nullptr, u8"错误", u8"保存翻译后的文件错误！");
        break;
    }
    case tw::TWResult::RESULT_FAIL: {
        QMessageBox::warning(nullptr, u8"错误", u8"bug错误！");
        break;
    }
    }
}
