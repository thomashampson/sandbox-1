import numpy as np
import matplotlib.pyplot as plt
from matplotlib.transforms import Affine2D

from  mpl_toolkits.axisartist.grid_helper_curvelinear import GridHelperCurveLinear
from mpl_toolkits.axisartist import Subplot



# SKEW = 1,-0.562081,0.309295,0,0.827082,-0.466674,0,0,0.828585
# SKEW INVERTED = 1,0.679596,0.00947933,0,1.20907,0.68097,0,0,1.20688

SKEW = np.array([[1,-0.562081,0.309295],
                  [0,0.827082,-0.466674],
                  [0,0,0.828585]])
# INV_SKEW = np.array([[1,0.679596,0.00947933],
#                           [0,1.20907,0.68097],
#                           [0,0,1.20688]])

SKEW = np.array([[1,0,0],
                 [0,1,0],
                 [0,0,0.5]])
INV_SKEW = np.linalg.inv(SKEW)


def curvelinear_test1(fig):
    # def tr(x, y):
    #     x, y = np.asarray(x), np.asarray(y)
    #     xx, yy = np.empty_like(x), np.empty_like(y)
    #     nx = len(x)
    #     s = SKEW[:2, :2]
    #     for i in range(nx):
    #         xx[i] = x[i]
    #         yy[i] = y[i]

    #     return xx, yy

    # def inv_tr(x,y):
    #     x, y = np.asarray(x), np.asarray(y)
    #     xx, yy = np.empty_like(x), np.empty_like(y)
    #     nx = len(x)
    #     s = INV_SKEW[:2, :2]
    #     for i in range(nx):
    #         xx[i] = s[0][0]*x[i] + s[1][0]*y[i]
    #         yy[i] = s[0][1]*x[i] + s[1][1]*y[i]


    #     return xx, yy


    #grid_helper = GridHelperCurveLinear((tr, inv_tr))
    tr = Affine2D().rotate_deg(-30)
    grid_helper = GridHelperCurveLinear(tr)
    ax1 = Subplot(fig, 1, 1, 1, grid_helper=grid_helper)
    fig.add_subplot(ax1)

    #xx, yy = tr.transform([3, 6], [5.0, 10.])
    #ax1.plot(xx, yy)

    ax1.set_aspect(1.)
    ax1.set_xlim(-10, 10.)
    ax1.set_ylim(-10, 10.)

#    ax1.axis["t"]=ax1.new_floating_axis(0, 0.)
#    ax1.axis["t2"]=ax1.new_floating_axis(1, 0.)
    ax1.grid(True)

fig = plt.figure()
curvelinear_test1(fig)
plt.show()
