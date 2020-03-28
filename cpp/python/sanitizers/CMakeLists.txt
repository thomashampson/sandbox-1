cmake_minimum_required ( VERSION 3.15 )

# Define the project name.
project ( sanitizers )

# Sanitizers
if(CMAKE_COMPILER_IS_GNUCXX AND (NOT CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 8))
  message(FATAL_ERROR "GCC 7 and below do not support sanitizers")
endif()

add_compile_options(
  -fsanitize=address
  -fno-omit-frame-pointer
  -fno-optimize-sibling-calls
)
add_link_options(
  -fsanitize=address
)

# External packages
find_package ( Python3 COMPONENTS Development REQUIRED )
set(PYTHONXY python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR})
find_package ( Boost COMPONENTS python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR} REQUIRED )

# Compile flags
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_REQUIRED TRUE)
add_compile_options(-Wall -Wextra)

add_library(core SHARED core.cpp core.hpp)

set(_targetname pycore)
add_library(${_targetname} SHARED pycore.cpp)
target_link_libraries(${_targetname} PRIVATE
  core
  Boost::${PYTHONXY}
  Boost::disable_autolinking
  Boost::dynamic_linking
  Python3::Python
)
set_target_properties(${_targetname} PROPERTIES
  PREFIX ""
  LIBRARY_OUTPUT_NAME core
)
