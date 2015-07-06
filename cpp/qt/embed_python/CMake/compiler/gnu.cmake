###############################################################################
# Configure flags for gcc
###############################################################################

# Global warning flags.
set (COMMON_FLAGS "-Wall -Wextra -Wconversion -Winit-self -Wpointer-arith -Wcast-qual -Wcast-align -fno-common" )
set (FLAGS_CXX "-Woverloaded-virtual -fno-operator-names -std=c++0x" )

# Disable some warnings about deprecated headers and type conversions that
# we can't do anything about
# -Wno-deprecated: Do not warn about use of deprecated headers.
# -Wno-write-strings: Do not warn about deprecated conversions of char*->const char*
# -Wno-unused-result: Do not warn about unused return values in some C functions
set (IGNORED_WARNINGS  "-Wno-deprecated -Wno-write-strings")

# Check if we have a new enough version for this flag
# some -pedantic warnings remain with gcc 4.4.7
if (NOT (GCC_COMPILER_VERSION VERSION_LESS "4.5"))
  set (COMMON_FLAGS "${COMMON_FLAGS} -pedantic")
  set (IGNORED_WARNINGS "${IGNORED_WARNINGS} -pedantic")
endif ()

# Apply
set( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${COMMON_FLAGS} ${IGNORED_WARNINGS}" )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMMON_FLAGS} ${FLAGS_CXX} ${IGNORED_WARNINGS}" )
