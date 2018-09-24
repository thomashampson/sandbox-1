#! /usr/bin/python
from __future__ import print_function
import sys

from PyQt5.QtWidgets import QApplication, QMainWindow

from matplotlib.backends.backend_qt5agg import (
    FigureCanvasQTAgg as FigureCanvas)
from matplotlib.cm import ScalarMappable, get_cmap
from matplotlib.colorbar import Colorbar
from matplotlib.colors import Normalize
from matplotlib.figure import Figure

import numpy as np

DEFAULT_CMAP = get_cmap('viridis')


class MainWindow(QMainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle('ColorBar Example')
        fig = Figure()
        rect = 0.25, 0.05, 0.1, 0.90
        self.cb_axes = fig.add_axes(rect)
        self.setCentralWidget(FigureCanvas(fig))

        self._create_colorbar()

    def _create_colorbar(self):
        self.mappable = ScalarMappable(norm=Normalize(vmin=-1., vmax=1.),
                                       cmap=DEFAULT_CMAP)
        # The array is required but does not affect the output:
        # https://stackoverflow.com/questions/28801803/matplotlib-scalarmappable-why-need-to-set-array-if-norm-set
        self.mappable.set_array([])
        self.colobar = Colorbar(ax=self.cb_axes,
                                mappable=self.mappable)


if __name__ == '__main__':
    qapp = QApplication(sys.argv)
    mainwin = MainWindow()
    mainwin.show()
    sys.exit(qapp.exec_())
