from __future__ import unicode_literals
from collections import namedtuple
from enum import Enum
from typing import Optional, Tuple, Callable

import sys
import os
import random
import matplotlib
from matplotlib.image import AxesImage
from matplotlib.transforms import Bbox, BboxTransform

# Make sure that we are using QT5
matplotlib.use('Qt5Agg')
# Uncomment this line before running, it breaks sphinx-gallery builds
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import QPoint

import numpy as np
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.figure import Figure

progname = os.path.basename(sys.argv[0])
progversion = "0.1"

class MyMplCanvas(FigureCanvas):
    """Ultimately, this is a QWidget (as well as a FigureCanvasAgg, etc.)."""

    def __init__(self, parent=None, width=5, height=4, dpi=100):
        fig = Figure(figsize=(width, height), dpi=dpi)
        self.axes = fig.add_subplot(111)

        self.compute_initial_figure()

        FigureCanvas.__init__(self, fig)
        self.setParent(parent)

        FigureCanvas.setSizePolicy(self,
                                   QtWidgets.QSizePolicy.Expanding,
                                   QtWidgets.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)

    def compute_initial_figure(self):
        pass


class Direction(Enum):
    Up = 1,
    Down = 2,
    Left = 3,
    Right = 4


class PixelPositionTransform:
    """
    Define a transformation that computes the new position on an image grid
    that will take that position to the next pixel in a given direction.
    The __call__ method expects a derived type to implement the actual
    computation of the new data coordinates
    """

    def __init__(self, image: AxesImage,
                 new_pixel: Callable[[float, float], Tuple[float, float]]):
        """
        :param image: A reference to the image the cursor hovers over
        """
        self.new_pixel = new_pixel
        axes = image.axes
        self.data_to_display_trans = axes.transData
        self.display_to_data_trans = axes.transData.inverted()
        # compute pixel widths, assuming a regular grid
        extent = image.get_extent()
        xmin, xmax, ymin, ymax = extent
        arr = image.get_array()
        self.delta_x, self.delta_y = (xmax - xmin)/arr.shape[1], (ymax - ymin)/arr.shape[0]
        self.canvas = image.axes.figure.canvas

    def transform_point(self, pos: QPoint) -> QPoint:
        """
        Given the position of a cursor on the given image move
        the cursor to the next pixel. The actual transforms should
        be implemented in derived classes.
        :param pos: Cursor position in global Qt logical pixel coordinates
        :return: The new position in Qt logical pixel coordinates
        """
        canvas = self.canvas
        xdisp, ydisp = canvas.mouseEventCoords(canvas.mapFromGlobal(pos))
        xdata, ydata = self.display_to_data_trans.transform_point((xdisp, ydisp))
        xdata_new, ydata_new = self.new_pixel(xdata, ydata)
        xdisp_new, ydisp_new = self.data_to_display_trans.transform_point((xdata_new, ydata_new))
        return self.to_qt_global_coords(xdisp_new, ydisp_new)
   
    def to_qt_global_coords(self, xdisp: float, ydisp: float) -> QPoint:
        """
        Transform from matplotlib display coordinates to logical global Qt coordinates
        :param xdisp: X coordinates in display coordinates
        :param ydisp: Y coordinates in dsiplay coorindates
        """
        canvas = self.canvas
        dpi_ratio = canvas._dpi_ratio
        xp = xdisp/dpi_ratio
        yp = (canvas.figure.bbox.height - ydisp)/dpi_ratio
        return canvas.mapToGlobal(QPoint(int(xp), int(yp)))


class PixelPositionTransformUp(PixelPositionTransform):
    """
    Transform to compute the new position in data coordinates
    by moving up 1 pixel
    """
    def __init__(self, image: AxesImage):
        super().__init__(image, new_pixel=lambda x, y:  (x, y + self.delta_y))


class PixelPositionTransformDown(PixelPositionTransform):
    """Transform to compute the new position in data coordinates
    by moving down 1 pixel
    """
    def __init__(self, image: AxesImage):
        super().__init__(image, new_pixel=lambda x, y:  (x, y - self.delta_y))


