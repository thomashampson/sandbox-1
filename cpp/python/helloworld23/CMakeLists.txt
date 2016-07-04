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
include_directories ( SYSTEM ${Boost_INCLUDE_DIR} )
add_definitions ( -DBOOST_ALL_DYN_LINK -DBOOST_ALL_NO_LIB )
add_definitions ( -DBOOST_PYTHON_NO_LIB )

set ( SRCS
  src/module.cpp
)

set ( BUILD_SHARED_LIBS ON )

# Warnings
if (NOT MSVC)
  # Flags for c++11
  set ( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
  foreach ( _src_file ${SRCS} )
    set_source_files_properties( ${_src_file}
                                 PROPERTIES COMPILE_FLAGS "-Wall -Wextra" )
  endforeach()
endif()

set ( _libname helloworld23 )
add_library ( ${_libname} ${BOOST_PYTHON_SRCS} ${SRCS} )
target_link_libraries ( ${_libname} stdc++ ${Boost_LIBRARIES} ${PYTHON_LIBRARIES} )
if (MSVC)
  set_target_properties( ${_libname} PROPERTIES SUFFIX ".pyd" )
else ()
  set_target_properties( ${_libname} PROPERTIES PREFIX "" )
endif ()
