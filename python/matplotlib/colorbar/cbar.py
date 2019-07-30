#! /usr/bin/python
from __future__ import print_function
import sys
from compiler.ast import Power

from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QVBoxLayout, QWidget
import matplotlib as mpl
mpl.use("Qt5Agg")

from matplotlib.backends.backend_qt5agg import (
    FigureCanvasQTAgg as FigureCanvas)
from matplotlib.cm import ScalarMappable, get_cmap
from matplotlib.colors import Normalize, SymLogNorm, PowerNorm, LogNorm
from matplotlib.figure import Figure
import matplotlib.ticker as ticker
import matplotlib.scale as scale
import matplotlib.pyplot as plt

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
        self.mappable = ScalarMappable(norm=Normalize(vmin=-31.709, vmax=4399.65),
                                  cmap=DEFAULT_CMAP)
        self.mappable.set_array([])
        fig.colorbar(self.mappable, ax=self.cb_axes, cax=self.cb_axes)

    def _update_cb_scale(self):
        # check if the new mappable is valid
        updated_norm = PowerNorm(2, -1, 1)
        #scale_min, scale_max = updated_norm(updated_norm.vmin), updated_norm(updated_norm.vmax)
        #updated_norm.vmin = scale_min
        #updated_norm.vmax = scale_max
        #updated_norm.autoscale_None([-1, 1])
        updated_norm.autoscale([-1, 1])
        updated_mappable = ScalarMappable(norm=updated_norm,
                                          cmap=DEFAULT_CMAP)
        updated_mappable.set_array([])

        # this removes the axis too
        self.mappable.colorbar.remove()
        rect = 0.25, 0.05, 0.1, 0.90
        self.cb_axes = self.canvas.figure.add_axes(rect)
        self.mappable = updated_mappable
        # self.canvas.figure.colorbar(self.mappable, ax=self.cb_axes, cax=self.cb_axes,
        #                             ticks=ticker.SymmetricalLogLocator(transform=scale.SymmetricalLogTransform(10, 0.0001, 0.1)),
        #                             format=ticker.LogFormatterMathtext())
        self.canvas.figure.colorbar(self.mappable, ax=self.cb_axes, cax=self.cb_axes)
        self.canvas.draw()


if __name__ == '__main__':
    qapp = QApplication(sys.argv)
    mainwin = MainWindow()
    mainwin.show()
    sys.exit(qapp.exec_())
