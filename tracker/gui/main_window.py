#!/usr/bin/env python3
# main.py

import sys
from PySide2.QtWidgets import QApplication, QMainWindow
from ui_window import Ui_main_window


class MainWindow(QMainWindow, Ui_main_window):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
