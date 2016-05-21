cmake_minimum_required ( VERSION 2.8.12 )

# Define the project name.
project ( helloworld23 )

# External packages
find_package ( PythonInterp REQUIRED )
set ( Python_ADDITIONAL_VERSIONS ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} )
find_package ( PythonLibs REQUIRED )
include_directories ( SYSTEM ${PYTHON_INCLUDE_PATH} )
set ( Boost_LIBRARIES )
find_package ( Boost COMPONENTS python-py${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR} REQUIRED )

set ( SRCS
  src/module.cpp
)

set ( BUILD_SHARED_LIBS ON )

# Flags for c++11
set ( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
add_definitions ( -DBOOST_PYTHON_NO_LIB )

# Warnings
foreach ( _src_file ${SRCS} )
  set_source_files_properties( ${_src_file}
                               PROPERTIES COMPILE_FLAGS "-Wall -Wextra" )
endforeach()

set ( _libname helloworld23 )
add_library ( ${_libname} ${BOOST_PYTHON_SRCS} ${SRCS} )
target_link_libraries ( ${_libname} ${Boost_LIBRARIES} )
set_target_properties( ${_libname} PROPERTIES PREFIX "" )
