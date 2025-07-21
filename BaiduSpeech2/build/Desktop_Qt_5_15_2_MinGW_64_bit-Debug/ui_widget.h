/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *pushButton;
    QPushButton *clearButton;
    QTextEdit *textEdit;
    QComboBox *comboBox;
    QTableWidget *tableWidget;
    QPushButton *deleteButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(879, 640);
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 430, 181, 61));
        clearButton = new QPushButton(Widget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(580, 430, 181, 61));
        textEdit = new QTextEdit(Widget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(350, 130, 441, 271));
        comboBox = new QComboBox(Widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(660, 70, 121, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        comboBox->setFont(font);
        tableWidget = new QTableWidget(Widget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(20, 100, 301, 331));
        deleteButton = new QPushButton(Widget);
        deleteButton->setObjectName(QString::fromUtf8("deleteButton"));
        deleteButton->setGeometry(QRect(60, 450, 211, 51));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        pushButton->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        clearButton->setText(QCoreApplication::translate("Widget", "\346\270\205\347\251\272", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Widget", "\346\231\256\351\200\232\350\257\235", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Widget", "\350\213\261\346\226\207", nullptr));

        deleteButton->setText(QCoreApplication::translate("Widget", "\345\210\240\351\231\244\351\200\211\344\270\255\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
