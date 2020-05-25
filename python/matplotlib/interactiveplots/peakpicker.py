#!/usr/bin/env python
"""Prototype matplotlib graph with interactive fitting region markers
"""
from __future__ import print_function


from PyQt5.QtCore import QEvent, QObject, Qt, pyqtSignal
from PyQt5.QtWidgets import QApplication, QLineEdit, QTableWidgetItem
from PyQt5.uic import loadUiType

from matplotlib.backend_bases import (MouseEvent)

from matplotlib.backends.backend_qt5agg import (
    FigureCanvasQTAgg as FigureCanvas,
    NavigationToolbar2QT as NavigationToolbar)
from matplotlib.figure import Figure
from matplotlib.lines import Line2D

import numpy as np

# Process .ui file
Ui_MainWindow, QMainWindow = loadUiType('mainwindow.ui')

class MouseClickMonitor(QObject):

    def __init__(self, canvas):
        super(MouseClickMonitor, self).__init__()
        self.canvas = canvas

    def eventFilter(self, obj, event):
        if event.type() == QEvent.MouseButtonDblClick:
            x, y = self.canvas.mouseEventCoords(event.pos())
            print(self.canvas.figure.axes[0].title.contains(MouseEvent('foo', x, y, dblclick=True)))
            return True
        else:
            return super(MouseClickMonitor, self).eventFilter(obj, event)


#class InlineLabelEditor(QLineEdit):

#    def __init__(self, canvas, artist):




# ------------------------------------------------------------------------------
class MainWindow(QMainWindow, Ui_MainWindow):

    def __init__(self):
        super(MainWindow, self).__init__()
        self.setupUi(self)
        self.setWindowTitle('Fit Window')

        self._create_mplplot()
        self._peak_picker = self._create_peak_picker(self._canvas)

        self._onpick = self._canvas.mpl_connect('pick_event',
                                                self._on_pick)


    def _create_mplplot(self):
        x = np.arange(1,101, 0.01)
        mu, sigma = 50, 5
        y = np.exp( - (x - mu)**2 / (2 * sigma**2))
        fig = Figure()
        axes = fig.add_subplot(111)
        axes.plot(x, y, color='black')
        axes.set_title('Text', y=1.02)

        self._canvas = FigureCanvas(fig)
        print(dir(FigureCanvas))
        self._filter = MouseClickMonitor(self._canvas)
        self._canvas.installEventFilter(self._filter)
        self.mpllayout.addWidget(self._canvas)
        self._canvas.draw()
        return fig

    def _create_peak_picker(self, canvas):
        picker = PeakPickerTool(canvas)
        self.on_region_update(picker.lines[0].get_xdata()[0],
                              picker.lines[1].get_xdata()[0])
        picker.region_updated.connect(self.on_region_update)
        return picker

    def _on_pick(self, evt):
        if not evt.mouseevent.dblclick:
            return
        print(dir(evt.artist.get_text()))
        # print("Title double clicked at matplotlib coords",evt.mouseevent.x, evt.mouseevent.y)
        # print("Canvas width=",self._canvas.width(), "height=", self._canvas.height())
        # editor = QLineEdit(self._canvas)
        # editor.setAttribute(Qt.WA_DeleteOnClose)
        # editor.setText(self._canvas.figure.get_axes()[0].get_title())
        # self._canvas.figure.get_axes()[0].set_title('')
        # self._canvas.draw()
        # editor.move(evt.mouseevent.x - (0.5*editor.width()), self._canvas.height() - evt.mouseevent.y - 0.5*editor.height())
        # editor.show()
        # self._editor = editor


    def on_region_update(self, leftx, rightx):
        self.table_widget.setItem(0, 1, QTableWidgetItem(str(leftx)))
        self.table_widget.setItem(1, 1, QTableWidgetItem(str(rightx)))


# ------------------------------------------------------------------------------

class PeakPickerTool(QObject):

    # Indicates that the region has been updated
    region_updated = pyqtSignal(float, float)

    def __init__(self, canvas, init_indent=0.1):
        super(PeakPickerTool, self).__init__()
        self._canvas = canvas
        self._line_clicked = None

        figure = canvas.figure
        ax = figure.axes[0]

        xrange = ax.get_xlim()
        abs_indent = init_indent*(xrange[1] - xrange[0])
        init_xleft, init_xright = xrange[0] + abs_indent, xrange[1] - abs_indent
        left, right = \
            self._create_region_markers(figure, init_xleft, init_xright, ax.get_ylim())
        # The order here is important when checking what was clicked
        # There is probabaly a more intelligent way to to this
        self.lines = [left, right]
        ax.add_line(left)
        ax.add_line(right)
        canvas.draw()

        self.mpl_connect()

    def _create_region_markers(self, fig, xleft, xright, yrange):
        left = Line2D([xleft, xleft], yrange,
                      figure=fig, linestyle='--', picker=True)
        right = Line2D([xright, xright], yrange,
                       figure=fig, linestyle='--', picker=True)
        return left, right

    def mpl_connect(self):
        self._cid_press = self._canvas.mpl_connect('button_press_event',
                                                   self._on_button_press)
        self._cid_release = self._canvas.mpl_connect('button_release_event',
                                                     self._on_button_release)
        self._cid_move = self._canvas.mpl_connect('motion_notify_event',
                                                  self._on_mousemove)

    def mpl_disconnect(self):
        self._canvas.mpl_disconnect(self.cid_press)
        self._canvas.mpl_disconnect(self.cid_release)
        self._canvas.mpl_disconnect(self.cid_move)

    def _on_button_press(self, event):
        # Artist.picker is only set to true for the Line2D objects
        # In the more general case we'd probably need to discriminate more
        self._line_clicked = None
        if event.inaxes is None:
            return
        for i, _ in enumerate(self.lines):
            contains, _ = self.lines[i].contains(event)
            if contains:
                self._line_clicked = i
                return

    def _on_button_release(self, event):
        self._line_clicked = None

    def _on_mousemove(self, event):
        if self._line_clicked is None:
            return
        self.lines[self._line_clicked].set_xdata([event.xdata, event.xdata])
        self._canvas.draw()
        self.region_updated.emit(self.lines[0].get_xdata()[0], self.lines[1].get_xdata()[0])

# ------------------------------------------------------------------------------

if __name__ == '__main__':
    import sys
    qapp = QApplication(sys.argv)
    mainwin = MainWindow()
    mainwin.show()
    sys.exit(qapp.exec_())
