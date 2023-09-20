/********************************************************************************
** Form generated from reading UI file 'TinyTsTranslate.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TINYTSTRANSLATE_H
#define UI_TINYTSTRANSLATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *appID;
    QLabel *password;
    QLineEdit *lineEdit_2;
    QPushButton *selectFile;
    QLineEdit *filepath;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QLabel *password_2;
    QComboBox *languageBox;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *generate;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(372, 225);
        Widget->setLayoutDirection(Qt::LeftToRight);
        widget = new QWidget(Widget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(13, 13, 347, 184));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        appID = new QLineEdit(widget);
        appID->setObjectName(QString::fromUtf8("appID"));

        gridLayout->addWidget(appID, 0, 2, 1, 3);

        password = new QLabel(widget);
        password->setObjectName(QString::fromUtf8("password"));

        gridLayout->addWidget(password, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 4);

        selectFile = new QPushButton(widget);
        selectFile->setObjectName(QString::fromUtf8("selectFile"));
        selectFile->setIconSize(QSize(16, 16));

        gridLayout->addWidget(selectFile, 2, 0, 1, 3);

        filepath = new QLineEdit(widget);
        filepath->setObjectName(QString::fromUtf8("filepath"));

        gridLayout->addWidget(filepath, 2, 3, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        password_2 = new QLabel(widget);
        password_2->setObjectName(QString::fromUtf8("password_2"));

        horizontalLayout->addWidget(password_2);

        languageBox = new QComboBox(widget);
        languageBox->setObjectName(QString::fromUtf8("languageBox"));

        horizontalLayout->addWidget(languageBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 1, 1, 2);

        generate = new QPushButton(widget);
        generate->setObjectName(QString::fromUtf8("generate"));

        gridLayout->addWidget(generate, 4, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 4, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "translate", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\345\272\224\347\224\250ID", nullptr));
        password->setText(QCoreApplication::translate("Widget", "\345\257\206\351\222\245", nullptr));
        selectFile->setText(QCoreApplication::translate("Widget", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        password_2->setText(QCoreApplication::translate("Widget", "\350\257\255\350\250\200", nullptr));
        generate->setText(QCoreApplication::translate("Widget", "\345\274\200\345\247\213\347\224\237\346\210\220", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TINYTSTRANSLATE_H
