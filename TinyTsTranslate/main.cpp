#include "TinyTsTranslate.h"
#include <QtWidgets/QApplication>
#include <codecvt>
#include <locale>
#include <iostream>
#include <QMessagebox>
int main(int argc, char *argv[])
{
    system("chcp 65001");//更改控制台代码页
    std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
    std::locale::global(utf8_locale);
    std::wcout.imbue(std::locale(std::locale("Chinese"), new std::codecvt_utf8<wchar_t>)); //支持wcout输出
    QApplication a(argc, argv);
    a.setFont(QFont("Microsoft Yahei", 13));
    QMessageBox::warning(nullptr, "警告", "该程序为测试版本，记得备份原数据，造成损失概不负责 ");
    TinyTsTranslate w;
    w.show();
    return a.exec();
}