class PixelPositionTransformLeft(PixelPositionTransform):
    """Transform to compute the new position in data coordinates
    by moving left 1 pixel
    """
    def __init__(self, image: AxesImage):
        super().__init__(image, new_pixel=lambda x, y:  (x - self.delta_x, y))


class PixelPositionTransformRight(PixelPositionTransform):
    """Transform to compute the new position in data coordinates
    by moving left 1 pixel
    """
    def __init__(self, image: AxesImage):
        super().__init__(image, new_pixel=lambda x, y:  (x + self.delta_x, y))




class MyStaticMplCanvas(MyMplCanvas):
    """Simple canvas with a sine plot."""

    PIXEL_TRANSFORM_CLS = {
        'up': PixelPositionTransformUp,
        'down': PixelPositionTransformDown,
        'left': PixelPositionTransformLeft,
        'right': PixelPositionTransformRight,
    }

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.mpl_connect('motion_notify_event', self._on_move)
        self.mpl_connect('key_release_event', self._on_key_release)

    def compute_initial_figure(self):
        Z = np.arange(50*50)
        Z = Z.reshape((50,50))
        self.image = self.axes.imshow(Z, origin='lower')

    def _on_move(self, evt):
        if evt.inaxes:
            print("Mouse move event ", evt.xdata, evt.ydata)

    def _on_key_release(self, evt):
        axes = evt.inaxes
        if axes is None:
            return

        pixel_transforms = self.PIXEL_TRANSFORM_CLS
        if evt.key in pixel_transforms:
            to_next_pixel = pixel_transforms[evt.key](self.image)
            QtGui.QCursor.setPos(to_next_pixel.transform_point(QtGui.QCursor.pos()))


# Data type to store information related to a cursor over an image
CursorInfo = namedtuple("CursorInfo", ("array", "extent", "point"))


def cursor_info(image, xdata, ydata):
    """Return information on the image for the given position in
    data coordinates.
    :param image: An instance of an image type
    :param xdata: X data coordinate of cursor
    :param xdata: Y data coordinate of cursor
    :return: None if point is not valid on the image else return CursorInfo type
    """
    extent = image.get_extent()
    xmin, xmax, ymin, ymax = extent
    arr = image.get_array()
    data_extent = Bbox([[ymin, xmin], [ymax, xmax]])
    array_extent = Bbox([[0, 0], arr.shape[:2]])
    trans = BboxTransform(boxin=data_extent, boxout=array_extent)
    point = trans.transform_point([ydata, xdata])
    if any(np.isnan(point)):
        return None

    point = point.astype(int)
    if 0 <= point[0] < arr.shape[0] and 0 <= point[1] < arr.shape[1]:
        return CursorInfo(array=arr, extent=extent, point=point)
    else:
        return None


class ApplicationWindow(QtWidgets.QMainWindow):
    def __init__(self):
        QtWidgets.QMainWindow.__init__(self)
        self.setAttribute(QtCore.Qt.WA_DeleteOnClose)
        self.setWindowTitle("application main window")

        self.file_menu = QtWidgets.QMenu('&File', self)
        self.file_menu.addAction('&Quit', self.fileQuit,
                                 QtCore.Qt.CTRL + QtCore.Qt.Key_Q)
        self.menuBar().addMenu(self.file_menu)

        self.help_menu = QtWidgets.QMenu('&Help', self)
        self.menuBar().addSeparator()
        self.menuBar().addMenu(self.help_menu)

        self.main_widget = QtWidgets.QWidget(self)

        l = QtWidgets.QVBoxLayout(self.main_widget)
        sc = MyStaticMplCanvas(self.main_widget, width=5, height=4, dpi=100)
        l.addWidget(sc)

        self.main_widget.setFocus()
        self.main_widget.setFocusProxy(sc)
        self.setCentralWidget(self.main_widget)

        self.statusBar().showMessage("All hail matplotlib!", 2000)

    def fileQuit(self):
        self.close()

    def closeEvent(self, ce):
        self.fileQuit()

qApp = QtWidgets.QApplication(sys.argv)

aw = ApplicationWindow()
aw.setWindowTitle("%s" % progname)
aw.show()
sys.exit(qApp.exec_())
