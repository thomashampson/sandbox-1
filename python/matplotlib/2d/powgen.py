import mantid.simpleapi as sapi
#import mantid.plots
import matplotlib as mpl
mpl.use('Qt5Agg')
import matplotlib.pyplot as plt
import matplotlib.artist as artist
import matplotlib.transforms as transforms
import matplotlib.path as path
import matplotlib.cm as cm
import matplotlib.collections as collections
import numpy
import time

# data = sapi.Load(Filename="~/Downloads/for_mpl.nxs")
# print("Data loaded")
# time.sleep(5)
# start_time = time.time()
#
# colors = data.extractY()
# print("colors extracted")
# time.sleep(5)
#
# plt.pcolor(colors)
# plt.show()

# (X, Y, Z ) = get_matrix_2d_data(data, False, True)
# get_data_time = time.time()
# plt.pcolormesh(X, Y, Z)
# plt.show()
# end_time = time.time()
# print("Get data time: {}s".format(get_data_time - start_time))
# print("Total time: {}s".format(end_time - start_time))

"""
Demonstrates similarities between pcolor, pcolormesh, imshow and pcolorfast
for drawing quadrilateral grids.

"""
import matplotlib.pyplot as plt
import numpy as np

# # make these smaller to increase the resolution
# dx, dy = 0.15, 0.05
#
# # generate 2 2d grids for the x & y bounds
# y, x = np.mgrid[slice(-3, 3 + dy, dy),
#                 slice(-3, 3 + dx, dx)]
# z = (1 - x / 2. + x ** 5 + y ** 3) * np.exp(-x ** 2 - y ** 2)
# # x and y are bounds, so z should be the value *inside* those bounds.
# # Therefore, remove the last value from the z array.
# z = z[:-1, :-1]
# z_min, z_max = -np.abs(z).max(), np.abs(z).max()

class WorkspaceArtist(collections.Collection):

    def __init__(self, workspace):
        collections.Collection.__init__(self)
        self._ws = workspace
        self._nspectra = self._ws.getNumberHistograms()
        ypts = self._ws.getAxis(1).extractValues()
        dy = 0.5*(ypts[1:] - ypts[:-1])
        edges = numpy.empty(len(ypts)+1)
        edges[0] = ypts[0] - dy[0]
        edges[-1] = ypts[-1] + dy[-1]
        edges[1:-1] = ypts[1:] - dy
        self._yvalues = edges
        self._meshWidth, self._meshHeight = workspace.blocksize(), 2
        self._antialiased = True
        self._shading = 'flat'

    @artist.allow_rasterization
    def draw(self, renderer):
        if not self.get_visible():
            return

        def get_spectrum_coords(i):
            xlower, xupper = self._ws.readX(i), self._ws.readX(i+1)
            y0, y1 = self._yvalues[i], self._yvalues[i+1]
            ylower = np.empty(xlower.shape)
            ylower.fill(y0)
            yupper = np.empty(xupper.shape)
            yupper.fill(y1)
            X = numpy.hstack((xlower, xupper))
            Y = numpy.hstack((ylower, yupper))
            coords = np.column_stack((X, Y)).astype(float, copy=False)
            coords = np.asarray(coords, float).reshape(
                (2, self._meshWidth + 1, 2))
            return coords

        for i in range(self._nspectra - 1):
            self.set_facecolor(self.to_rgba(self._ws.readY(i)))
            self.draw_mesh(renderer, get_spectrum_coords(i))

    @artist.allow_rasterization
    def draw_mesh(self, renderer, coordinates):
        renderer.open_group(self.__class__.__name__, self.get_gid())
        transform = self.get_transform()
        transOffset = self.get_offset_transform()
        offsets = self._offsets

        if self.have_units():
            if len(self._offsets):
                xs = self.convert_xunits(self._offsets[:, 0])
                ys = self.convert_yunits(self._offsets[:, 1])
                offsets = np.column_stack([xs, ys])

        self.update_scalarmappable()

        if not transform.is_affine:
            coordinates = coordinates.reshape((-1, 2))
            coordinates = transform.transform(coordinates)
            coordinates = coordinates.reshape(self._coordinates.shape)
            transform = transforms.IdentityTransform()
        # else:
        #     coordinates = self._coordinates

        if not transOffset.is_affine:
            offsets = transOffset.transform_non_affine(offsets)
            transOffset = transOffset.get_affine()

        gc = renderer.new_gc()
        self._set_gc_clip(gc)
        gc.set_linewidth(self.get_linewidth()[0])

        if self._shading == 'gouraud':
            triangles, colors = self.convert_mesh_to_triangles(
                self._meshWidth, self._meshHeight, coordinates)
            renderer.draw_gouraud_triangles(
                gc, triangles, colors, transform.frozen())
        else:
            renderer.draw_quad_mesh(
                gc, transform.frozen(), self._meshWidth, self._meshHeight,
                coordinates, offsets, transOffset, self.get_facecolor(),
                self._antialiased, self.get_edgecolors())
        gc.restore()
        renderer.close_group(self.__class__.__name__)
        self.stale = False

    def update_scalarmappable(self):
        pass


#data = sapi.Load(Filename="~/Downloads/for_mpl.nxs")
data = sapi.Load(Filename="~/Downloads/MAR21335_Ei60.00meV.nxs")

fig, ax = plt.subplots(1, 1)#subplot_kw={'projection':'mantid'})
# dx, dy = 1, 1
# y, x = np.mgrid[slice(-3, 3 + dy, dy),
#                 slice(-3, 3 + dx, dx)]
# z = (1 - x / 2. + x ** 5 + y ** 3) * np.exp(-x ** 2 - y ** 2)
# # # x and y are bounds, so z should be the value *inside* those bounds.
# # # Therefore, remove the last value from the z array.
# z = z[:-1, :-1]
# z_min, z_max = -np.abs(z).max(), np.abs(z).max()
#plt.pcolormesh(x, y, z, cmap='RdBu', vmin=z_min, vmax=z_max)

print(data.getNumberHistograms(), data.readX(0).shape[0],
      data.isHistogramData())
#ax.pcolormesh(data)

workspace_artist = WorkspaceArtist(data)
workspace_artist.set_alpha(1.0)
workspace_artist.set_array([])
#workspace_artist.set_cmap(cmap)
#workspace_artist.set_norm(norm)
#workspace_artist.set_clim(vmin, vmax)
workspace_artist.autoscale_None()

ax.add_artist(workspace_artist)

plt.show()