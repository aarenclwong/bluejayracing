from GuiDriver import GuiDriver
from PyQt5 import QtWidgets as qtw

if __name__ == '__main__':
    app = qtw.QApplication([])
    widget = GuiDriver()
    widget.show()
    app.exec_()


for i in range(0, 1000000):
    widget.setRPM(i)