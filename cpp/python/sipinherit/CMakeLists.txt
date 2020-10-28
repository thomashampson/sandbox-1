cmake_minimum_required(VERSION 3.15)
project(sipinherit)

# General settings
set( BUILD_SHARED_LIBS ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

# Compiler flags
if( ${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" )
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17" )
endif()

# Dependencies
find_package(Python3 REQUIRED COMPONENTS Interpreter Development)
find_package(Boost REQUIRED python38)
set(SIP_EXECUTABLE /usr/bin/sip)

# Targets
add_custom_command ( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/sipsipinheritpart0.cpp
  COMMAND ${SIP_EXECUTABLE}
  -c ${CMAKE_CURRENT_BINARY_DIR} -j1 -w
  -o -e ${CMAKE_CURRENT_LIST_DIR}/sipinherit.sip
  DEPENDS sipinherit.sip
  COMMENT "Generating sipinherit bindings using sip" )
add_library(sipinherit ${CMAKE_CURRENT_BINARY_DIR}/sipsipinheritpart0.cpp
  NamedItemRegistry.cpp NamedItemRegistry.h INamedItem.h extract.cpp extract.h)
target_include_directories(sipinherit PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(sipinherit Python3::Module Boost::python38)
set_target_properties(sipinherit PROPERTIES PREFIX "")
