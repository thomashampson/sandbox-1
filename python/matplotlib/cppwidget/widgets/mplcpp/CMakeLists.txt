# Rules for matplotlib cpp library



set (LIB_SRCS
  src/MplFigureCanvas.cpp
  src/PythonObject.cpp
)

set (MOC_HEADERS
  include/MplFigureCanvas.h
)

set (NOMOC_HEADERS
  include/PythonObject.h
)


mtd_add_qt_library (TARGET_NAME mplcpp QT_VERSION 4 SRC ${LIB_SRCS} MOC ${MOC_HEADERS}
                    NOMOC ${NOMOC_HEADERS} INCLUDES ${CMAKE_CURRENT_LIST_DIR}/include)
