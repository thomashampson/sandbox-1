cmake_minimum_required ( VERSION 2.8.12 )

# Define the project name.
project ( extract_ref )

# External packages
find_package ( PythonLibs REQUIRED )
include_directories ( SYSTEM ${PYTHON_INCLUDE_PATH} )

# Third party sources
file ( GLOB_RECURSE BOOST_PYTHON_SRCS
       third_party/boost/python/src/*.cpp )
set ( SRCS
  src/DataObjects.cpp
  src/DataService.cpp
  src/WorkspaceFactory.cpp
  src/module.cpp
)

set ( BUILD_SHARED_LIBS ON )

# Flags for c++11
set ( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
add_definitions ( -DBOOST_DEBUG_PYTHON -DBOOST_PYTHON_NO_LIB -DNPY_NO_DEPRECATED_API=NPY_1_7_API_VERSION )

# Warnings
foreach ( _src_file ${SRCS} )
  set_source_files_properties( ${_src_file}
                               PROPERTIES COMPILE_FLAGS "-Wall -Wextra" )
endforeach()

add_library ( extract_ref ${BOOST_PYTHON_SRCS} ${SRCS} )
set_target_properties( extract_ref PROPERTIES PREFIX "" )
