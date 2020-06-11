import numpy as np
import matplotlib.cm as cm
import matplotlib.pyplot as plt
from matplotlib.transforms import Bbox, BboxTransform
from matplotlib.widgets import RectangleSelector
import numpy as np


delta = 0.025
x = y = np.arange(-3.0, 3.0, delta)
X, Y = np.meshgrid(x, y)
Z1 = np.exp(-X**2 - Y**2)
Z2 = np.exp(-(X - 1)**2 - (Y - 1)**2)
Z = (Z1 - Z2) * 2

fig, (ax1, ax2) = plt.subplots(1,2)
im = ax1.imshow(Z, interpolation='bilinear', cmap=cm.RdYlGn,
               origin='lower', extent=[-3, 3, -3, 3],
               vmax=abs(Z).max(), vmin=-abs(Z).max())


def line_select_callback(eclick, erelease):
    'eclick and erelease are the press and release events'
    x1, y1 = eclick.xdata, eclick.ydata
    x2, y2 = erelease.xdata, erelease.ydata

    xmin, xmax, ymin, ymax = im.get_extent()
    arr = im.get_array()
    data_extent = Bbox([[ymin, xmin], [ymax, xmax]])
    array_extent = Bbox([[0, 0], arr.shape[:2]])
    trans = BboxTransform(boxin=data_extent, boxout=array_extent)
    i1, j1 = trans.transform_point([y1, x1]).astype(int)
    i2, j2 = trans.transform_point([y2, x2]).astype(int)

    xx = np.linspace(xmin, xmax, arr.shape[1])
    ax2.clear()
    ax2.plot(xx[j1:j2], np.sum(arr[j1:j2, i1:i2], axis=1))
    ax2.autoscale()
    fig.canvas.draw_idle()
    #print("ycut:",np.sum(arr[i1:i2, j1:j2], axis=0))


# drawtype is 'box' or 'line' or 'none'
RS = RectangleSelector(ax1, line_select_callback,
                       drawtype='box', useblit=True,
                       button=[1],  # don't use middle button
                       minspanx=5, minspany=5,
                       spancoords='pixels',
                       interactive=True)

plt.show()
