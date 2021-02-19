import sys

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


from .designer.ui_main import Ui_MainWindow


def close_app(app):
    app.exec_()

def run_app():
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(close_app(app))

class MainWindow(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)

        self.ui = Ui_MainWindow()       #Ui_MainWindow is created class from QTDesigner
        self.ui.setupUi(self)           #initialize class
        self.show()                     #"render" GUI