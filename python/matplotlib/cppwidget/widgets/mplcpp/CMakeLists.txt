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

set (INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_SOURCE_DIR}/widgets/mplcpp/include
)
# Target
mtd_add_qt4_and_qt5_library (TARGET_NAME mplcpp SRC ${LIB_SRCS} MOC ${MOC_HEADERS}
                             NOMOC ${NOMOC_HEADERS} INCLUDE_DIRS ${INCLUDES})
