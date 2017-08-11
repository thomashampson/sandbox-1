# Unit tests
#
set (STD_TESTS
  PythonObjectTest.h
  NDArray1DTest.h
)

set (QT_TESTS
  MplFigureCanvasTest.h
)
# TESTHELPER_SRCS is used internally by cxxtest_add_test when set
qt4_wrap_cpp (TESTHELPER_SRCS ${QT_TESTS})

# CXXTEST_EXTRA_HEADER passes this file to the --include argument
set (CXXTEST_EXTRA_HEADER GlobalInitialization.h)

cxxtest_add_test (mplcpp-test-qt4 ${STD_TESTS} ${QT_TESTS})
target_include_directories (mplcpp-test-qt4 PRIVATE ${CXXTEST_INCLUDE_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/../include)
target_link_libraries (mplcpp-test-qt4 Qt4::QtGui mplcpp-Qt4 ${PYTHON_LIBRARIES})
