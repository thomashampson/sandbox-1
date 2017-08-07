#include "MplFigureCanvas.h"

namespace {
#if QT_VERSION >= QT_VERSION_CHECK(4, 0, 0) &&                                 \
    QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
const char *MPL_QT_BACKEND = "matplotlib.backends.backend_qt4agg";
#elif QT_VERSION >= QT_VERSION_CHECK(5, 0, 0) &&                               \
    QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
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
    : QWidget(parent), m_canvasType() {
  PythonObject mpl_qt_backend(NewRef(PyImport_ImportModule(MPL_QT_BACKEND)));

}
/**
 * @brief Destroys the object
 */
MplFigureCanvas::~MplFigureCanvas() {}
}
