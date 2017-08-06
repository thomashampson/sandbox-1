# Unit tests
#
include (PathManipulations)
set (TEST_HEADERS
    PythonObjectTest.h
)
make_absolute (ABS_TEST_HEADERS ${CMAKE_CURRENT_SOURCE_DIR} ${TEST_HEADERS})
cxxtest_add_test (mplcpp-test-qt4 mplcpp-test.cpp ${ABS_TEST_HEADERS})
target_include_directories (mplcpp-test-qt4 PRIVATE ${CXXTEST_INCLUDE_DIR})
target_link_libraries (mplcpp-test-qt4 mplcpp-qt4)
