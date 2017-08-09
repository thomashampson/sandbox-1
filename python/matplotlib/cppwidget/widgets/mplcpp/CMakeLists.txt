# Rules for matplotlib cpp library
set (LIB_SRCS
  src/MplAxes.cpp
  src/MplFigureCanvas.cpp
  src/NDArray1D.cpp
  src/Numpy.cpp
  src/PythonErrors.cpp
  src/PythonObject.cpp
  src/SipUtils.cpp
)

set (MOC_HEADERS
  include/MplFigureCanvas.h
)

set (NOMOC_HEADERS
  include/MplAxes.h
  include/NDArray1D.h
  include/Numpy.h
  include/PythonErrors.h
  include/PythonObject.h
  include/SipUtils.h
  include/WrapPython.h
)

set (INCLUDES
  ${CMAKE_CURRENT_LIST_DIR}/include
  ${CMAKE_SOURCE_DIR}/widgets/mplcpp/include
)
# Target
mtd_add_qt4_and_qt5_library (TARGET_NAME mplcpp SRC ${LIB_SRCS} MOC ${MOC_HEADERS}
                             NOMOC ${NOMOC_HEADERS} INCLUDE_DIRS ${INCLUDES}
                             LINK_LIBRARIES ${PYTHON_LIBRARIES})

# Tests
add_subdirectory (test)
