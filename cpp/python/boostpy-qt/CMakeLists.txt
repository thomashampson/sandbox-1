cmake_minimum_required( VERSION 2.8.12 )
project( boostpy-qt  )

################################################################################
# General settings
################################################################################
set( BUILD_SHARED_LIBS ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )
# Add the path to our custom 'find' modules
set ( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMake")

################################################################################
# Subprojects
################################################################################
add_subdirectory( src )
