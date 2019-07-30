project (allocators)
cmake_minimum_required (VERSION 3.5)

######################################
# Functions
######################################
function (set_standard_warnings tgt)
  target_compile_options ( ${tgt} PRIVATE -Wall -Wextra)
endfunction()

function (enable_cxx14 tgt)
  set_target_properties(
    ${tgt} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
  )
endfunction ()

function (enable_clang_tidy tgt)
  if (WITH_CLANG_TIDY)
    find_program (
      CLANG_TIDY_EXE
      NAMES "clang-tidy"
      DOC "Path to clang-tidy executable"
    )
    if (NOT CLANG_TIDY_EXE)
      message (STATUS "clang-tidy not found.")
    else ()
      message (STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
      set (DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif ()

    set_target_properties (${tgt} PROPERTIES CXX_CLANG_TIDY "${DO_CLANG_TIDY}")
  endif ()
endfunction ()

######################################
# Options
######################################
option (WITH_CLANG_TIDY "If enabled run clang-tidy alongside the compiler" OFF)

######################################
# Setup
######################################
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package (spdlog REQUIRED)
find_package (fmt REQUIRED)

######################################
# Targets
######################################
add_executable (main main.cpp)
#target_link_libraries (main PRIVATE tcmalloc_minimal)
target_link_libraries (main PRIVATE spdlog::spdlog fmt::fmt)
enable_cxx14 (main)
set_standard_warnings (main)
enable_clang_tidy (main)
