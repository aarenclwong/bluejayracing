# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'window.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_screen(object):
    def setupUi(self, screen):
        screen.setObjectName("screen")
        screen.setEnabled(True)
        screen.resize(800, 480)
        self.background = QtWidgets.QWidget(screen)
        self.background.setEnabled(True)
        self.background.setGeometry(QtCore.QRect(0, 0, 800, 480))
        self.background.setStyleSheet("QWidget#background{\n"
"background-color: qconicalgradient(cx:0.485, cy:0.499909, angle:227.4, stop:0.278607 rgba(66, 66, 66, 255), stop:0.875622 rgba(43, 43, 43, 255));}")
        self.background.setObjectName("background")
        self.rpm_label = QtWidgets.QLabel(self.background)
        self.rpm_label.setGeometry(QtCore.QRect(150, 100, 91, 48))
        self.rpm_label.setAutoFillBackground(False)
        self.rpm_label.setObjectName("rpm_label")
        self.speed_label = QtWidgets.QLabel(self.background)
        self.speed_label.setGeometry(QtCore.QRect(500, 100, 123, 48))
        self.speed_label.setObjectName("speed_label")
        self.rpm_widget = QtWidgets.QLabel(self.background)
        self.rpm_widget.setEnabled(True)
        self.rpm_widget.setGeometry(QtCore.QRect(90, 210, 200, 200))
        self.rpm_widget.setText("")
        self.rpm_widget.setScaledContents(True)
        self.rpm_widget.setObjectName("rpm_widget")
        self.speed_widget = QtWidgets.QLabel(self.background)
        self.speed_widget.setGeometry(QtCore.QRect(470, 220, 200, 200))
        self.speed_widget.setText("")
        self.speed_widget.setScaledContents(True)
        self.speed_widget.setObjectName("speed_widget")

        self.retranslateUi(screen)
        QtCore.QMetaObject.connectSlotsByName(screen)

    def retranslateUi(self, screen):
        _translate = QtCore.QCoreApplication.translate
        screen.setWindowTitle(_translate("screen", "Dialog"))
        self.rpm_label.setText(_translate("screen", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600; color:#ffffff;\">RPM</span></p></body></html>"))
        self.speed_label.setText(_translate("screen", "<html><head/><body><p><span style=\" font-size:24pt; font-weight:600; color:#ffffff;\">Speed</span></p></body></html>"))
