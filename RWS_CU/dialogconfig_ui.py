# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'dialogconfig.ui'
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
from PySide6.QtWidgets import (QApplication, QDialog, QGridLayout, QHeaderView,
    QLabel, QLineEdit, QPushButton, QSizePolicy,
    QTableWidget, QTableWidgetItem, QWidget)

class Ui_DialogConfig(object):
    def setupUi(self, DialogConfig):
        if not DialogConfig.objectName():
            DialogConfig.setObjectName(u"DialogConfig")
        DialogConfig.resize(1048, 480)
        self.gridLayout = QGridLayout(DialogConfig)
        self.gridLayout.setObjectName(u"gridLayout")
        self.tableWidget = QTableWidget(DialogConfig)
        if (self.tableWidget.columnCount() < 2):
            self.tableWidget.setColumnCount(2)
        __qtablewidgetitem = QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(0, __qtablewidgetitem)
        __qtablewidgetitem1 = QTableWidgetItem()
        self.tableWidget.setHorizontalHeaderItem(1, __qtablewidgetitem1)
        self.tableWidget.setObjectName(u"tableWidget")
        self.tableWidget.setSortingEnabled(True)
        self.tableWidget.horizontalHeader().setVisible(False)
        self.tableWidget.horizontalHeader().setCascadingSectionResizes(False)
        self.tableWidget.horizontalHeader().setMinimumSectionSize(30)
        self.tableWidget.horizontalHeader().setDefaultSectionSize(200)
        self.tableWidget.horizontalHeader().setHighlightSections(True)
        self.tableWidget.horizontalHeader().setStretchLastSection(True)

        self.gridLayout.addWidget(self.tableWidget, 0, 0, 1, 4)

        self.pushButton_save = QPushButton(DialogConfig)
        self.pushButton_save.setObjectName(u"pushButton_save")

        self.gridLayout.addWidget(self.pushButton_save, 1, 1, 1, 1)

        self.lineEdit = QLineEdit(DialogConfig)
        self.lineEdit.setObjectName(u"lineEdit")
        self.lineEdit.setEchoMode(QLineEdit.Password)
        self.lineEdit.setCursorMoveStyle(Qt.VisualMoveStyle)

        self.gridLayout.addWidget(self.lineEdit, 1, 3, 1, 1)

        self.label = QLabel(DialogConfig)
        self.label.setObjectName(u"label")

        self.gridLayout.addWidget(self.label, 1, 2, 1, 1)


        self.retranslateUi(DialogConfig)

        QMetaObject.connectSlotsByName(DialogConfig)
    # setupUi

    def retranslateUi(self, DialogConfig):
        DialogConfig.setWindowTitle(QCoreApplication.translate("DialogConfig", u"C\u00e0i \u0111\u1eb7t tham s\u1ed1", None))
        ___qtablewidgetitem = self.tableWidget.horizontalHeaderItem(0)
        ___qtablewidgetitem.setText(QCoreApplication.translate("DialogConfig", u"Tham s\u1ed1", None));
        ___qtablewidgetitem1 = self.tableWidget.horizontalHeaderItem(1)
        ___qtablewidgetitem1.setText(QCoreApplication.translate("DialogConfig", u"Gi\u00e1 tr\u1ecb", None));
        self.pushButton_save.setText(QCoreApplication.translate("DialogConfig", u"Save", None))
        self.lineEdit.setInputMask("")
        self.label.setText(QCoreApplication.translate("DialogConfig", u"Nh\u1eadp m\u1eadt kh\u1ea9u \u0111\u1ec3 l\u01b0u b\u1ea3ng tham s\u1ed1:", None))
    # retranslateUi

