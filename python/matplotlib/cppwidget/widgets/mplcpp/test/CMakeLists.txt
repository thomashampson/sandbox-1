# Unit tests
#
set (TEST_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/PythonObjectTest.h
)

cxxtest_add_test (mplcpp-test-qt4 mplcpp-test.cpp ${TEST_HEADERS})
target_include_directories (mplcpp-test-qt4 PRIVATE ${CXXTEST_INCLUDE_DIR} ${CMAKE_CURRENT_LIST_DIR}/../include)
target_link_libraries (mplcpp-test-qt4 mplcpp-Qt4 ${PYTHON_LIBRARIES})
