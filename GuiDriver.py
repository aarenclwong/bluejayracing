from content.driver_gui import Ui_DriverGui as window
from SimpleGuiDriver import GuiDriver as simple
from content.simple_window import Ui_screen as simple_ui
from AdvancedGuiDriver import GuiDriver as advanced
from PyQt5 import QtWidgets as qtw
from PyQt5.QtCore import Qt


class GuiDriver(qtw.QWidget):
    def __init__(self):
        super().__init__()
        #self.setWindowFlag(Qt.FramelessWindowHint)

        self.ui = window()
        self.ui.setupUi(self)

        self.ui.simple = simple()
        self.ui.advanced = advanced()
        self.ui.stackedWidget.addWidget(self.ui.simple)
        self.ui.stackedWidget.addWidget(self.ui.advanced)

        self.window = 0

        self.ui.switchMode.clicked.connect(self._switchWindow)

    def _switchWindow(self):
        self.ui.stackedWidget.setCurrentIndex(int(not self.window))
        self.window = int(not(bool(self.window)))

    def setRPM(self, rpm):
        self.ui.simple.setRPM(rpm)
        self.ui.advanced.setRPM(rpm)

    def setSpeed(self, speed):
        self.ui.simple.setSpeed(speed)
        self.ui.advanced.setSpeed(speed)
