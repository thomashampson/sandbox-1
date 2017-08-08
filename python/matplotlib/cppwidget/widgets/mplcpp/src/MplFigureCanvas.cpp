#include "MplFigureCanvas.h"
#include "PythonErrors.h"
#include "SipUtils.h"

#include <QVBoxLayout>

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

// Return static instance of figure type
const Python::PythonObject &mplFigureType() {
  static Python::PythonObject figureType;
  if (figureType.isNone())
    figureType = Python::getAttrOnModule("matplotlib.figure", "Figure");
  return figureType;
}

// Return static instance of figure canvas type
const Python::PythonObject &mplFigureCanvasType() {
  static Python::PythonObject figureCanvasType;
  if (figureCanvasType.isNone()) {
    // Importing PyQt version first helps matplotlib select the correct backend.
    // We should do this in some kind of initialisation routine
    Python::importModule(PYQT_MODULE);
    figureCanvasType =
        Python::getAttrOnModule(MPL_QT_BACKEND, "FigureCanvasQTAgg");
  }
  return figureCanvasType;
}
}

namespace Python {
/**
 * @brief Constructs a matplotlib Qt canvas containing a single subplot
 * @param parent A pointer to the parent widget, can be nullptr
 */
MplFigureCanvas::MplFigureCanvas(QWidget *parent)
    : QWidget(parent), m_pyCanvas(), m_axes() {
  setLayout(new QVBoxLayout);

  // Create a figure and attach it to a canvas object. This creates a
  // blank widget
  PythonObject figure(NewRef(PyObject_CallObject(mplFigureType().get(), NULL)));
  m_axes = PythonObject(
      NewRef(PyObject_CallMethod(figure.get(), "add_subplot", "i", 111)));
  auto instance =
      PyObject_CallFunction(mplFigureCanvasType().get(), "(O)", figure.get());
  if (!instance) {
    throw PythonError(errorToString());
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
