/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "testview.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    TestView *widget;
    QPushButton *setTestData1Button;
    QPushButton *setSampleDataButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(256, 132);
        widget = new TestView(Widget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(20, 60, 211, 51));
        setTestData1Button = new QPushButton(Widget);
        setTestData1Button->setObjectName(QStringLiteral("setTestData1Button"));
        setTestData1Button->setGeometry(QRect(20, 20, 101, 23));
        setSampleDataButton = new QPushButton(Widget);
        setSampleDataButton->setObjectName(QStringLiteral("setSampleDataButton"));
        setSampleDataButton->setGeometry(QRect(130, 20, 101, 23));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        setTestData1Button->setText(QApplication::translate("Widget", "setTestData1", Q_NULLPTR));
        setSampleDataButton->setText(QApplication::translate("Widget", "setSampleData", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
