cmake_minimum_required (VERSION 3.0.0)

foreach (p
    CMP0020 # CMake 2.8.11
    CMP0022 # CMake 2.8.12
    CMP0025 # CMake 3.0
    CMP0053 # CMake 3.1
    CMP0054 # CMake 3.1
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach ()

project (mplcpp)
set (CMAKE_MODULE_PATH ${mplcpp_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Compiler
include (CheckCXXCompilerFlag)
check_cxx_compiler_flag ("-std=c++14" COMPILER_SUPPORTS_CXX14 )
check_cxx_compiler_flag ("-std=c++11" COMPILER_SUPPORTS_CXX11 )
check_cxx_compiler_flag ("-std=c++0x" COMPILER_SUPPORTS_CXX0X )
if (COMPILER_SUPPORTS_CXX14)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
elseif (COMPILER_SUPPORTS_CXX11)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif (COMPILER_SUPPORTS_CXX0X)
  set (CMAKE_CXX_FLAGS "$${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

# Python
find_package (PythonInterp REQUIRED)
find_package (PythonLibs REQUIRED)
find_package (SIP REQUIRED)

# Qt
# Automoc & Autouic won't work while we are building against Qt4 & Qt5

# Qt 4
find_package (Qt4 REQUIRED QtCore QtGui)
find_package (PyQt4 REQUIRED)

# Qt 5
find_package (Qt5Widgets REQUIRED)
find_package (PyQt5 REQUIRED)

include_directories ( SYSTEM ${SIP_INCLUDE_DIR} )
include_directories ( ${CMAKE_CURRENT_LIST_DIR}/include )

# app
set (SRCS
  src/main.cpp
  src/MainWindow.cpp
  src/MplFigureCanvas.cpp
  src/PythonObject.cpp
)

set (UI_FILES
  include/mainwindow.ui
)

set (MOC_HEADERS
  include/MainWindow.h
  include/MplFigureCanvas.h
)

set (NOMOC_HEADERS
  include/PythonObject.h
)

add_subdirectory (qt4-target)
add_subdirectory (qt5-target)
