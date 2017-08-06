#include "MplFigureCanvas.h"

namespace Python {
/**
 * @brief Constructs a wrapper around a matplotlib Qt canvas to display plots
 * @param parent A pointer to the parent widget, can be nullptr
 */
MplFigureCanvas::MplFigureCanvas(QWidget *parent)
    : QWidget(parent), m_canvasType() {}
/**
 * @brief Destroys the object
 */
MplFigureCanvas::~MplFigureCanvas() {}
}
