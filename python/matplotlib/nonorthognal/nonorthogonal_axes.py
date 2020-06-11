import numpy as np
import matplotlib.pyplot as plt
from matplotlib.transforms import Affine2D

from  mpl_toolkits.axisartist.grid_helper_curvelinear import GridHelperCurveLinear
from mpl_toolkits.axisartist import Subplot


def curvelinear_test1(fig):
    angle = np.radians(45.)
    def tr(x, y):
        x, y = np.asarray(x), np.asarray(y)
        return x + np.cos(angle) * y, np.sin(angle) * y

    def inv_tr(x, y):
        x, y = np.asarray(x), np.asarray(y)
        return x - y / np.tan(angle), y / np.sin(angle)

    grid_helper = GridHelperCurveLinear((tr, inv_tr))
    ax1 = Subplot(fig, 1, 1, 1, grid_helper=grid_helper)
    fig.add_subplot(ax1)

    xx, yy = tr([3, 6], [5.0, 10.])
    ax1.plot(xx, yy)

    ax1.set_aspect(1.)
    ax1.set_xlim(-10, 10.)
    ax1.set_ylim(-10, 10.)

    print(ax1.get_xlim())

    ax1.grid(True)

fig = plt.figure()
curvelinear_test1(fig)
plt.show()
