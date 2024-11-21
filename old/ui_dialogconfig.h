/********************************************************************************
** Form generated from reading UI file 'dialogconfig.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCONFIG_H
#define UI_DIALOGCONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogConfig
{
public:
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QPushButton *pushButton_save;
    QLineEdit *lineEdit;
    QLabel *label;

    void setupUi(QDialog *DialogConfig)
    {
        if (DialogConfig->objectName().isEmpty())
            DialogConfig->setObjectName(QStringLiteral("DialogConfig"));
        DialogConfig->resize(1048, 480);
        gridLayout = new QGridLayout(DialogConfig);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tableWidget = new QTableWidget(DialogConfig);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setSortingEnabled(true);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->horizontalHeader()->setMinimumSectionSize(30);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        gridLayout->addWidget(tableWidget, 0, 0, 1, 4);

        pushButton_save = new QPushButton(DialogConfig);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

        gridLayout->addWidget(pushButton_save, 1, 1, 1, 1);

        lineEdit = new QLineEdit(DialogConfig);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEchoMode(QLineEdit::Password);
        lineEdit->setCursorMoveStyle(Qt::VisualMoveStyle);

        gridLayout->addWidget(lineEdit, 1, 3, 1, 1);

        label = new QLabel(DialogConfig);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 1, 2, 1, 1);


        retranslateUi(DialogConfig);

        QMetaObject::connectSlotsByName(DialogConfig);
    } // setupUi

    void retranslateUi(QDialog *DialogConfig)
    {
        DialogConfig->setWindowTitle(QApplication::translate("DialogConfig", "C\303\240i \304\221\341\272\267t tham s\341\273\221", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("DialogConfig", "Tham s\341\273\221", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("DialogConfig", "Gi\303\241 tr\341\273\213", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("DialogConfig", "Save", Q_NULLPTR));
        lineEdit->setInputMask(QString());
        label->setText(QApplication::translate("DialogConfig", "Nh\341\272\255p m\341\272\255t kh\341\272\251u \304\221\341\273\203 l\306\260u b\341\272\243ng tham s\341\273\221:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogConfig: public Ui_DialogConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCONFIG_H
