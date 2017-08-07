# Utility functions to add libraries/executables parametrized by
# the required version of Qt
#
# name: mtd_add_qt_library
# brief: create a library target for a given Qt version
# For all options see mtd_add_qt_target
function (mtd_add_qt_library)
  mtd_add_qt_target (LIBRARY ${ARGN})
endfunction()


# name: mtd_add_qt_executable
# brief: create an executable target for a given Qt version
# For all options see mtd_add_qt_target
function (mtd_add_qt_executable)
  mtd_add_qt_executable (EXECUTABLE ${ARGN})
endfunction()

# Target agnostic function to add either an executable or library linked to Qt
# keyword: TARGET_NAME The name of the target.
# keyword: QT_VERSION The major version of Qt to build against
# keyword: SRC .cpp files to include in the target build
# keyword: MOC Header files that are to be parsed by moc
# keyword: NOMOC Additional headers that are not to be passed to moc
# keyword: INCLUDES A list of include directories to add to the target
function (mtd_add_qt_target)
  set (options LIBRARY EXECUTABLE NO_SUFFIX)
  set (oneValueArgs TARGET_NAME QT_VERSION)
  set (multiValueArgs SRC UI MOC NOMOC INCLUDES)
  cmake_parse_arguments (PARSED "${options}" "${oneValueArgs}"
                         "${multiValueArgs}" ${ARGN})

  set (_base_src_dir ${CMAKE_CURRENT_LIST_DIR})
  set (_binary_dir_on_entry ${CMAKE_CURRENT_BINARY_DIR})
  set (_base_binary_dir ${CMAKE_CURRENT_BINARY_DIR}/qt${PARSED_QT_VERSION})
  set (CMAKE_CURRENT_BINARY_DIR ${_base_binary_dir})
  if (PARSED_QT_VERSION EQUAL 4)
    qt4_wrap_ui (UI_HEADERS ${PARSED_UI})
    qt4_wrap_cpp (MOC_GENERATED ${PARSED_MOC})
    set (_link_libraries Qt4::QtGui)
  else ()
    message (FATAL_ERROR "Unknown Qt version. Please specify only the major version.")
  endif()
  set (CMAKE_CURRENT_BINARY_DIR ${_binary_dir_on_entry})
  if (${PARSED_NO_SUFFIX})
    set (_target ${PARSED_TARGET_NAME})
  else()
    set (_target ${PARSED_TARGET_NAME}-Qt${PARSED_QT_VERSION})
  endif()
  if (${PARSED_LIBRARY})
    add_library (${_target} ${PARSED_SRC} ${MOC_GENERATED} ${UI_HEADERS})
  elseif (${PARSED_EXECUTABLE})
    add_executable (${_target} ${PARSED_SRC} ${MOC_GENERATED} ${UI_HEADERS})
  else ()
    message (FATAL_ERROR "Unknown target type. Options=LIBRARY,EXECUTABLE")
  endif()
  target_include_directories (${_target} PUBLIC ${_base_binary_dir} PUBLIC ${PARSED_INCLUDES})
  target_link_libraries (${_target} PRIVATE ${_link_libraries})
endfunction()

