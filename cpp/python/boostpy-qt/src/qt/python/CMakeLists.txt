################################################################################
# Dependencies
################################################################################
find_package( PythonInterp REQUIRED )
find_package( PythonLibs REQUIRED )
include_directories ( SYSTEM ${PYTHON_INCLUDE_PATH} )
find_package( SIP REQUIRED )
include_directories ( SYSTEM ${SIP_INCLUDE_DIR} )
find_package( PyQt4 REQUIRED )

################################################################################
# SIP sources
################################################################################
set ( SIP_SPEC ${CMAKE_CURRENT_SOURCE_DIR}/pywidgets.sip )
set ( SIP_CPP_DIR ${CMAKE_CURRENT_BINARY_DIR} )
set ( SIP_CPP_SRC ${SIP_CPP_DIR}/sippywidgetspart0.cpp)

###########################################################################
# Sip generated files
###########################################################################

# Flags used:
# -e : C++ exceptions turn into python exceptions.
# -j1 : split into 1 file
# -w : enable warnings
# -o : automatic docstrings (not supported in old version < 4.10)

add_custom_command ( OUTPUT ${SIP_CPP_SRC}
  COMMAND ${SIP_EXECUTABLE}
  -I ${PYQT4_SIP_DIR} ${PYQT4_SIP_FLAGS}
  -c ${SIP_CPP_DIR} -j1 -w
  -o -e ${SIP_SPEC}
  DEPENDS ${SIP_SPEC} ${SIP_HDRS}
  COMMENT "Generating pywidgets bindings using sip" )

###########################################################################
# Target
###########################################################################

add_library( pywidgets ${SIP_CPP_SRC} )
# No lib prefix
set_target_properties( pywidgets PROPERTIES PREFIX "" )
target_link_libraries( pywidgets LINK_PRIVATE widgets )
