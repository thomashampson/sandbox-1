#ifndef MPLPLOTWIDGETTEST_H
#define MPLPLOTWIDGETTEST_H

#include "cxxtest/TestSuite.h"

#include "MplFigureCanvas.h"

class MplFigureCanvasTestImpl : public QObject {
  Q_OBJECT
private slots:
};

class MplFigureCanvasTest : public CxxTest::TestSuite {
public:
  static MplFigureCanvasTest *createSuite() { return new MplFigureCanvasTest; }
  static void destroySuite(MplFigureCanvasTest *suite) { delete suite; }

  void test_Default_Construction_Yields_Single_Subplot() {
    Python::MplFigureCanvas canvas;
    TSM_ASSERT_EQUALS("Default canvas should have a single subplot",
                      Python::SubPlotSpec(1, 1), canvas.subplotSpec());
  }

  void test_Construction_With_SubPlot_Layout_Respects_It() {
    Python::MplFigureCanvas canvas(231);
    TSM_ASSERT_EQUALS("Canvas should respect subplot layout request",
                      Python::SubPlotSpec(2, 3), canvas.subplotSpec());
  }
};

#endif // MPLPLOTWIDGETTEST_H
