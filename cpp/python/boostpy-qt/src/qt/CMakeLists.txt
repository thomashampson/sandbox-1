################################################################################
# Dependencies
################################################################################
find_package ( Qt4 COMPONENTS QtCore QtGui REQUIRED )
include( UseQt4 )

################################################################################
# Subprojects
################################################################################

add_subdirectory( widgets )
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )

# bindings
add_subdirectory( python )

# app
add_subdirectory( app )
