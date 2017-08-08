#include "MplFigureCanvas.h"
#include "SipUtils.h"

#include <QVBoxLayout>

#include <iostream>

namespace {
#if QT_VERSION >= QT_VERSION_CHECK(4, 0, 0) &&                                 \
    QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
// Define PyQt version and matplotlib backend
const char *PYQT_MODULE = "PyQt4";
const char *MPL_QT_BACKEND = "matplotlib.backends.backend_qt4agg";

#elif QT_VERSION >= QT_VERSION_CHECK(5, 0, 0) &&                               \
    QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
// Define PyQt version and matplotlib backend
const char *PYQT_MODULE = "PyQt5";
const char *MPL_QT_BACKEND = "matplotlib.backends.backend_qt5agg";

#else
#error "Unknown Qt version. Cannot determine matplotlib backend."
#endif
}

namespace Python {
/**
 * @brief Constructs a wrapper around a matplotlib Qt canvas to display plots
 * @param parent A pointer to the parent widget, can be nullptr
 */
MplFigureCanvas::MplFigureCanvas(QWidget *parent)
    : QWidget(parent), m_pyCanvas() {
  setLayout(new QVBoxLayout);

  // Importing PyQt version first helps matplotlib select the correct backend.
  // We should do this in some kind of initialisation routine
  PythonObject pyQtModule(NewRef(PyImport_ImportModule(PYQT_MODULE)));

  // Create a figure and attach it to a canvas object. This creates a
  // blank widget
  PythonObject mplFigureModule(
      NewRef(PyImport_ImportModule("matplotlib.figure")));
  PythonObject figureType(mplFigureModule.getAttr("Figure"));
  PythonObject figure(NewRef(PyObject_CallObject(figureType.get(), NULL)));

  PythonObject mplQtBackend(NewRef(PyImport_ImportModule(MPL_QT_BACKEND)));
  auto canvasType = mplQtBackend.getAttr("FigureCanvasQTAgg");
  auto instance = PyObject_CallFunction(canvasType.get(), "(O)", figure.get());
  if (!instance) {
    PyErr_Print();
    throw std::runtime_error("An error occurred");
  }
  m_pyCanvas = PythonObject(NewRef(instance));
  auto cpp = static_cast<QWidget *>(sipUnwrap(m_pyCanvas.get()));
  assert(cpp);
  layout()->addWidget(cpp);
}

/**
 * @brief Destroys the object
 */
MplFigureCanvas::~MplFigureCanvas() {}
}
