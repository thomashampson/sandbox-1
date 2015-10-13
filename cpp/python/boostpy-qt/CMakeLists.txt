cmake_minimum_required( VERSION 2.8.12 )
project( boostpy-qt  )

################################################################################
# General settings
################################################################################
set( BUILD_SHARED_LIBS ON )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib )

################################################################################
# Dependencies
################################################################################
find_package ( Qt4 COMPONENTS QtCore QtGui REQUIRED )
include( UseQt4 )

################################################################################
# Subprojects
################################################################################
add_subdirectory( src )
