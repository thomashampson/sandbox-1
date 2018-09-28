#! /usr/bin/python
from __future__ import print_function
import sys

from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget

from matplotlib.backends.backend_qt5agg import (
    FigureCanvasQTAgg as FigureCanvas)
from matplotlib.cm import ScalarMappable, get_cmap
from matplotlib.colors import Normalize
from matplotlib.figure import Figure

import numpy as np

DEFAULT_CMAP = get_cmap('viridis')


class MainWindow(QMainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle('ColorBar Example')
        self.setCentralWidget(ColorbarWidget())


class ColorbarWidget(QWidget):

    def __init__(self, parent=None):
        super(ColorbarWidget, self).__init__(parent)
        fig = Figure()
        rect = 0.25, 0.05, 0.1, 0.90
        self.cb_axes = fig.add_axes(rect)
        self.canvas = FigureCanvas(fig)
        self.setLayout(QVBoxLayout())
        self.layout().addWidget(self.canvas)
        self.button = QPushButton("Update")
        self.layout().addWidget(self.button)
        self.button.pressed.connect(self._update_cb_scale)

        self._create_colorbar(fig)

    def _create_colorbar(self, fig):
        self.mappable = ScalarMappable(norm=Normalize(vmin=-1., vmax=1.),
                                  cmap=DEFAULT_CMAP)
        self.mappable.set_array([])
        self.cb = fig.colorbar(self.mappable, ax=self.cb_axes, cax=self.cb_axes)

    def _update_cb_scale(self):
        self.mappable.set_clim(30, 4300)
        self.canvas.draw()




if __name__ == '__main__':
    qapp = QApplication(sys.argv)
    mainwin = MainWindow()
    mainwin.show()
    sys.exit(qapp.exec_())
