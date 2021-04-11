cmake_minimum_required(VERSION 3.15)
project(sipfinder)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")

# Python
find_package(Python 3.6.0 REQUIRED COMPONENTS Interpreter Development)

# Qt
if(NOT Qt5_DIR)
  set(Qt5_DIR /usr/local/opt/qt@5/lib/cmake/Qt5)
endif()
set(CMAKE_AUTOMOC ON)
find_package(
  Qt5
  COMPONENTS Widgets
  REQUIRED
)

# Sip/PyQt
find_package(SIP REQUIRED)
find_package(PyQt5 REQUIRED)

# C++ library
add_library(widgets SHARED InfoWidget.cpp)
target_link_libraries(widgets Qt5::Widgets)

# Python library
include(SipQtTargetFunctions)
mtd_add_sip_module(
  MODULE_NAME _commonqt5
  SIP_SRCS _common.sip
  TARGET_NAME _commonqt5
  PYQT_VERSION 5
  INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}
  LINK_LIBS widgets
)
