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
 */
class MplFigureCanvas : public QWidget {
  Q_OBJECT
public:
  explicit MplFigureCanvas(QWidget *parent = 0);
  ~MplFigureCanvas();

private:
  Python::PythonObject m_canvasType;
};
}
#endif // MPLFIGURECANVAS_H
