# PathManipulations.cmake
# Collections of functions to manipulates lists of paths
#
# name: MAKE_ABSOLUTE
#   OUTPUT_LIST: Output variable containing absolute paths
#   BASE_DIR: Directory to prepend to given paths
#   ARGN: Files with relative paths
function (MAKE_ABSOLUTE OUTPUT_LIST BASE_DIR)
  set (${OUTPUT_LIST} )
  foreach(_file ${ARGN})
    list (APPEND ${OUTPUT_LIST} ${BASE_DIR}/${_file})
  endforeach()
  # Push the variable into the calling scope
  set (${OUTPUT_LIST} ${${OUTPUT_LIST}} PARENT_SCOPE)
endfunction()
