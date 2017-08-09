#include "MplFigureCanvas.h"
#include "MplAxes.h"
#include "PythonErrors.h"
#include "SipUtils.h"

#include <QVBoxLayout>

namespace {
//------------------------------------------------------------------------------
// Static constants/functions
//------------------------------------------------------------------------------
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
//------------------------------------------------------------------------------
// MplFigureCanvas::Impl - Private implementation
//------------------------------------------------------------------------------
class MplFigureCanvas::Impl {
  friend class MplFigureCanvas;
  Impl(int subplotLayout) {
    // Create a figure and attach it to a canvas object. This creates a
    // blank widget
    PythonObject figure(
        NewRef(PyObject_CallObject(mplFigureType().get(), NULL)));
    m_axes = MplAxes(NewRef(
        PyObject_CallMethod(figure.get(), "add_subplot", "i", subplotLayout)));
    auto instance =
        PyObject_CallFunction(mplFigureCanvasType().get(), "(O)", figure.get());
    if (!instance) {
      throw PythonError(errorToString());
    }
    m_canvas = PythonObject(NewRef(instance));
  }

private:
  PythonObject m_canvas;
  MplAxes m_axes;
};

//------------------------------------------------------------------------------
// MplFigureCanvas
//------------------------------------------------------------------------------
/**
 * @brief Constructs a matplotlib Qt canvas containing a single subplot
 * @param subplotLayout The subplot layout defined in matplotlib's convenience
 * format. See
 * https://matplotlib.org/api/pyplot_api.html#matplotlib.pyplot.subplot
 * @param parent A pointer to the parent widget, can be nullptr
 */
MplFigureCanvas::MplFigureCanvas(int subplotLayout, QWidget *parent)
    : QWidget(parent), m_impl(new Impl(subplotLayout)) {
  setLayout(new QVBoxLayout);
  auto cpp = static_cast<QWidget *>(sipUnwrap(m_impl->m_canvas.get()));
  assert(cpp);
  layout()->addWidget(cpp);
}

/**
 * @brief Destroys the object
 */
MplFigureCanvas::~MplFigureCanvas() { delete m_impl; }

/**
 *
 * @return A reference to the Axes object
 */
MplAxes MplFigureCanvas::axes() const
{
  return m_impl->m_axes;
}

/**
 * Call FigureCanvas.draw method on base class
 */
void MplFigureCanvas::draw()
{
  PyObject_CallMethod(m_impl->m_canvas.get(), "draw", "", nullptr);
}
}
