"""
    Hacky script to plot a sample cube with a ray-tracing track
    to visualize where the interaction occurs
"""
# -*- coding: utf-8 -*-
from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()
ax = fig.gca(projection='3d')
ax.set_aspect("equal")

# draw cuboid at centre
height = 0.05  # y-dir (m)
width = 0.05  # x-dir (m)
thick = 0.001  # z-dir (m)
half_height, half_width, half_thick = 0.5*height, 0.5*width, 0.5*thick
min, max = [-half_width, -half_height, -half_thick], [half_width, half_height, half_thick]


# draw cuboid
# Up struts
ax.plot3D(xs=(min[0], min[0]), ys=(min[1], min[1]), zs=(min[2], max[2]), color="b")
ax.plot3D(xs=(max[0], max[0]), ys=(max[1], max[1]), zs=(min[2], max[2]), color="b")
ax.plot3D(xs=(min[0], min[0]), ys=(max[1], max[1]), zs=(min[2], max[2]), color="b")
ax.plot3D(xs=(max[0], max[0]), ys=(min[1], min[1]), zs=(min[2], max[2]), color="b")
# Connect the tops
ax.plot3D(xs=(min[0], max[0]), ys=(max[1], max[1]), zs=(max[2], max[2]), color="b")
ax.plot3D(xs=(min[0], max[0]), ys=(min[1], min[1]), zs=(max[2], max[2]), color="b")
ax.plot3D(xs=(min[0], min[0]), ys=(min[1], max[1]), zs=(max[2], max[2]), color="b")
ax.plot3D(xs=(max[0], max[0]), ys=(min[1], max[1]), zs=(max[2], max[2]), color="b")
# Connect the bottoms
ax.plot3D(xs=(min[0], max[0]), ys=(max[1], max[1]), zs=(min[2], min[2]), color="b")
ax.plot3D(xs=(min[0], max[0]), ys=(min[1], min[1]), zs=(min[2], min[2]), color="b")
ax.plot3D(xs=(min[0], min[0]), ys=(min[1], max[1]), zs=(min[2], min[2]), color="b")
ax.plot3D(xs=(max[0], max[0]), ys=(min[1], max[1]), zs=(min[2], min[2]), color="b")

# draw scatter point
scatter_pt = [-0.02499360863727253, 0.0028527463411453266, -0.00049252402700947716]
ax.scatter(scatter_pt[0], scatter_pt[1], scatter_pt[2], color="g", s=10)

# draw detector pos
det_pos = [-0.53173036172566235, 0.32470189779965286, 0.42478704911668153]
#ax.scatter(det_pos[0], det_pos[1], det_pos[2], color="g", s=10)

#draw a vector
from matplotlib.patches import FancyArrowPatch
from mpl_toolkits.mplot3d import proj3d

class Arrow3D(FancyArrowPatch):
    def __init__(self, xs, ys, zs, *args, **kwargs):
        FancyArrowPatch.__init__(self, (0,0), (0,0), *args, **kwargs)
        self._verts3d = xs, ys, zs

    def draw(self, renderer):
        xs3d, ys3d, zs3d = self._verts3d
        xs, ys, zs = proj3d.proj_transform(xs3d, ys3d, zs3d, renderer.M)
        self.set_positions((xs[0],ys[0]),(xs[1],ys[1]))
        FancyArrowPatch.draw(self, renderer)


direc = np.array(scatter_pt) - np.array(det_pos)
norm2 = np.dot(direc, direc)
direc = direc/np.sqrt(norm2)
arrow_length = 0.1

a = Arrow3D([scatter_pt[0] - direc[0]*0.5*arrow_length, scatter_pt[0] + direc[0]*0.5*arrow_length],
            [scatter_pt[1] - direc[1]*0.5*arrow_length, scatter_pt[1] + direc[1]*0.5*arrow_length],
            [scatter_pt[2] - direc[2]*0.5*arrow_length, scatter_pt[2] + direc[2]*0.5*arrow_length],
            mutation_scale=20, lw=1, arrowstyle="-|>", color="k")
#ax.set_zlim3d(min[2], max[2])
ax.add_artist(a)
plt.show()
