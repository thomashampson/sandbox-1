#ifndef MPLFIGURECANVAS_H
#define MPLFIGURECANVAS_H

#include "PythonObject.h"
#include <QWidget>

namespace Python {

/**
 * @brief C++ wrapper around a matplotlib Qt canvas.
 *
 * It uses the Agg version of the Qt matplotlib backend that matches the
 * Qt version that the library is compiled against.
 *
 * This replicates the example of embedding in Python from
 * https://matplotlib.org/examples/user_interfaces/embedding_in_qt5.html
 */
class MplFigureCanvas : public QWidget {
  Q_OBJECT
public:
  explicit MplFigureCanvas(QWidget *parent = 0);
  ~MplFigureCanvas();

private:
  Python::PythonObject m_pyCanvas;
  Python::PythonObject m_axes;
};
}
#endif // MPLFIGURECANVAS_H
