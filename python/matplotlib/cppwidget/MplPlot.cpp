#include "MplPlot.h"

#include "sipAPI_mplcpp.h"

#include <QVBoxLayout>

PyMODINIT_FUNC init_mplcpp();

// -----------------------------------------------------------------------------
MplPlot::MplPlot(QWidget *parent) : QWidget(parent) {
  // Create vertical layout
  setLayout(new QVBoxLayout);

  // Init sip stuff
  init_mplcpp();
  PyObject *mpl_qt4backend = PyImport_ImportModule("matplotlib.backends.backend_qt4agg");
  assert(mpl_qt4backend);
  PyObject *mpl_figure = PyImport_ImportModule("matplotlib.figure");
  assert(mpl_figure);
  PyObject *numpy = PyImport_ImportModule("numpy");

  PyObject *figure = PyObject_CallObject(PyObject_GetAttrString(mpl_figure, "Figure"), nullptr);
  PyObject *axes = PyObject_CallMethod(figure, "add_subplot", "(iii)", 1,1,1);
  PyObject *xdata = PyObject_CallMethod(numpy, "arange", "(iid)", 1,101,0.01);
  PyObject_CallMethodObjArgs(axes, PyString_FromString("plot"), xdata, xdata, NULL);
  PyObject *fig_canvas_attr = PyObject_GetAttrString(mpl_qt4backend, "FigureCanvasQTAgg");
  PyObject *figure_canvas = PyObject_CallMethod(mpl_qt4backend, "FigureCanvasQTAgg", "(O)", figure);

  PyObject *pyself = self();
  PyObject *layout_attr = PyObject_GetAttrString(pyself, "layout");
  PyObject *layout = PyObject_CallObject(layout_attr, nullptr);

  PyObject_CallMethod(layout, "addWidget", "(O)", figure_canvas);
  PyObject_CallMethod(figure_canvas, "draw", NULL);

  Py_DECREF(pyself);
  Py_DECREF(mpl_figure);
  Py_DECREF(mpl_qt4backend);
}

// -----------------------------------------------------------------------------
PyObject *MplPlot::self() {
  static sipWrapperType *sipClass(nullptr);
  if (!sipClass) {
    sipClass = sipFindClass("MplPlot");
  }
  PyObject *sip_wrapped = sipConvertFromInstance(this, sipClass, NULL);
  assert(sip_wrapped);
  return sip_wrapped;
}
