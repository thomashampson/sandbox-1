# ------------------------------------------------------------------------------
# Prototype binary reader
#
# Author: Martyn Gigg
# -----------------------------------------------------------------------``-------
cmake_minimum_required (VERSION 3.15)
project(readbin)

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
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_property(_is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(_is_multi_config)
  # Define a new configuration for debugging with Conda.
  # Crucially it must link to the MSVC release runtime but we switch off all optimzations
  set(_conda_debug_cfg_name DebugWithRelRuntime)
  string(TOUPPER ${_conda_debug_cfg_name} _conda_debug_cfg_name_upper)
  # C/CXX flags
  foreach(lang C CXX)
    set(CMAKE_${lang}_FLAGS_${_conda_debug_cfg_name_upper} "/Zi /Ob0 /Od /RTC1" CACHE STRING "" FORCE)
  endforeach()
  # Linker
  foreach(t EXE SHARED MODULE)
    set(CMAKE_${t}_LINKER_FLAGS_${_conda_debug_cfg_name_upper} ${CMAKE_${t}_LINKER_FLAGS_RELWITHDEBINFO} CACHE STRING "" FORCE)
  endforeach()

  # Set configurations. We also dump MinSizeRel & Debug as the former is not used and the latter will not work
  set(CMAKE_CONFIGURATION_TYPES "${_conda_debug_cfg_name};Release;RelWithDebInfo" CACHE STRING "" FORCE)
  message(STATUS "Detected a build with Conda on Windows. Resetting available build configurations to ${CMAKE_CONFIGURATION_TYPES}")
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
