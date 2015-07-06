cmake_minimum_required (VERSION 2.8)
project (embed_python)

###############################################################################
# Project-specific CMake
###############################################################################
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

###############################################################################
# Compiler Setup
###############################################################################
include (CompilerSetup)

################################################################################
# Dependencies
################################################################################
# Qt4
set (CMAKE_AUTOMOC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
find_package (Qt4 4.8 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})
# Python
find_package (PythonLibs REQUIRED)
include_directories (${PYTHON_INCLUDE_DIR})

################################################################################
# Source
################################################################################
set (SRC_FILES
    code.cpp
    codeeditor.cpp
    main.cpp
    mainwindow.cpp
    pythoninterpreter.cpp
)

set (INC_FILES
    code.h
    codeeditor.h
    mainwindow.h
    pythoninterpreter.h
)

set (MOC_FILES
    ${INC_FILES}
)

set (SRC_FILES
    ${SRC_FILES}
)

set (UI_FILES
    codeeditor.ui
)
qt4_wrap_ui (UI_HEADERS ${UI_FILES})
include_directories (${CMAKE_CURRENT_BINARY_DIR})

################################################################################
# Target
################################################################################
if( WIN32 )
    option (CONSOLE "Enable/disable the console" ON)
  if (CONSOLE)
       set (WIN_CONSOLE)
   else ()
       set(WIN_CONSOLE WIN32)
   endif()
endif()

add_executable ( embed_python ${WIN_CONSOLE}
  ${SRC_FILES} ${INC_FILES} ${UI_HEADERS}
)
target_link_libraries (embed_python LINK_PRIVATE
    Qt4::QtCore Qt4::QtGui
    ${PYTHON_LIBRARIES}
)
