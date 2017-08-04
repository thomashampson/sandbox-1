#include "MplPlot.h"
#include "sip.h"
#include <QVBoxLayout>


static const sipAPIDef *sip_api()
{
  static const sipAPIDef *sip_API = 0;
  if (sip_API) return sip_API;
#if defined(SIP_USE_PYCAPSULE)
  sip_API = (const sipAPIDef *)PyCapsule_Import("sip._C_API", 0);
#else
  /* Import the SIP module. */
  PyObject * sip_module = PyImport_ImportModule("sip");
  if (sip_module == NULL) return NULL;

  /* Get the module's dictionary. */
  PyObject * sip_module_dict = PyModule_GetDict(sip_module);

  /* Get the "_C_API" attribute. */
  PyObject * c_api = PyDict_GetItemString(sip_module_dict, "_C_API");
  if (c_api == NULL) return NULL;

  /* Sanity check that it is the right type. */
  if (!PyCObject_Check(c_api)) return NULL;

  /* Get the actual pointer from the object. */
  sip_API = (const sipAPIDef *)PyCObject_AsVoidPtr(c_api);
#endif
  return sip_API;
}

static PyObject * incref(PyObject * object)
{
	Py_INCREF(object);
	return object;
}


void * sipUnwrap(PyObject *obj_ptr)
{
  if (!PyObject_TypeCheck(obj_ptr, sip_api()->api_wrapper_type))
    {
      PyErr_SetString(PyExc_TypeError, "Not a wrapped type");
      return nullptr;
     }

  // transfer ownership from python to C++
  sip_api()->api_transfer_to(obj_ptr, 0);
  // reinterpret to sipWrapper
  sipSimpleWrapper *wrapper = reinterpret_cast<sipSimpleWrapper*>(obj_ptr);
#if (SIP_API_MAJOR_NR == 8 && SIP_API_MINOR_NR >= 1) || SIP_API_MAJOR_NR > 8
  return sip_api()->api_get_address(wrapper);
#elif SIP_API_MAJOR_NR == 8
  return wrapper->data;
#else
  return wrapper->u.cppPtr;
#endif
}

//PyMODINIT_FUNC init_mplcpp();

// -----------------------------------------------------------------------------
MplPlot::MplPlot(QWidget *parent) : QWidget(parent) {
  // Create vertical layout
  setLayout(new QVBoxLayout);

  // Init sip stuff
  //init_mplcpp();
  PyObject *mpl_qt4backend = PyImport_ImportModule("matplotlib.backends.backend_qt5agg");
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

  auto cpp = static_cast<QWidget*>(sipUnwrap(figure_canvas));
  assert(cpp);
  layout()->addWidget(cpp);

  PyObject_CallMethod(figure_canvas, "draw", NULL);

  Py_DECREF(mpl_figure);
  Py_DECREF(mpl_qt4backend);
}
