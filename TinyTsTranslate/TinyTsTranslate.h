#pragma once

#include <QtWidgets/QMainWindow>
#include "../build/ui_TinyTsTranslate.h"

class TinyTsTranslate : public QMainWindow
{
    Q_OBJECT

public:
    TinyTsTranslate(QWidget *parent = nullptr);
    ~TinyTsTranslate();
public slots:
    void generate();
private:
    Ui_Widget ui;
};
