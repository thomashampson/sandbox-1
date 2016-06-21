#ifndef MPLPLOT_H_
#define MPLPLOT_H_
#include "Python.h"
#include <QWidget>

// -----------------------------------------------------------------------------
class MplPlot : public QWidget {

Q_OBJECT

public:
  MplPlot(QWidget *parent = 0);

private:
  PyObject * self();
};

#endif //MPLPLOT_H_
