#ifndef MPLFIGURECANVAS_H
#define MPLFIGURECANVAS_H

#include <QWidget>

#include "MplAxes.h"

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
  explicit MplFigureCanvas(int subplotLayout = 111, QWidget *parent = 0);
  ~MplFigureCanvas();

  MplAxes axes() const;
  void draw();

private:
  // Private implementation to keep Python out of headers
  class Impl;
  Impl *m_impl;
};
}
#endif // MPLFIGURECANVAS_H
