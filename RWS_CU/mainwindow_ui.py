# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'mainwindow.ui'
##
## Created by: Qt User Interface Compiler version 6.7.2
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QFrame, QGridLayout, QGroupBox,
    QHBoxLayout, QLabel, QMainWindow, QPushButton,
    QRadioButton, QSizePolicy, QSlider, QSpacerItem,
    QStackedWidget, QStatusBar, QTextBrowser, QTextEdit,
    QVBoxLayout, QWidget)

from qcgaugewidget import QcGaugeWidget
from qcustombutton import QCustomButton
from qcustomslider import QCustomSlider

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1697, 1252)
        MainWindow.setMinimumSize(QSize(60, 90))
        font = QFont()
        font.setPointSize(12)
        MainWindow.setFont(font)
        MainWindow.setStyleSheet(u"color:black; background-color: rgba(114,129,119,0);")
        self.centralwidget = QWidget(MainWindow)
        self.centralwidget.setObjectName(u"centralwidget")
        self.groupBox_setup = QGroupBox(self.centralwidget)
        self.groupBox_setup.setObjectName(u"groupBox_setup")
        self.groupBox_setup.setGeometry(QRect(1050, 60, 721, 631))
        self.groupBox_setup.setStyleSheet(u"background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)")
        self.gridLayout_7 = QGridLayout(self.groupBox_setup)
        self.gridLayout_7.setSpacing(6)
        self.gridLayout_7.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.groupBox_13 = QGroupBox(self.groupBox_setup)
        self.groupBox_13.setObjectName(u"groupBox_13")
        self.gridLayout_12 = QGridLayout(self.groupBox_13)
        self.gridLayout_12.setSpacing(6)
        self.gridLayout_12.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_12.setObjectName(u"gridLayout_12")
        self.label_11 = QLabel(self.groupBox_13)
        self.label_11.setObjectName(u"label_11")

        self.gridLayout_12.addWidget(self.label_11, 0, 0, 1, 1)

        self.label_9 = QLabel(self.groupBox_13)
        self.label_9.setObjectName(u"label_9")

        self.gridLayout_12.addWidget(self.label_9, 1, 0, 1, 1)

        self.label_10 = QLabel(self.groupBox_13)
        self.label_10.setObjectName(u"label_10")

        self.gridLayout_12.addWidget(self.label_10, 2, 0, 1, 1)

        self.textEdit_gearh = QTextEdit(self.groupBox_13)
        self.textEdit_gearh.setObjectName(u"textEdit_gearh")

        self.gridLayout_12.addWidget(self.textEdit_gearh, 1, 1, 1, 1)

        self.textEdit_gearv = QTextEdit(self.groupBox_13)
        self.textEdit_gearv.setObjectName(u"textEdit_gearv")

        self.gridLayout_12.addWidget(self.textEdit_gearv, 1, 2, 1, 1)

        self.textEdit_pprh = QTextEdit(self.groupBox_13)
        self.textEdit_pprh.setObjectName(u"textEdit_pprh")

        self.gridLayout_12.addWidget(self.textEdit_pprh, 2, 1, 1, 1)

        self.textEdit_pprv = QTextEdit(self.groupBox_13)
        self.textEdit_pprv.setObjectName(u"textEdit_pprv")

        self.gridLayout_12.addWidget(self.textEdit_pprv, 2, 2, 1, 1)

        self.bt_save_setting_2 = QPushButton(self.groupBox_13)
        self.bt_save_setting_2.setObjectName(u"bt_save_setting_2")
        sizePolicy = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.bt_save_setting_2.sizePolicy().hasHeightForWidth())
        self.bt_save_setting_2.setSizePolicy(sizePolicy)
        self.bt_save_setting_2.setAutoExclusive(True)

        self.gridLayout_12.addWidget(self.bt_save_setting_2, 0, 3, 1, 1)

        self.bt_send_pid_2 = QPushButton(self.groupBox_13)
        self.bt_send_pid_2.setObjectName(u"bt_send_pid_2")
        sizePolicy.setHeightForWidth(self.bt_send_pid_2.sizePolicy().hasHeightForWidth())
        self.bt_send_pid_2.setSizePolicy(sizePolicy)
        self.bt_send_pid_2.setAutoExclusive(True)

        self.gridLayout_12.addWidget(self.bt_send_pid_2, 1, 3, 2, 1)

        self.textEdit_acc = QTextEdit(self.groupBox_13)
        self.textEdit_acc.setObjectName(u"textEdit_acc")

        self.gridLayout_12.addWidget(self.textEdit_acc, 0, 2, 1, 1)


        self.gridLayout_7.addWidget(self.groupBox_13, 0, 0, 1, 2)

        self.groupBox_6 = QGroupBox(self.groupBox_setup)
        self.groupBox_6.setObjectName(u"groupBox_6")
        self.gridLayout_6 = QGridLayout(self.groupBox_6)
        self.gridLayout_6.setSpacing(6)
        self.gridLayout_6.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.label_6 = QLabel(self.groupBox_6)
        self.label_6.setObjectName(u"label_6")

        self.gridLayout_6.addWidget(self.label_6, 0, 0, 1, 1)

        self.textEdit_ballistic_k = QTextEdit(self.groupBox_6)
        self.textEdit_ballistic_k.setObjectName(u"textEdit_ballistic_k")

        self.gridLayout_6.addWidget(self.textEdit_ballistic_k, 0, 1, 1, 1)

        self.bt_save_setting = QPushButton(self.groupBox_6)
        self.bt_save_setting.setObjectName(u"bt_save_setting")
        sizePolicy.setHeightForWidth(self.bt_save_setting.sizePolicy().hasHeightForWidth())
        self.bt_save_setting.setSizePolicy(sizePolicy)
        self.bt_save_setting.setAutoExclusive(True)

        self.gridLayout_6.addWidget(self.bt_save_setting, 0, 2, 1, 1)


        self.gridLayout_7.addWidget(self.groupBox_6, 2, 1, 1, 1)

        self.groupBox_7 = QGroupBox(self.groupBox_setup)
        self.groupBox_7.setObjectName(u"groupBox_7")
        self.gridLayout_8 = QGridLayout(self.groupBox_7)
        self.gridLayout_8.setSpacing(6)
        self.gridLayout_8.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_8.setObjectName(u"gridLayout_8")
        self.bt_control_1_pulse = QPushButton(self.groupBox_7)
        self.bt_control_1_pulse.setObjectName(u"bt_control_1_pulse")
        self.bt_control_1_pulse.setCheckable(True)
        self.bt_control_1_pulse.setChecked(True)
        self.bt_control_1_pulse.setAutoExclusive(True)

        self.gridLayout_8.addWidget(self.bt_control_1_pulse, 0, 0, 1, 2)

        self.bt_control_2_pulse = QPushButton(self.groupBox_7)
        self.bt_control_2_pulse.setObjectName(u"bt_control_2_pulse")
        self.bt_control_2_pulse.setCheckable(True)
        self.bt_control_2_pulse.setAutoExclusive(True)

        self.gridLayout_8.addWidget(self.bt_control_2_pulse, 1, 0, 1, 2)


        self.gridLayout_7.addWidget(self.groupBox_7, 2, 0, 1, 1)

        self.groupBox_8 = QGroupBox(self.groupBox_setup)
        self.groupBox_8.setObjectName(u"groupBox_8")
        self.gridLayout_9 = QGridLayout(self.groupBox_8)
        self.gridLayout_9.setSpacing(6)
        self.gridLayout_9.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_9.setObjectName(u"gridLayout_9")
        self.label_8 = QLabel(self.groupBox_8)
        self.label_8.setObjectName(u"label_8")

        self.gridLayout_9.addWidget(self.label_8, 1, 2, 1, 1)

        self.textEdit_dv = QTextEdit(self.groupBox_8)
        self.textEdit_dv.setObjectName(u"textEdit_dv")

        self.gridLayout_9.addWidget(self.textEdit_dv, 5, 2, 1, 1)

        self.textEdit_ph = QTextEdit(self.groupBox_8)
        self.textEdit_ph.setObjectName(u"textEdit_ph")

        self.gridLayout_9.addWidget(self.textEdit_ph, 3, 1, 1, 1)

        self.textEdit_ih = QTextEdit(self.groupBox_8)
        self.textEdit_ih.setObjectName(u"textEdit_ih")

        self.gridLayout_9.addWidget(self.textEdit_ih, 4, 1, 1, 1)

        self.textEdit_dh = QTextEdit(self.groupBox_8)
        self.textEdit_dh.setObjectName(u"textEdit_dh")

        self.gridLayout_9.addWidget(self.textEdit_dh, 5, 1, 1, 1)

        self.textEdit_iv = QTextEdit(self.groupBox_8)
        self.textEdit_iv.setObjectName(u"textEdit_iv")

        self.gridLayout_9.addWidget(self.textEdit_iv, 4, 2, 1, 1)

        self.label_7 = QLabel(self.groupBox_8)
        self.label_7.setObjectName(u"label_7")

        self.gridLayout_9.addWidget(self.label_7, 1, 1, 1, 1)

        self.textEdit_pv = QTextEdit(self.groupBox_8)
        self.textEdit_pv.setObjectName(u"textEdit_pv")

        self.gridLayout_9.addWidget(self.textEdit_pv, 3, 2, 1, 1)

        self.bt_send_pid = QPushButton(self.groupBox_8)
        self.bt_send_pid.setObjectName(u"bt_send_pid")
        sizePolicy.setHeightForWidth(self.bt_send_pid.sizePolicy().hasHeightForWidth())
        self.bt_send_pid.setSizePolicy(sizePolicy)
        self.bt_send_pid.setAutoExclusive(True)

        self.gridLayout_9.addWidget(self.bt_send_pid, 3, 3, 3, 1)

        self.label_2 = QLabel(self.groupBox_8)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout_9.addWidget(self.label_2, 3, 0, 1, 1)

        self.label_3 = QLabel(self.groupBox_8)
        self.label_3.setObjectName(u"label_3")

        self.gridLayout_9.addWidget(self.label_3, 4, 0, 1, 1)

        self.label_4 = QLabel(self.groupBox_8)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_9.addWidget(self.label_4, 5, 0, 1, 1)

        self.label_7.raise_()
        self.label_8.raise_()
        self.textEdit_dv.raise_()
        self.textEdit_ph.raise_()
        self.textEdit_ih.raise_()
        self.textEdit_dh.raise_()
        self.textEdit_iv.raise_()
        self.textEdit_pv.raise_()
        self.bt_send_pid.raise_()
        self.label_2.raise_()
        self.label_3.raise_()
        self.label_4.raise_()

        self.gridLayout_7.addWidget(self.groupBox_8, 1, 0, 1, 2)

        self.groupBox_14 = QGroupBox(self.groupBox_setup)
        self.groupBox_14.setObjectName(u"groupBox_14")
        self.gridLayout_13 = QGridLayout(self.groupBox_14)
        self.gridLayout_13.setSpacing(6)
        self.gridLayout_13.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_13.setObjectName(u"gridLayout_13")
        self.label_14 = QLabel(self.groupBox_14)
        self.label_14.setObjectName(u"label_14")

        self.gridLayout_13.addWidget(self.label_14, 2, 0, 1, 1)

        self.textEdit_p_track = QTextEdit(self.groupBox_14)
        self.textEdit_p_track.setObjectName(u"textEdit_p_track")

        self.gridLayout_13.addWidget(self.textEdit_p_track, 0, 1, 1, 1)

        self.textEdit_d_track = QTextEdit(self.groupBox_14)
        self.textEdit_d_track.setObjectName(u"textEdit_d_track")

        self.gridLayout_13.addWidget(self.textEdit_d_track, 2, 1, 1, 1)

        self.label_13 = QLabel(self.groupBox_14)
        self.label_13.setObjectName(u"label_13")

        self.gridLayout_13.addWidget(self.label_13, 1, 0, 1, 1)

        self.label_12 = QLabel(self.groupBox_14)
        self.label_12.setObjectName(u"label_12")

        self.gridLayout_13.addWidget(self.label_12, 0, 0, 1, 1)

        self.textEdit_i_track = QTextEdit(self.groupBox_14)
        self.textEdit_i_track.setObjectName(u"textEdit_i_track")

        self.gridLayout_13.addWidget(self.textEdit_i_track, 1, 1, 1, 1)

        self.bt_send_pid_track = QPushButton(self.groupBox_14)
        self.bt_send_pid_track.setObjectName(u"bt_send_pid_track")
        sizePolicy.setHeightForWidth(self.bt_send_pid_track.sizePolicy().hasHeightForWidth())
        self.bt_send_pid_track.setSizePolicy(sizePolicy)
        self.bt_send_pid_track.setAutoExclusive(True)

        self.gridLayout_13.addWidget(self.bt_send_pid_track, 0, 2, 3, 1)


        self.gridLayout_7.addWidget(self.groupBox_14, 3, 0, 1, 2)

        self.groupBox_angle_limit = QGroupBox(self.centralwidget)
        self.groupBox_angle_limit.setObjectName(u"groupBox_angle_limit")
        self.groupBox_angle_limit.setGeometry(QRect(1530, 750, 121, 91))
        self.groupBox_angle_limit.setStyleSheet(u"background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)")
        self.gridLayout_14 = QGridLayout(self.groupBox_angle_limit)
        self.gridLayout_14.setSpacing(6)
        self.gridLayout_14.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_14.setObjectName(u"gridLayout_14")
        self.radioButton_leftlimit = QRadioButton(self.groupBox_angle_limit)
        self.radioButton_leftlimit.setObjectName(u"radioButton_leftlimit")

        self.gridLayout_14.addWidget(self.radioButton_leftlimit, 1, 0, 1, 1)

        self.radioButton_nolimit = QRadioButton(self.groupBox_angle_limit)
        self.radioButton_nolimit.setObjectName(u"radioButton_nolimit")

        self.gridLayout_14.addWidget(self.radioButton_nolimit, 1, 1, 1, 1)

        self.radioButton_uplimit = QRadioButton(self.groupBox_angle_limit)
        self.radioButton_uplimit.setObjectName(u"radioButton_uplimit")

        self.gridLayout_14.addWidget(self.radioButton_uplimit, 0, 1, 1, 1)

        self.radioButton_downlimit = QRadioButton(self.groupBox_angle_limit)
        self.radioButton_downlimit.setObjectName(u"radioButton_downlimit")

        self.gridLayout_14.addWidget(self.radioButton_downlimit, 2, 1, 1, 1)

        self.radioButton_rightlimit = QRadioButton(self.groupBox_angle_limit)
        self.radioButton_rightlimit.setObjectName(u"radioButton_rightlimit")

        self.gridLayout_14.addWidget(self.radioButton_rightlimit, 1, 2, 1, 1)

        self.groupBox_15 = QGroupBox(self.centralwidget)
        self.groupBox_15.setObjectName(u"groupBox_15")
        self.groupBox_15.setGeometry(QRect(1250, 90, 131, 141))
        self.groupBox_15.setStyleSheet(u"background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)")
        self.gridLayout_15 = QGridLayout(self.groupBox_15)
        self.gridLayout_15.setSpacing(6)
        self.gridLayout_15.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_15.setObjectName(u"gridLayout_15")
        self.bt_video_main = QPushButton(self.groupBox_15)
        self.bt_video_main.setObjectName(u"bt_video_main")
        sizePolicy.setHeightForWidth(self.bt_video_main.sizePolicy().hasHeightForWidth())
        self.bt_video_main.setSizePolicy(sizePolicy)
        self.bt_video_main.setCheckable(True)
        self.bt_video_main.setAutoExclusive(False)

        self.gridLayout_15.addWidget(self.bt_video_main, 0, 0, 1, 1)

        self.bt_video_off = QPushButton(self.groupBox_15)
        self.bt_video_off.setObjectName(u"bt_video_off")
        sizePolicy.setHeightForWidth(self.bt_video_off.sizePolicy().hasHeightForWidth())
        self.bt_video_off.setSizePolicy(sizePolicy)
        self.bt_video_off.setCheckable(True)
        self.bt_video_off.setAutoExclusive(False)

        self.gridLayout_15.addWidget(self.bt_video_off, 1, 0, 1, 1)

        self.groupBox_16 = QGroupBox(self.centralwidget)
        self.groupBox_16.setObjectName(u"groupBox_16")
        self.groupBox_16.setGeometry(QRect(1220, 250, 121, 101))
        self.groupBox_16.setStyleSheet(u"background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)")
        self.verticalLayout_6 = QVBoxLayout(self.groupBox_16)
        self.verticalLayout_6.setSpacing(2)
        self.verticalLayout_6.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalLayout_6.setContentsMargins(5, 5, 5, 5)
        self.frame_gui = QFrame(self.centralwidget)
        self.frame_gui.setObjectName(u"frame_gui")
        self.frame_gui.setGeometry(QRect(5, 15, 1034, 771))
        self.frame_gui.setStyleSheet(u"background-color: rgba(255, 255, 255,0);")
        self.frame_4 = QFrame(self.frame_gui)
        self.frame_4.setObjectName(u"frame_4")
        self.frame_4.setGeometry(QRect(0, 9, 120, 751))
        sizePolicy1 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.frame_4.sizePolicy().hasHeightForWidth())
        self.frame_4.setSizePolicy(sizePolicy1)
        self.frame_4.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.frame_4.setFrameShape(QFrame.NoFrame)
        self.verticalLayout_2 = QVBoxLayout(self.frame_4)
        self.verticalLayout_2.setSpacing(3)
        self.verticalLayout_2.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(5, 5, 5, 5)
        self.bt_f_1 = QCustomButton(self.frame_4)
        self.bt_f_1.setObjectName(u"bt_f_1")
        sizePolicy.setHeightForWidth(self.bt_f_1.sizePolicy().hasHeightForWidth())
        self.bt_f_1.setSizePolicy(sizePolicy)
        icon = QIcon()
        icon.addFile(u"icons/gun.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.bt_f_1.setIcon(icon)
        self.bt_f_1.setIconSize(QSize(64, 64))
        self.bt_f_1.setCheckable(True)
        self.bt_f_1.setAutoExclusive(True)

        self.verticalLayout_2.addWidget(self.bt_f_1)

        self.bt_f_2 = QCustomButton(self.frame_4)
        self.bt_f_2.setObjectName(u"bt_f_2")
        sizePolicy.setHeightForWidth(self.bt_f_2.sizePolicy().hasHeightForWidth())
        self.bt_f_2.setSizePolicy(sizePolicy)
        icon1 = QIcon()
        icon1.addFile(u"icons/camera-recorder.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.bt_f_2.setIcon(icon1)
        self.bt_f_2.setIconSize(QSize(64, 64))
        self.bt_f_2.setCheckable(True)
        self.bt_f_2.setAutoExclusive(True)

        self.verticalLayout_2.addWidget(self.bt_f_2)

        self.bt_f_3 = QCustomButton(self.frame_4)
        self.bt_f_3.setObjectName(u"bt_f_3")
        sizePolicy.setHeightForWidth(self.bt_f_3.sizePolicy().hasHeightForWidth())
        self.bt_f_3.setSizePolicy(sizePolicy)
        icon2 = QIcon()
        icon2.addFile(u"icons/target.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.bt_f_3.setIcon(icon2)
        self.bt_f_3.setIconSize(QSize(64, 64))
        self.bt_f_3.setCheckable(True)
        self.bt_f_3.setAutoExclusive(True)

        self.verticalLayout_2.addWidget(self.bt_f_3)

        self.bt_f_4 = QCustomButton(self.frame_4)
        self.bt_f_4.setObjectName(u"bt_f_4")
        sizePolicy.setHeightForWidth(self.bt_f_4.sizePolicy().hasHeightForWidth())
        self.bt_f_4.setSizePolicy(sizePolicy)
        icon3 = QIcon()
        icon3.addFile(u"icons/control.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.bt_f_4.setIcon(icon3)
        self.bt_f_4.setIconSize(QSize(64, 64))
        self.bt_f_4.setCheckable(True)
        self.bt_f_4.setAutoExclusive(True)

        self.verticalLayout_2.addWidget(self.bt_f_4)

        self.bt_f_5 = QCustomButton(self.frame_4)
        self.bt_f_5.setObjectName(u"bt_f_5")
        sizePolicy.setHeightForWidth(self.bt_f_5.sizePolicy().hasHeightForWidth())
        self.bt_f_5.setSizePolicy(sizePolicy)
        icon4 = QIcon()
        icon4.addFile(u"icons/tracker.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.bt_f_5.setIcon(icon4)
        self.bt_f_5.setIconSize(QSize(64, 64))
        self.bt_f_5.setCheckable(True)
        self.bt_f_5.setAutoExclusive(True)

        self.verticalLayout_2.addWidget(self.bt_f_5)

        self.bt_f_6 = QCustomButton(self.frame_4)
        self.bt_f_6.setObjectName(u"bt_f_6")
        sizePolicy.setHeightForWidth(self.bt_f_6.sizePolicy().hasHeightForWidth())
        self.bt_f_6.setSizePolicy(sizePolicy)
        icon5 = QIcon()
        icon5.addFile(u"icons/application-settings.png", QSize(), QIcon.Mode.Normal, QIcon.State.Off)
        self.bt_f_6.setIcon(icon5)
        self.bt_f_6.setIconSize(QSize(64, 64))
        self.bt_f_6.setCheckable(True)
        self.bt_f_6.setAutoExclusive(True)

        self.verticalLayout_2.addWidget(self.bt_f_6)

        self.stackedWidget = QStackedWidget(self.frame_gui)
        self.stackedWidget.setObjectName(u"stackedWidget")
        self.stackedWidget.setGeometry(QRect(900, 0, 120, 600))
        sizePolicy1.setHeightForWidth(self.stackedWidget.sizePolicy().hasHeightForWidth())
        self.stackedWidget.setSizePolicy(sizePolicy1)
        self.stackedWidget.setMinimumSize(QSize(120, 600))
        self.stackedWidget.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.page = QWidget()
        self.page.setObjectName(u"page")
        self.verticalLayout_7 = QVBoxLayout(self.page)
        self.verticalLayout_7.setSpacing(6)
        self.verticalLayout_7.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.bt_control_mode = QCustomButton(self.page)
        self.bt_control_mode.setObjectName(u"bt_control_mode")
        sizePolicy.setHeightForWidth(self.bt_control_mode.sizePolicy().hasHeightForWidth())
        self.bt_control_mode.setSizePolicy(sizePolicy)
        self.bt_control_mode.setMinimumSize(QSize(0, 90))
        self.bt_control_mode.setCheckable(False)

        self.verticalLayout_7.addWidget(self.bt_control_mode)

        self.bt_control_mode_2 = QCustomButton(self.page)
        self.bt_control_mode_2.setObjectName(u"bt_control_mode_2")
        sizePolicy.setHeightForWidth(self.bt_control_mode_2.sizePolicy().hasHeightForWidth())
        self.bt_control_mode_2.setSizePolicy(sizePolicy)
        self.bt_control_mode_2.setMinimumSize(QSize(0, 90))
        self.bt_control_mode_2.setCheckable(False)

        self.verticalLayout_7.addWidget(self.bt_control_mode_2)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout_7.addItem(self.verticalSpacer_2)

        self.stackedWidget.addWidget(self.page)
        self.stackedWidgetPage1 = QWidget()
        self.stackedWidgetPage1.setObjectName(u"stackedWidgetPage1")
        self.verticalLayout_3 = QVBoxLayout(self.stackedWidgetPage1)
        self.verticalLayout_3.setSpacing(6)
        self.verticalLayout_3.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.bt_control_file_6 = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_file_6.setObjectName(u"bt_control_file_6")
        sizePolicy.setHeightForWidth(self.bt_control_file_6.sizePolicy().hasHeightForWidth())
        self.bt_control_file_6.setSizePolicy(sizePolicy)
        self.bt_control_file_6.setCheckable(False)

        self.verticalLayout_3.addWidget(self.bt_control_file_6)

        self.bt_control_file_2 = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_file_2.setObjectName(u"bt_control_file_2")
        sizePolicy.setHeightForWidth(self.bt_control_file_2.sizePolicy().hasHeightForWidth())
        self.bt_control_file_2.setSizePolicy(sizePolicy)
        self.bt_control_file_2.setCheckable(False)

        self.verticalLayout_3.addWidget(self.bt_control_file_2)

        self.bt_control_file_3 = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_file_3.setObjectName(u"bt_control_file_3")
        sizePolicy.setHeightForWidth(self.bt_control_file_3.sizePolicy().hasHeightForWidth())
        self.bt_control_file_3.setSizePolicy(sizePolicy)
        self.bt_control_file_3.setCheckable(False)

        self.verticalLayout_3.addWidget(self.bt_control_file_3)

        self.bt_control_file_4 = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_file_4.setObjectName(u"bt_control_file_4")
        sizePolicy.setHeightForWidth(self.bt_control_file_4.sizePolicy().hasHeightForWidth())
        self.bt_control_file_4.setSizePolicy(sizePolicy)
        self.bt_control_file_4.setCheckable(False)

        self.verticalLayout_3.addWidget(self.bt_control_file_4)

        self.bt_control_file_5 = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_file_5.setObjectName(u"bt_control_file_5")
        sizePolicy.setHeightForWidth(self.bt_control_file_5.sizePolicy().hasHeightForWidth())
        self.bt_control_file_5.setSizePolicy(sizePolicy)
        self.bt_control_file_5.setCheckable(False)

        self.verticalLayout_3.addWidget(self.bt_control_file_5)

        self.bt_control_focusauto = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_focusauto.setObjectName(u"bt_control_focusauto")
        sizePolicy.setHeightForWidth(self.bt_control_focusauto.sizePolicy().hasHeightForWidth())
        self.bt_control_focusauto.setSizePolicy(sizePolicy)
        self.bt_control_focusauto.setCheckable(True)

        self.verticalLayout_3.addWidget(self.bt_control_focusauto)

        self.bt_control_focusauto_2 = QCustomButton(self.stackedWidgetPage1)
        self.bt_control_focusauto_2.setObjectName(u"bt_control_focusauto_2")
        sizePolicy.setHeightForWidth(self.bt_control_focusauto_2.sizePolicy().hasHeightForWidth())
        self.bt_control_focusauto_2.setSizePolicy(sizePolicy)
        self.bt_control_focusauto_2.setCheckable(True)

        self.verticalLayout_3.addWidget(self.bt_control_focusauto_2)

        self.stackedWidget.addWidget(self.stackedWidgetPage1)
        self.stackedWidgetPage3 = QWidget()
        self.stackedWidgetPage3.setObjectName(u"stackedWidgetPage3")
        self.verticalLayout = QVBoxLayout(self.stackedWidgetPage3)
        self.verticalLayout.setSpacing(6)
        self.verticalLayout.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.bt_control_file_7 = QCustomButton(self.stackedWidgetPage3)
        self.bt_control_file_7.setObjectName(u"bt_control_file_7")
        sizePolicy2 = QSizePolicy(QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Fixed)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.bt_control_file_7.sizePolicy().hasHeightForWidth())
        self.bt_control_file_7.setSizePolicy(sizePolicy2)
        self.bt_control_file_7.setMinimumSize(QSize(0, 90))
        self.bt_control_file_7.setMaximumSize(QSize(16777215, 90))
        self.bt_control_file_7.setCheckable(False)

        self.verticalLayout.addWidget(self.bt_control_file_7)

        self.toolButton_sightup = QCustomButton(self.stackedWidgetPage3)
        self.toolButton_sightup.setObjectName(u"toolButton_sightup")
        sizePolicy.setHeightForWidth(self.toolButton_sightup.sizePolicy().hasHeightForWidth())
        self.toolButton_sightup.setSizePolicy(sizePolicy)
        self.toolButton_sightup.setMinimumSize(QSize(0, 90))
        self.toolButton_sightup.setMaximumSize(QSize(16777215, 90))
        self.toolButton_sightup.setCheckable(False)

        self.verticalLayout.addWidget(self.toolButton_sightup)

        self.toolButton_sight_right = QCustomButton(self.stackedWidgetPage3)
        self.toolButton_sight_right.setObjectName(u"toolButton_sight_right")
        sizePolicy.setHeightForWidth(self.toolButton_sight_right.sizePolicy().hasHeightForWidth())
        self.toolButton_sight_right.setSizePolicy(sizePolicy)
        self.toolButton_sight_right.setMinimumSize(QSize(0, 90))
        self.toolButton_sight_right.setMaximumSize(QSize(16777215, 90))
        self.toolButton_sight_right.setCheckable(False)

        self.verticalLayout.addWidget(self.toolButton_sight_right)

        self.bt_control_kv = QCustomButton(self.stackedWidgetPage3)
        self.bt_control_kv.setObjectName(u"bt_control_kv")
        sizePolicy.setHeightForWidth(self.bt_control_kv.sizePolicy().hasHeightForWidth())
        self.bt_control_kv.setSizePolicy(sizePolicy)
        self.bt_control_kv.setMinimumSize(QSize(0, 90))
        self.bt_control_kv.setCheckable(True)

        self.verticalLayout.addWidget(self.bt_control_kv)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Policy.Minimum, QSizePolicy.Policy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer)

        self.stackedWidget.addWidget(self.stackedWidgetPage3)
        self.stackedWidgetPage4 = QWidget()
        self.stackedWidgetPage4.setObjectName(u"stackedWidgetPage4")
        self.verticalLayout_4 = QVBoxLayout(self.stackedWidgetPage4)
        self.verticalLayout_4.setSpacing(6)
        self.verticalLayout_4.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.groupBox_17 = QGroupBox(self.stackedWidgetPage4)
        self.groupBox_17.setObjectName(u"groupBox_17")
        self.groupBox_17.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.gridLayout_16 = QGridLayout(self.groupBox_17)
        self.gridLayout_16.setSpacing(6)
        self.gridLayout_16.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_16.setObjectName(u"gridLayout_16")
        self.bt_zero_set_3 = QCustomButton(self.groupBox_17)
        self.bt_zero_set_3.setObjectName(u"bt_zero_set_3")
        sizePolicy.setHeightForWidth(self.bt_zero_set_3.sizePolicy().hasHeightForWidth())
        self.bt_zero_set_3.setSizePolicy(sizePolicy)
        self.bt_zero_set_3.setCheckable(True)
        self.bt_zero_set_3.setAutoExclusive(True)

        self.gridLayout_16.addWidget(self.bt_zero_set_3, 0, 0, 1, 1)

        self.bt_control_usb = QCustomButton(self.groupBox_17)
        self.bt_control_usb.setObjectName(u"bt_control_usb")
        sizePolicy.setHeightForWidth(self.bt_control_usb.sizePolicy().hasHeightForWidth())
        self.bt_control_usb.setSizePolicy(sizePolicy)
        self.bt_control_usb.setCheckable(True)
        self.bt_control_usb.setAutoExclusive(True)

        self.gridLayout_16.addWidget(self.bt_control_usb, 1, 0, 1, 1)

        self.bt_control_usb_2 = QCustomButton(self.groupBox_17)
        self.bt_control_usb_2.setObjectName(u"bt_control_usb_2")
        sizePolicy.setHeightForWidth(self.bt_control_usb_2.sizePolicy().hasHeightForWidth())
        self.bt_control_usb_2.setSizePolicy(sizePolicy)
        self.bt_control_usb_2.setCheckable(True)
        self.bt_control_usb_2.setChecked(True)
        self.bt_control_usb_2.setAutoExclusive(True)

        self.gridLayout_16.addWidget(self.bt_control_usb_2, 2, 0, 1, 1)


        self.verticalLayout_4.addWidget(self.groupBox_17)

        self.bt_stab_2 = QCustomButton(self.stackedWidgetPage4)
        self.bt_stab_2.setObjectName(u"bt_stab_2")
        sizePolicy2.setHeightForWidth(self.bt_stab_2.sizePolicy().hasHeightForWidth())
        self.bt_stab_2.setSizePolicy(sizePolicy2)
        self.bt_stab_2.setMinimumSize(QSize(0, 90))
        self.bt_stab_2.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.bt_stab_2.setCheckable(True)
        self.bt_stab_2.setAutoExclusive(True)

        self.verticalLayout_4.addWidget(self.bt_stab_2)

        self.bt_video_test_2 = QCustomButton(self.stackedWidgetPage4)
        self.bt_video_test_2.setObjectName(u"bt_video_test_2")
        sizePolicy3 = QSizePolicy(QSizePolicy.Policy.Preferred, QSizePolicy.Policy.Fixed)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.bt_video_test_2.sizePolicy().hasHeightForWidth())
        self.bt_video_test_2.setSizePolicy(sizePolicy3)
        self.bt_video_test_2.setMinimumSize(QSize(0, 90))
        self.bt_video_test_2.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.bt_video_test_2.setCheckable(True)
        self.bt_video_test_2.setChecked(True)
        self.bt_video_test_2.setAutoExclusive(True)

        self.verticalLayout_4.addWidget(self.bt_video_test_2)

        self.stackedWidget.addWidget(self.stackedWidgetPage4)
        self.stackedWidgetPage5 = QWidget()
        self.stackedWidgetPage5.setObjectName(u"stackedWidgetPage5")
        self.bt_tracksizeup_2 = QCustomButton(self.stackedWidgetPage5)
        self.bt_tracksizeup_2.setObjectName(u"bt_tracksizeup_2")
        self.bt_tracksizeup_2.setGeometry(QRect(20, 110, 115, 92))
        sizePolicy.setHeightForWidth(self.bt_tracksizeup_2.sizePolicy().hasHeightForWidth())
        self.bt_tracksizeup_2.setSizePolicy(sizePolicy)
        self.bt_tracksizeup_2.setCheckable(False)
        self.bt_tracksizeup = QCustomButton(self.stackedWidgetPage5)
        self.bt_tracksizeup.setObjectName(u"bt_tracksizeup")
        self.bt_tracksizeup.setGeometry(QRect(20, 17, 115, 91))
        sizePolicy.setHeightForWidth(self.bt_tracksizeup.sizePolicy().hasHeightForWidth())
        self.bt_tracksizeup.setSizePolicy(sizePolicy)
        self.bt_tracksizeup.setCheckable(False)
        self.stackedWidget.addWidget(self.stackedWidgetPage5)
        self.stackedWidgetPage6 = QWidget()
        self.stackedWidgetPage6.setObjectName(u"stackedWidgetPage6")
        self.toolButton_show_setup = QCustomButton(self.stackedWidgetPage6)
        self.toolButton_show_setup.setObjectName(u"toolButton_show_setup")
        self.toolButton_show_setup.setGeometry(QRect(10, 30, 115, 91))
        sizePolicy.setHeightForWidth(self.toolButton_show_setup.sizePolicy().hasHeightForWidth())
        self.toolButton_show_setup.setSizePolicy(sizePolicy)
        self.toolButton_show_setup.setCheckable(False)
        self.groupBox_10 = QGroupBox(self.stackedWidgetPage6)
        self.groupBox_10.setObjectName(u"groupBox_10")
        self.groupBox_10.setGeometry(QRect(20, 140, 121, 171))
        self.groupBox_10.setStyleSheet(u"background-color: rgb(69,78,72); color:rgb(255, 255, 255)")
        self.gridLayout_10 = QGridLayout(self.groupBox_10)
        self.gridLayout_10.setSpacing(6)
        self.gridLayout_10.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_10.setObjectName(u"gridLayout_10")
        self.label_stim_stat = QLabel(self.groupBox_10)
        self.label_stim_stat.setObjectName(u"label_stim_stat")

        self.gridLayout_10.addWidget(self.label_stim_stat, 2, 1, 1, 1)

        self.label_cu_connection = QLabel(self.groupBox_10)
        self.label_cu_connection.setObjectName(u"label_cu_connection")

        self.gridLayout_10.addWidget(self.label_cu_connection, 1, 1, 1, 1)

        self.label_video_fps_3 = QLabel(self.groupBox_10)
        self.label_video_fps_3.setObjectName(u"label_video_fps_3")

        self.gridLayout_10.addWidget(self.label_video_fps_3, 1, 0, 1, 1)

        self.label_video_fps_5 = QLabel(self.groupBox_10)
        self.label_video_fps_5.setObjectName(u"label_video_fps_5")

        self.gridLayout_10.addWidget(self.label_video_fps_5, 2, 0, 1, 1)

        self.label_video_fps_17 = QLabel(self.groupBox_10)
        self.label_video_fps_17.setObjectName(u"label_video_fps_17")

        self.gridLayout_10.addWidget(self.label_video_fps_17, 3, 0, 1, 1)

        self.label_video_fps_18 = QLabel(self.groupBox_10)
        self.label_video_fps_18.setObjectName(u"label_video_fps_18")

        self.gridLayout_10.addWidget(self.label_video_fps_18, 4, 0, 1, 1)

        self.label_plc_1 = QLabel(self.groupBox_10)
        self.label_plc_1.setObjectName(u"label_plc_1")

        self.gridLayout_10.addWidget(self.label_plc_1, 3, 1, 1, 1)

        self.label_plc2 = QLabel(self.groupBox_10)
        self.label_plc2.setObjectName(u"label_plc2")

        self.gridLayout_10.addWidget(self.label_plc2, 4, 1, 1, 1)

        self.connectButton = QPushButton(self.groupBox_10)
        self.connectButton.setObjectName(u"connectButton")
        sizePolicy.setHeightForWidth(self.connectButton.sizePolicy().hasHeightForWidth())
        self.connectButton.setSizePolicy(sizePolicy)
        self.connectButton.setCheckable(False)

        self.gridLayout_10.addWidget(self.connectButton, 0, 0, 1, 2)

        self.groupBox_11 = QGroupBox(self.stackedWidgetPage6)
        self.groupBox_11.setObjectName(u"groupBox_11")
        self.groupBox_11.setGeometry(QRect(20, 320, 121, 131))
        self.groupBox_11.setStyleSheet(u"background-color: rgb(32, 64, 128); color:rgb(255, 255, 255)")
        self.verticalLayout_5 = QVBoxLayout(self.groupBox_11)
        self.verticalLayout_5.setSpacing(2)
        self.verticalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(5, 5, 5, 5)
        self.pushButton_play_video = QPushButton(self.groupBox_11)
        self.pushButton_play_video.setObjectName(u"pushButton_play_video")
        sizePolicy.setHeightForWidth(self.pushButton_play_video.sizePolicy().hasHeightForWidth())
        self.pushButton_play_video.setSizePolicy(sizePolicy)
        self.pushButton_play_video.setCheckable(False)

        self.verticalLayout_5.addWidget(self.pushButton_play_video)

        self.pushButton_record = QPushButton(self.groupBox_11)
        self.pushButton_record.setObjectName(u"pushButton_record")
        sizePolicy.setHeightForWidth(self.pushButton_record.sizePolicy().hasHeightForWidth())
        self.pushButton_record.setSizePolicy(sizePolicy)
        self.pushButton_record.setCheckable(True)

        self.verticalLayout_5.addWidget(self.pushButton_record)

        self.pushButton_power_off = QPushButton(self.groupBox_11)
        self.pushButton_power_off.setObjectName(u"pushButton_power_off")
        sizePolicy.setHeightForWidth(self.pushButton_power_off.sizePolicy().hasHeightForWidth())
        self.pushButton_power_off.setSizePolicy(sizePolicy)
        self.pushButton_power_off.setCheckable(False)

        self.verticalLayout_5.addWidget(self.pushButton_power_off)

        self.stackedWidget.addWidget(self.stackedWidgetPage6)
        self.frame_5 = QFrame(self.centralwidget)
        self.frame_5.setObjectName(u"frame_5")
        self.frame_5.setGeometry(QRect(130, 20, 771, 141))
        sizePolicy1.setHeightForWidth(self.frame_5.sizePolicy().hasHeightForWidth())
        self.frame_5.setSizePolicy(sizePolicy1)
        self.frame_5.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.horizontalLayout = QHBoxLayout(self.frame_5)
        self.horizontalLayout.setSpacing(6)
        self.horizontalLayout.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.groupBox_9 = QGroupBox(self.frame_5)
        self.groupBox_9.setObjectName(u"groupBox_9")
        self.groupBox_9.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.gridLayout_2 = QGridLayout(self.groupBox_9)
        self.gridLayout_2.setSpacing(6)
        self.gridLayout_2.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.label_video_fps_2 = QLabel(self.groupBox_9)
        self.label_video_fps_2.setObjectName(u"label_video_fps_2")

        self.gridLayout_2.addWidget(self.label_video_fps_2, 2, 0, 1, 1)

        self.label_video_fps = QLabel(self.groupBox_9)
        self.label_video_fps.setObjectName(u"label_video_fps")

        self.gridLayout_2.addWidget(self.label_video_fps, 0, 0, 1, 1)

        self.label_track_y = QLabel(self.groupBox_9)
        self.label_track_y.setObjectName(u"label_track_y")
        self.label_track_y.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")

        self.gridLayout_2.addWidget(self.label_track_y, 2, 1, 1, 1)

        self.label_track_x = QLabel(self.groupBox_9)
        self.label_track_x.setObjectName(u"label_track_x")

        self.gridLayout_2.addWidget(self.label_track_x, 0, 1, 1, 1)


        self.horizontalLayout.addWidget(self.groupBox_9)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer)

        self.frame_7 = QFrame(self.frame_5)
        self.frame_7.setObjectName(u"frame_7")
        self.frame_7.setStyleSheet(u"background-color: rgb(69,78,72); color:rgb(255, 255, 255)")
        self.frame_7.setFrameShape(QFrame.StyledPanel)
        self.frame_7.setFrameShadow(QFrame.Raised)
        self.gridLayout = QGridLayout(self.frame_7)
        self.gridLayout.setSpacing(6)
        self.gridLayout.setContentsMargins(11, 11, 11, 11)
        self.gridLayout.setObjectName(u"gridLayout")
        self.label_5 = QLabel(self.frame_7)
        self.label_5.setObjectName(u"label_5")
        self.label_5.setFont(font)

        self.gridLayout.addWidget(self.label_5, 2, 0, 1, 1)

        self.slider_range = QSlider(self.frame_7)
        self.slider_range.setObjectName(u"slider_range")
        sizePolicy4 = QSizePolicy(QSizePolicy.Policy.Fixed, QSizePolicy.Policy.Preferred)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.slider_range.sizePolicy().hasHeightForWidth())
        self.slider_range.setSizePolicy(sizePolicy4)
        self.slider_range.setMinimumSize(QSize(500, 0))
        self.slider_range.setMinimum(1)
        self.slider_range.setMaximum(30)
        self.slider_range.setSingleStep(1)
        self.slider_range.setPageStep(1)
        self.slider_range.setValue(1)
        self.slider_range.setOrientation(Qt.Horizontal)
        self.slider_range.setTickPosition(QSlider.TicksAbove)
        self.slider_range.setTickInterval(1)

        self.gridLayout.addWidget(self.slider_range, 1, 2, 1, 2)

        self.label_speed = QLabel(self.frame_7)
        self.label_speed.setObjectName(u"label_speed")
        sizePolicy5 = QSizePolicy(QSizePolicy.Policy.Expanding, QSizePolicy.Policy.Preferred)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.label_speed.sizePolicy().hasHeightForWidth())
        self.label_speed.setSizePolicy(sizePolicy5)

        self.gridLayout.addWidget(self.label_speed, 0, 2, 1, 1)

        self.frame_2 = QFrame(self.frame_7)
        self.frame_2.setObjectName(u"frame_2")
        self.frame_2.setStyleSheet(u"background-color: rgb(69,78,72); color:rgb(255, 255, 255)")
        self.gridLayout_3 = QGridLayout(self.frame_2)
        self.gridLayout_3.setSpacing(6)
        self.gridLayout_3.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.image_label_8 = QLabel(self.frame_2)
        self.image_label_8.setObjectName(u"image_label_8")
        self.image_label_8.setFrameShape(QFrame.Panel)

        self.gridLayout_3.addWidget(self.image_label_8, 0, 1, 1, 1)

        self.image_label_10 = QLabel(self.frame_2)
        self.image_label_10.setObjectName(u"image_label_10")
        self.image_label_10.setFrameShape(QFrame.Panel)

        self.gridLayout_3.addWidget(self.image_label_10, 1, 1, 1, 1)

        self.image_label_9 = QLabel(self.frame_2)
        self.image_label_9.setObjectName(u"image_label_9")
        self.image_label_9.setFrameShape(QFrame.Panel)

        self.gridLayout_3.addWidget(self.image_label_9, 1, 2, 1, 1)

        self.image_label_12 = QLabel(self.frame_2)
        self.image_label_12.setObjectName(u"image_label_12")
        self.image_label_12.setFrameShape(QFrame.Panel)

        self.gridLayout_3.addWidget(self.image_label_12, 2, 1, 1, 1)

        self.image_label_11 = QLabel(self.frame_2)
        self.image_label_11.setObjectName(u"image_label_11")
        self.image_label_11.setFrameShape(QFrame.Panel)

        self.gridLayout_3.addWidget(self.image_label_11, 0, 2, 1, 1)

        self.image_label_13 = QLabel(self.frame_2)
        self.image_label_13.setObjectName(u"image_label_13")
        self.image_label_13.setFrameShape(QFrame.Panel)

        self.gridLayout_3.addWidget(self.image_label_13, 2, 2, 1, 1)


        self.gridLayout.addWidget(self.frame_2, 0, 4, 3, 1)

        self.label_fov = QLabel(self.frame_7)
        self.label_fov.setObjectName(u"label_fov")
        font1 = QFont()
        font1.setPointSize(16)
        self.label_fov.setFont(font1)

        self.gridLayout.addWidget(self.label_fov, 2, 1, 1, 1)

        self.slider_fov = QSlider(self.frame_7)
        self.slider_fov.setObjectName(u"slider_fov")
        sizePolicy4.setHeightForWidth(self.slider_fov.sizePolicy().hasHeightForWidth())
        self.slider_fov.setSizePolicy(sizePolicy4)
        self.slider_fov.setMinimumSize(QSize(500, 0))
        self.slider_fov.setMinimum(17)
        self.slider_fov.setMaximum(600)
        self.slider_fov.setSingleStep(1)
        self.slider_fov.setPageStep(10)
        self.slider_fov.setValue(600)
        self.slider_fov.setOrientation(Qt.Horizontal)
        self.slider_fov.setTickPosition(QSlider.TicksAbove)
        self.slider_fov.setTickInterval(1)

        self.gridLayout.addWidget(self.slider_fov, 2, 2, 1, 2)

        self.label_speed_2 = QLabel(self.frame_7)
        self.label_speed_2.setObjectName(u"label_speed_2")
        sizePolicy5.setHeightForWidth(self.label_speed_2.sizePolicy().hasHeightForWidth())
        self.label_speed_2.setSizePolicy(sizePolicy5)

        self.gridLayout.addWidget(self.label_speed_2, 0, 0, 1, 1)

        self.label = QLabel(self.frame_7)
        self.label.setObjectName(u"label")
        self.label.setFont(font)

        self.gridLayout.addWidget(self.label, 1, 0, 1, 1)

        self.label_range = QLabel(self.frame_7)
        self.label_range.setObjectName(u"label_range")
        self.label_range.setFont(font1)

        self.gridLayout.addWidget(self.label_range, 1, 1, 1, 1)

        self.label_fovSpeed = QLabel(self.frame_7)
        self.label_fovSpeed.setObjectName(u"label_fovSpeed")
        sizePolicy5.setHeightForWidth(self.label_fovSpeed.sizePolicy().hasHeightForWidth())
        self.label_fovSpeed.setSizePolicy(sizePolicy5)

        self.gridLayout.addWidget(self.label_fovSpeed, 3, 2, 1, 1)


        self.horizontalLayout.addWidget(self.frame_7)

        self.frame_8 = QFrame(self.frame_5)
        self.frame_8.setObjectName(u"frame_8")
        self.frame_8.setStyleSheet(u"color:white; background-color: rgba(114,129,119,100);")
        self.gridLayout_4 = QGridLayout(self.frame_8)
        self.gridLayout_4.setSpacing(0)
        self.gridLayout_4.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.gridLayout_4.setContentsMargins(0, 0, 0, 0)
        self.label_video_fps_8 = QLabel(self.frame_8)
        self.label_video_fps_8.setObjectName(u"label_video_fps_8")
        self.label_video_fps_8.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_4.addWidget(self.label_video_fps_8, 3, 1, 1, 1)

        self.slider_ele = QCustomSlider(self.frame_8)
        self.slider_ele.setObjectName(u"slider_ele")
        self.slider_ele.setMinimumSize(QSize(60, 0))
        self.slider_ele.setMinimum(-1500)
        self.slider_ele.setMaximum(8000)
        self.slider_ele.setSingleStep(1)
        self.slider_ele.setPageStep(1)
        self.slider_ele.setOrientation(Qt.Vertical)
        self.slider_ele.setTickPosition(QSlider.TicksBothSides)
        self.slider_ele.setTickInterval(500)

        self.gridLayout_4.addWidget(self.slider_ele, 0, 0, 4, 1)

        self.label_video_fps_14 = QLabel(self.frame_8)
        self.label_video_fps_14.setObjectName(u"label_video_fps_14")
        self.label_video_fps_14.setAlignment(Qt.AlignBottom|Qt.AlignLeading|Qt.AlignLeft)

        self.gridLayout_4.addWidget(self.label_video_fps_14, 2, 1, 1, 1)

        self.label_video_fps_10 = QLabel(self.frame_8)
        self.label_video_fps_10.setObjectName(u"label_video_fps_10")

        self.gridLayout_4.addWidget(self.label_video_fps_10, 1, 1, 1, 1)

        self.label_video_fps_12 = QLabel(self.frame_8)
        self.label_video_fps_12.setObjectName(u"label_video_fps_12")
        self.label_video_fps_12.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignTop)

        self.gridLayout_4.addWidget(self.label_video_fps_12, 0, 1, 1, 1)


        self.horizontalLayout.addWidget(self.frame_8)

        self.view_azi = QcGaugeWidget(self.frame_5)
        self.view_azi.setObjectName(u"view_azi")
        self.view_azi.setMinimumSize(QSize(120, 120))
        self.view_azi.setMaximumSize(QSize(120, 120))
        self.view_azi.setAutoFillBackground(False)
        self.view_azi.setStyleSheet(u"")

        self.horizontalLayout.addWidget(self.view_azi)

        self.groupBox_4 = QGroupBox(self.centralwidget)
        self.groupBox_4.setObjectName(u"groupBox_4")
        self.groupBox_4.setGeometry(QRect(1250, 890, 280, 132))
        self.gridLayout_5 = QGridLayout(self.groupBox_4)
        self.gridLayout_5.setSpacing(6)
        self.gridLayout_5.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.textBrowser_msg = QTextBrowser(self.groupBox_4)
        self.textBrowser_msg.setObjectName(u"textBrowser_msg")

        self.gridLayout_5.addWidget(self.textBrowser_msg, 0, 0, 1, 1)

        self.pushButton_clear_msg = QPushButton(self.groupBox_4)
        self.pushButton_clear_msg.setObjectName(u"pushButton_clear_msg")

        self.gridLayout_5.addWidget(self.pushButton_clear_msg, 1, 0, 1, 1)

        MainWindow.setCentralWidget(self.centralwidget)
        self.frame_gui.raise_()
        self.groupBox_setup.raise_()
        self.groupBox_angle_limit.raise_()
        self.groupBox_15.raise_()
        self.groupBox_16.raise_()
        self.frame_5.raise_()
        self.groupBox_4.raise_()
        self.statusbar = QStatusBar(MainWindow)
        self.statusbar.setObjectName(u"statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)

        self.stackedWidget.setCurrentIndex(2)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"MainWindow", None))
        self.groupBox_setup.setTitle(QCoreApplication.translate("MainWindow", u"C\u00e0i \u0111\u1eb7t", None))
        self.groupBox_13.setTitle(QCoreApplication.translate("MainWindow", u"\u0110\u1ed9ng c\u01a1", None))
        self.label_11.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 qu\u00e1n t\u00ednh:", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"H\u1ed9p s\u1ed1:", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"PPR", None))
        self.textEdit_gearh.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">200</p></body></html>", None))
        self.textEdit_gearv.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">500</p></body></html>", None))
        self.textEdit_pprh.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">500</p></body></html>", None))
        self.textEdit_pprv.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">500</p></body></html>", None))
        self.bt_save_setting_2.setText(QCoreApplication.translate("MainWindow", u"L\u01b0u", None))
        self.bt_send_pid_2.setText(QCoreApplication.translate("MainWindow", u"L\u01b0u", None))
        self.textEdit_acc.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.1</p></body></html>", None))
        self.groupBox_6.setTitle(QCoreApplication.translate("MainWindow", u"\u0110\u01b0\u1eddng \u0111\u1ea1n:", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 ch\u1ec9nh \u0111\u1ed9 cao \u0111\u01b0\u1eddng \u0111\u1ea1n:", None))
        self.textEdit_ballistic_k.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1</p></body></html>", None))
        self.bt_save_setting.setText(QCoreApplication.translate("MainWindow", u"L\u01b0u", None))
        self.groupBox_7.setTitle(QCoreApplication.translate("MainWindow", u"\u0110i\u1ec1u khi\u1ec3n", None))
        self.bt_control_1_pulse.setText(QCoreApplication.translate("MainWindow", u"Ch\u1ebf \u0111\u1ed9 1 xung", None))
        self.bt_control_2_pulse.setText(QCoreApplication.translate("MainWindow", u"Ch\u1ebf \u0111\u1ed9 2 xung", None))
        self.groupBox_8.setTitle(QCoreApplication.translate("MainWindow", u"\u1ed4n \u0111\u1ecbnh con quay", None))
        self.label_8.setText(QCoreApplication.translate("MainWindow", u"T\u1ea7m:", None))
        self.textEdit_dv.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", None))
        self.textEdit_ph.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1</p></body></html>", None))
        self.textEdit_ih.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.06</p></body></html>", None))
        self.textEdit_dh.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", None))
        self.textEdit_iv.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.06</p></body></html>", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"H\u01b0\u1edbng:", None))
        self.textEdit_pv.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1</p></body></html>", None))
        self.bt_send_pid.setText(QCoreApplication.translate("MainWindow", u"L\u01b0u", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 P:", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 I:", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 D:", None))
        self.groupBox_14.setTitle(QCoreApplication.translate("MainWindow", u"B\u00e1m \u1ea3nh:", None))
        self.label_14.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 D:", None))
        self.textEdit_p_track.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">1</p></body></html>", None))
        self.textEdit_d_track.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", None))
        self.label_13.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 I:", None))
        self.label_12.setText(QCoreApplication.translate("MainWindow", u"H\u1ec7 s\u1ed1 P:", None))
        self.textEdit_i_track.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.06</p></body></html>", None))
        self.bt_send_pid_track.setText(QCoreApplication.translate("MainWindow", u"L\u01b0u", None))
        self.groupBox_angle_limit.setTitle(QCoreApplication.translate("MainWindow", u"Gi\u1edbi h\u1ea1n g\u00f3c:", None))
        self.radioButton_leftlimit.setText("")
        self.radioButton_nolimit.setText("")
        self.radioButton_uplimit.setText("")
        self.radioButton_downlimit.setText("")
        self.radioButton_rightlimit.setText("")
        self.groupBox_15.setTitle(QCoreApplication.translate("MainWindow", u"Ch\u1ebf \u0111\u1ed9 video:", None))
        self.bt_video_main.setText(QCoreApplication.translate("MainWindow", u"Ng\u00e0y", None))
        self.bt_video_off.setText(QCoreApplication.translate("MainWindow", u"T\u1eaft", None))
        self.groupBox_16.setTitle(QCoreApplication.translate("MainWindow", u"Th\u01b0\u1edbc ng\u1eafm", None))
        self.bt_f_1.setText(QCoreApplication.translate("MainWindow", u"CAMERA NG\u00c0Y", None))
        self.bt_f_2.setText(QCoreApplication.translate("MainWindow", u"CAMERA \u0110\u00caM", None))
        self.bt_f_3.setText(QCoreApplication.translate("MainWindow", u"TH\u01af\u1edaC NG\u1eaeM", None))
        self.bt_f_4.setText(QCoreApplication.translate("MainWindow", u"\u0110I\u1ec0U KHI\u1ec2N B\u1ec6", None))
        self.bt_f_5.setText(QCoreApplication.translate("MainWindow", u"B\u00c1M M\u1ee4C TI\u00caU", None))
        self.bt_f_6.setText(QCoreApplication.translate("MainWindow", u"TR\u1ea0NG TH\u00c1I H\u1ec6 TH\u1ed0NG", None))
        self.bt_control_mode.setText(QCoreApplication.translate("MainWindow", u"Ch\u1ebf \u0111\u1ed9 khai h\u1ecfa", None))
        self.bt_control_mode_2.setText(QCoreApplication.translate("MainWindow", u"N\u1ea1p \u0111\u1ea1n", None))
        self.bt_control_file_6.setText(QCoreApplication.translate("MainWindow", u"Ng\u00e0y/\u0111\u00eam", None))
        self.bt_control_file_2.setText(QCoreApplication.translate("MainWindow", u"Zoom +", None))
        self.bt_control_file_3.setText(QCoreApplication.translate("MainWindow", u"Zoom -", None))
        self.bt_control_file_4.setText(QCoreApplication.translate("MainWindow", u"Focus+", None))
        self.bt_control_file_5.setText(QCoreApplication.translate("MainWindow", u"Focus-", None))
        self.bt_control_focusauto.setText(QCoreApplication.translate("MainWindow", u"Autofocus", None))
        self.bt_control_focusauto_2.setText(QCoreApplication.translate("MainWindow", u"T\u1eaft camera", None))
        self.bt_control_file_7.setText(QCoreApplication.translate("MainWindow", u"\u0110o xa laser", None))
        self.toolButton_sightup.setText(QCoreApplication.translate("MainWindow", u"Ch\u1ec9nh l\u00ean", None))
        self.toolButton_sight_right.setText(QCoreApplication.translate("MainWindow", u"Ch\u1ec9nh xu\u1ed1ng", None))
        self.bt_control_kv.setText(QCoreApplication.translate("MainWindow", u"K\u00ednh v\u1ea1ch", None))
        self.groupBox_17.setTitle(QCoreApplication.translate("MainWindow", u"Ch\u1ebf \u0111\u1ed9 \u0110K:", None))
        self.bt_zero_set_3.setText(QCoreApplication.translate("MainWindow", u"Joystick", None))
        self.bt_control_usb.setText(QCoreApplication.translate("MainWindow", u"USB", None))
        self.bt_control_usb_2.setText(QCoreApplication.translate("MainWindow", u"B\u00e0n ph\u00edm", None))
        self.bt_stab_2.setText(QCoreApplication.translate("MainWindow", u"Stab 2", None))
        self.bt_video_test_2.setText(QCoreApplication.translate("MainWindow", u"T\u1eaft STAB", None))
        self.bt_tracksizeup_2.setText(QCoreApplication.translate("MainWindow", u"Gi\u1ea3m \u00f4 b\u00e1m", None))
        self.bt_tracksizeup.setText(QCoreApplication.translate("MainWindow", u"T\u0103ng \u00f4 b\u00e1m", None))
        self.toolButton_show_setup.setText(QCoreApplication.translate("MainWindow", u"C\u00e0i \u0111\u1eb7t", None))
        self.groupBox_10.setTitle(QCoreApplication.translate("MainWindow", u"K\u1ebft n\u1ed1i:", None))
        self.label_stim_stat.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_cu_connection.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_video_fps_3.setText(QCoreApplication.translate("MainWindow", u"CU:", None))
        self.label_video_fps_5.setText(QCoreApplication.translate("MainWindow", u"GYRO:", None))
        self.label_video_fps_17.setText(QCoreApplication.translate("MainWindow", u"MCU 1:", None))
        self.label_video_fps_18.setText(QCoreApplication.translate("MainWindow", u"MCU 2:", None))
        self.label_plc_1.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_plc2.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.connectButton.setText(QCoreApplication.translate("MainWindow", u"N\u1ed1i PLC", None))
        self.groupBox_11.setTitle(QCoreApplication.translate("MainWindow", u"Video", None))
        self.pushButton_play_video.setText(QCoreApplication.translate("MainWindow", u"Open video", None))
        self.pushButton_record.setText(QCoreApplication.translate("MainWindow", u"Ghi l\u01b0u", None))
        self.pushButton_power_off.setText(QCoreApplication.translate("MainWindow", u"Stop replay", None))
        self.groupBox_9.setTitle(QCoreApplication.translate("MainWindow", u"FPS:", None))
        self.label_video_fps_2.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_video_fps.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_track_y.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_track_x.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"FOV(\u0111\u1ed9):", None))
        self.label_speed.setText(QCoreApplication.translate("MainWindow", u"00", None))
        self.image_label_8.setText(QCoreApplication.translate("MainWindow", u"Ch\u1ebf \u0111\u1ed9:", None))
        self.image_label_10.setText(QCoreApplication.translate("MainWindow", u"\u0110\u1ea1n:", None))
        self.image_label_9.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.image_label_12.setText(QCoreApplication.translate("MainWindow", u"S\u1eb5n s\u00e0ng:", None))
        self.image_label_11.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.image_label_13.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_fov.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_speed_2.setText(QCoreApplication.translate("MainWindow", u"T\u1ed1c \u0111\u1ed9 xe(km/h):", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"C\u1ef1 ly(m):", None))
        self.label_range.setText(QCoreApplication.translate("MainWindow", u"--", None))
        self.label_fovSpeed.setText(QCoreApplication.translate("MainWindow", u"00", None))
        self.label_video_fps_8.setText(QCoreApplication.translate("MainWindow", u"-15", None))
        self.label_video_fps_14.setText(QCoreApplication.translate("MainWindow", u"0", None))
        self.label_video_fps_10.setText(QCoreApplication.translate("MainWindow", u"30", None))
        self.label_video_fps_12.setText(QCoreApplication.translate("MainWindow", u"60", None))
        self.groupBox_4.setTitle(QCoreApplication.translate("MainWindow", u"Th\u00f4ng b\u00e1o", None))
        self.pushButton_clear_msg.setText(QCoreApplication.translate("MainWindow", u"Clear", None))
    # retranslateUi

