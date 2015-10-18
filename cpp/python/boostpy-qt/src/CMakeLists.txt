################################################################################
# Subprojects
################################################################################
add_subdirectory( core )
include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )

# bindings
add_subdirectory( python )

# GUI
add_subdirectory( qt )
