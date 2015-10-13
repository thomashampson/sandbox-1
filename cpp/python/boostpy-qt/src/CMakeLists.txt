################################################################################
# Subprojects
################################################################################
add_subdirectory( widgets )

include_directories ( ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory( app )
