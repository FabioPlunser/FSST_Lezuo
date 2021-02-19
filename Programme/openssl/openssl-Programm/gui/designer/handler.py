import os

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *

from ..designer.ui_main import Ui_MainWindow

class Handler():
    def __init__(self):
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

    def start_c_programm(self):
        pass