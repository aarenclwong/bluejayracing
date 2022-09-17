# This is a sample Python script.

# Press Shift+F10 to execute it or replace it with your code.
# Press Double Shift to search everywhere for classes, files, tool windows, actions, and settings.
import PyQt5
from PyQt5.QtWidgets import QApplication, QMainWindow
import sys


class Window(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setGeometry(300, 300, 600, 400)
        self.setWindowTitle("PyQt5 window")
        self.init_ui()

    def init_ui(self):
        self.label = PyQt5.QtWidgets.QLabel(self)
        self.label.setText("hi")
        self.label.move(200,200)

        self.modeButton = PyQt5.QtWidgets.QPushButton(self)
        self.modeButton.setText("Advanced Mode")
        self.modeButton.clicked.connect(self.adv_mode)

        self.show()

    def adv_mode(self):
        self.label.setText("Advanced Mode")
        self.update()

    def update(self):
        self.label.adjustSize()
        self.modeButton.adjustSize()

app = QApplication(sys.argv)
window = Window()
sys.exit(app.exec_())
