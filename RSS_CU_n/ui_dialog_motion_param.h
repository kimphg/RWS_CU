/********************************************************************************
** Form generated from reading UI file 'dialog_motion_param.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_MOTION_PARAM_H
#define UI_DIALOG_MOTION_PARAM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_motion_param
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox_setup;
    QGridLayout *gridLayout_7;
    QGroupBox *groupBox_8;
    QGridLayout *gridLayout_9;
    QLabel *label_5;
    QLabel *label_8;
    QLabel *label_7;
    QLineEdit *lineEdit_vp;
    QLabel *label_6;
    QLineEdit *lineEdit_open_loop;
    QLineEdit *lineEdit_vibration_1;
    QLabel *label_4;
    QLineEdit *lineEdit_vd;
    QLabel *label_2;
    QLineEdit *lineEdit_hd;
    QLineEdit *lineEdit_vi;
    QLineEdit *lineEdit_hp;
    QLabel *label_3;
    QLineEdit *lineEdit_hi;
    QPushButton *bt_send_pid;
    QLabel *label_9;
    QLineEdit *lineEdit_vibration_2;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;

    void setupUi(QDialog *Dialog_motion_param)
    {
        if (Dialog_motion_param->objectName().isEmpty())
            Dialog_motion_param->setObjectName(QString::fromUtf8("Dialog_motion_param"));
        Dialog_motion_param->resize(988, 376);
        gridLayout = new QGridLayout(Dialog_motion_param);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_setup = new QGroupBox(Dialog_motion_param);
        groupBox_setup->setObjectName(QString::fromUtf8("groupBox_setup"));
        groupBox_setup->setStyleSheet(QString::fromUtf8("background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)"));
        gridLayout_7 = new QGridLayout(groupBox_setup);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        groupBox_8 = new QGroupBox(groupBox_setup);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        gridLayout_9 = new QGridLayout(groupBox_8);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_5 = new QLabel(groupBox_8);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_9->addWidget(label_5, 0, 0, 1, 1);

        label_8 = new QLabel(groupBox_8);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_9->addWidget(label_8, 3, 2, 1, 1);

        label_7 = new QLabel(groupBox_8);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_9->addWidget(label_7, 3, 1, 1, 1);

        lineEdit_vp = new QLineEdit(groupBox_8);
        lineEdit_vp->setObjectName(QString::fromUtf8("lineEdit_vp"));

        gridLayout_9->addWidget(lineEdit_vp, 5, 2, 1, 1);

        label_6 = new QLabel(groupBox_8);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_9->addWidget(label_6, 1, 0, 1, 1);

        lineEdit_open_loop = new QLineEdit(groupBox_8);
        lineEdit_open_loop->setObjectName(QString::fromUtf8("lineEdit_open_loop"));

        gridLayout_9->addWidget(lineEdit_open_loop, 0, 1, 1, 1);

        lineEdit_vibration_1 = new QLineEdit(groupBox_8);
        lineEdit_vibration_1->setObjectName(QString::fromUtf8("lineEdit_vibration_1"));

        gridLayout_9->addWidget(lineEdit_vibration_1, 1, 1, 1, 1);

        label_4 = new QLabel(groupBox_8);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_9->addWidget(label_4, 9, 0, 1, 1);

        lineEdit_vd = new QLineEdit(groupBox_8);
        lineEdit_vd->setObjectName(QString::fromUtf8("lineEdit_vd"));

        gridLayout_9->addWidget(lineEdit_vd, 9, 2, 1, 1);

        label_2 = new QLabel(groupBox_8);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_9->addWidget(label_2, 5, 0, 1, 1);

        lineEdit_hd = new QLineEdit(groupBox_8);
        lineEdit_hd->setObjectName(QString::fromUtf8("lineEdit_hd"));

        gridLayout_9->addWidget(lineEdit_hd, 9, 1, 1, 1);

        lineEdit_vi = new QLineEdit(groupBox_8);
        lineEdit_vi->setObjectName(QString::fromUtf8("lineEdit_vi"));

        gridLayout_9->addWidget(lineEdit_vi, 8, 2, 1, 1);

        lineEdit_hp = new QLineEdit(groupBox_8);
        lineEdit_hp->setObjectName(QString::fromUtf8("lineEdit_hp"));

        gridLayout_9->addWidget(lineEdit_hp, 5, 1, 1, 1);

        label_3 = new QLabel(groupBox_8);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_9->addWidget(label_3, 8, 0, 1, 1);

        lineEdit_hi = new QLineEdit(groupBox_8);
        lineEdit_hi->setObjectName(QString::fromUtf8("lineEdit_hi"));

        gridLayout_9->addWidget(lineEdit_hi, 8, 1, 1, 1);

        bt_send_pid = new QPushButton(groupBox_8);
        bt_send_pid->setObjectName(QString::fromUtf8("bt_send_pid"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bt_send_pid->sizePolicy().hasHeightForWidth());
        bt_send_pid->setSizePolicy(sizePolicy);
        bt_send_pid->setAutoExclusive(true);

        gridLayout_9->addWidget(bt_send_pid, 3, 3, 7, 1);

        label_9 = new QLabel(groupBox_8);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_9->addWidget(label_9, 2, 0, 1, 1);

        lineEdit_vibration_2 = new QLineEdit(groupBox_8);
        lineEdit_vibration_2->setObjectName(QString::fromUtf8("lineEdit_vibration_2"));

        gridLayout_9->addWidget(lineEdit_vibration_2, 2, 1, 1, 1);

        label_10 = new QLabel(groupBox_8);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_9->addWidget(label_10, 1, 2, 1, 1);

        label_11 = new QLabel(groupBox_8);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_9->addWidget(label_11, 2, 2, 1, 1);

        label_12 = new QLabel(groupBox_8);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_9->addWidget(label_12, 0, 2, 1, 1);

        label_7->raise();
        label_8->raise();
        bt_send_pid->raise();
        label_3->raise();
        label_4->raise();
        lineEdit_hp->raise();
        label_2->raise();
        lineEdit_hi->raise();
        lineEdit_hd->raise();
        lineEdit_vp->raise();
        lineEdit_vi->raise();
        lineEdit_vd->raise();
        lineEdit_open_loop->raise();
        label_5->raise();
        label_6->raise();
        lineEdit_vibration_1->raise();
        label_9->raise();
        lineEdit_vibration_2->raise();
        label_10->raise();
        label_11->raise();
        label_12->raise();

        gridLayout_7->addWidget(groupBox_8, 0, 0, 1, 2);


        gridLayout->addWidget(groupBox_setup, 0, 0, 1, 1);


        retranslateUi(Dialog_motion_param);

        QMetaObject::connectSlotsByName(Dialog_motion_param);
    } // setupUi

    void retranslateUi(QDialog *Dialog_motion_param)
    {
        Dialog_motion_param->setWindowTitle(QCoreApplication::translate("Dialog_motion_param", "Dialog", nullptr));
        groupBox_setup->setTitle(QCoreApplication::translate("Dialog_motion_param", "C\303\240i \304\221\341\272\267t", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("Dialog_motion_param", "\341\273\224n \304\221\341\273\213nh con quay", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog_motion_param", "H\341\273\207 s\341\273\221 \304\221i\341\273\201u khi\341\273\203n v\303\262ng h\341\273\237:", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog_motion_param", "T\341\272\247m:", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog_motion_param", "H\306\260\341\273\233ng:", nullptr));
        lineEdit_vp->setText(QCoreApplication::translate("Dialog_motion_param", "3", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog_motion_param", "Tri\341\273\207t rung 1", nullptr));
        lineEdit_open_loop->setText(QCoreApplication::translate("Dialog_motion_param", "0.57", nullptr));
        lineEdit_vibration_1->setText(QCoreApplication::translate("Dialog_motion_param", "25", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog_motion_param", "H\341\273\207 s\341\273\221 D:", nullptr));
        lineEdit_vd->setText(QCoreApplication::translate("Dialog_motion_param", "-1", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_motion_param", "H\341\273\207 s\341\273\221 P:", nullptr));
        lineEdit_hd->setText(QCoreApplication::translate("Dialog_motion_param", "0.1", nullptr));
        lineEdit_vi->setText(QCoreApplication::translate("Dialog_motion_param", "0.1", nullptr));
        lineEdit_hp->setText(QCoreApplication::translate("Dialog_motion_param", "0.5", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog_motion_param", "H\341\273\207 s\341\273\221 I:", nullptr));
        lineEdit_hi->setText(QCoreApplication::translate("Dialog_motion_param", "0.3", nullptr));
        bt_send_pid->setText(QCoreApplication::translate("Dialog_motion_param", "L\306\260u", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog_motion_param", "Tri\341\273\207t rung 2", nullptr));
        lineEdit_vibration_2->setText(QCoreApplication::translate("Dialog_motion_param", "75", nullptr));
        label_10->setText(QCoreApplication::translate("Dialog_motion_param", "(s\341\273\221 nguy\303\252n t\341\273\253 10-50)", nullptr));
        label_11->setText(QCoreApplication::translate("Dialog_motion_param", "(s\341\273\221 nguy\303\252n t\341\273\253 60-80)", nullptr));
        label_12->setText(QCoreApplication::translate("Dialog_motion_param", "(0.55-0.59)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_motion_param: public Ui_Dialog_motion_param {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_MOTION_PARAM_H
