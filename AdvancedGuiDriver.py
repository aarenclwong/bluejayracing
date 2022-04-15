from content.advanced_window import Ui_screen as window
from content.rpm_dial import Ui_Form as rpm
from content.speed_dial import Ui_Form as speed
from PyQt5 import QtWidgets as qtw
from PyQt5.QtCore import Qt


class GuiDriver(qtw.QWidget):
    def __init__(self):
        super().__init__()
        #self.setWindowFlag(Qt.FramelessWindowHint)

        self.ui = window()
        self.ui.setupUi(self)

        self.speed_widget = speed()
        self.speed_widget.setupUi(self.ui.speed_widget)

        self.rpm_widget = rpm()
        self.rpm_widget.setupUi(self.ui.rpm_widget)

    def setRPM(self, rpm):
        self.rpm_widget.label.setText(str(rpm))