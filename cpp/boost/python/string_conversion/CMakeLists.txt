cmake_minimum_required(VERSION 3.5)

project(StringConversion)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_PYTHON3 ON "Use python 3 build")

# find python/boost python
find_package(PythonInterp REQUIRED)
set ( Python_ADDITIONAL_VERSIONS ${PYTHON_VERSION_MAJOR}.${PYTHON_VERSION_MINOR} )
find_package(PythonLibs REQUIRED)

if ( PYTHON_VERSION_MAJOR GREATER 2 )
  # Try a known set of suffixes plus a user-defined set
  # Define a cache variable to supply additional suffxies. These are tried first
  set ( BOOST_PYTHON_ADDITIONAL_SUFFIXES "" CACHE STRING "Additional suffixes to try when searching for the boost python3 library. These are prepended to the default list" )
  set ( _suffixes "${BOOST_PYTHON_ADDITIONAL_SUFFIXES};${PYTHON_VERSION_MAJOR};-py${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR};${PYTHON_VERSION_MAJOR}${PYTHON_VERSION_MINOR}")
  foreach ( _suffix ${_suffixes})
    find_package ( Boost COMPONENTS python${_suffix} )
    if ( Boost_FOUND )
      break ()
    endif ()
  endforeach ()
  if ( NOT Boost_FOUND )
    message ( FATAL_ERROR "Cannot find appropriate boost python version after trying with the "
      "following library suffixes: ${_suffixes}" )
  endif ()
else ()
  # Assumes that the default version is 27
  find_package ( Boost COMPONENTS python )
  if ( NOT Boost_FOUND )
    find_package ( Boost COMPONENTS python27 )
  endif ()
  if ( NOT Boost_FOUND )
    message ( FATAL_ERROR "Cannot find appropriate boost python version after trying with the "
      "following library suffixes: ;27" )
  endif ()
endif ()

add_library(stringy SHARED
  "stringy.cpp"
#  "container.cpp"
#  "containeritem.cpp"
#  "containeriterator.cpp"
)

target_include_directories(stringy PUBLIC ${PYTHON_INCLUDE_DIR})
target_link_libraries(stringy ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(stringy PROPERTIES PREFIX "")
