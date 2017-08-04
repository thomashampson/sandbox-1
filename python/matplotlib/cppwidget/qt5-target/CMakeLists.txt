# Defines targets for Qt5 version of the build. The separate
# subdirectory allows the standard Qt macros for uic & moc
# to be used without modifiation to generate files in a subdirectory.
#
# It expects all of the variables defining the target to have been set in the
# parent CMakeLists.txt
include (PathManipulations)

set (BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..)
make_absolute (ABS_SRCS ${BASE_DIR} ${SRCS})
make_absolute (ABS_MOC_HEADERS ${BASE_DIR} ${MOC_HEADERS})
make_absolute (ABS_NOMOC_HEADERS ${BASE_DIR} ${NOMOC_HEADERS})
make_absolute (ABS_UI_FILES ${BASE_DIR} ${UI_FILES})

qt5_wrap_cpp (MOC_SRCS ${ABS_MOC_HEADERS})
qt5_wrap_ui (UI_HEADERS ${ABS_UI_FILES})
add_executable (mplcpp-qt5 ${ABS_SRCS} ${MOC_SRCS} ${UI_HEADERS} ${ABS_NOMOC_HEADERS})
target_include_directories (mplcpp-qt5 PUBLIC ${CMAKE_CURRENT_BINARY_DIR} )
target_link_libraries (mplcpp-qt5 Qt5::Widgets ${PYTHON_LIBRARIES})
