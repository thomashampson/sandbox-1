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


# Qt
set (CMAKE_AUTOMOC ON)
set (CMAKE_AUTOUIC ON)
set (CMAKE_INCLUDE_CURRENT_DIR ON)
find_package (Qt4 REQUIRED QtCore QtGui)

# Python
find_package (PythonInterp REQUIRED)
find_package (PythonLibs REQUIRED)

# Sip, PyQt4
find_package ( PyQt4 REQUIRED )
find_package ( SIP REQUIRED )
separate_arguments ( PYQT4_SIP_FLAGS )

set (SIP_SRC _mplcpp.sip)
set (SIP_OUTFILE ${CMAKE_CURRENT_BINARY_DIR}/sip_mplcpppart0.cpp)
add_custom_command (OUTPUT ${SIP_OUTFILE}
  COMMAND ${SIP_EXECUTABLE} -I ${PYQT4_SIP_DIR} ${PYQT4_SIP_FLAGS}
    -c ${CMAKE_CURRENT_BINARY_DIR} -j1 -w -o
    ${CMAKE_CURRENT_LIST_DIR}/${SIP_SRC}
  DEPENDS ${SIP_SRC}
  COMMENT "Generating Python bindings"
)

include_directories ( SYSTEM ${SIP_INCLUDE_DIR} )

# app
set (SRCS
  main.cpp
  MainWindow.cpp
  MplPlot.cpp
)

set (HEADERS
  MainWindow.h
  MplPlot.h
)

add_executable (mplcpp ${SRCS} ${SIP_OUTFILE})
target_link_libraries (mplcpp Qt4::QtGui ${PYTHON_LIBRARIES})
