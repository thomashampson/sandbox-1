# ------------------------------------------------------------------------------
# Prototype binary reader
#
# Author: Martyn Gigg
# ------------------------------------------------------------------------------
cmake_minimum_required (VERSION 2.8.12)

# ------------------------------------------------------------------------------
# Global properties
# ------------------------------------------------------------------------------
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ------------------------------------------------------------------------------
# Dependencies
# ------------------------------------------------------------------------------

# ------------------------------------------------------------------------------
# Compiler flags
# ------------------------------------------------------------------------------
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
if (${CMAKE_VERSION} VERSION_GREATER 3.1.0 OR ${CMAKE_VERSION} VERSION_EQUAL 3.1.0)
  set (CMAKE_CXX_STANDARD 14)
  set (CXX_STANDARD_REQUIRED 11)
else()
  include (CheckCXXCompilerFlag)
  CHECK_CXX_COMPILER_FLAG ("-std=c++14" COMPILER_SUPPORTS_CXX14)
  CHECK_CXX_COMPILER_FLAG ("-std=c++11" COMPILER_SUPPORTS_CXX11)
  CHECK_CXX_COMPILER_FLAG ("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
  if (COMPILER_SUPPORTS_CXX14)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  elseif (COMPILER_SUPPORTS_CXX11)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  elseif (COMPILER_SUPPORTS_CXX0X)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  endif()
endif()

# ------------------------------------------------------------------------------
# Sources
# ------------------------------------------------------------------------------
set (HDRS
  src/BinaryFileReader.h
)
set (SRCS
  src/BinaryFileReader.cpp
  src/main.cpp
)

# ------------------------------------------------------------------------------
# Targets
# ------------------------------------------------------------------------------
add_executable (readbin ${SRCS} ${HDRS})
