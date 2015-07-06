###############################################################################
# Configure the specifics about the compiler
###############################################################################
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  include (${CMAKE_CURRENT_LIST_DIR}/compiler/gnu.cmake)
else ()
  message (WARNING "Unsupported compiler, continuing with default configuration.")
endif()
