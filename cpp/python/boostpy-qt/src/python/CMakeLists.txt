################################################################################
# Python bindings for framework
################################################################################
set( Boost_LIBRARIES ) # Empty out the variable after previous use
find_package( Boost REQUIRED python )
include_directories( SYSTEM ${PYTHON_INCLUDE_DIR} )

set( SRCS
  module.cpp
)

add_library ( pycore ${SRCS} )
# No library prefixes
set_target_properties( pycore PROPERTIES PREFIX "" )
# Dependencies
target_link_libraries( pycore LINK_PRIVATE core ${Boost_LIBRARIES} )
