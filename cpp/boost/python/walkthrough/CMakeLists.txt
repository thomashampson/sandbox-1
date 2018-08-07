cmake_minimum_required(VERSION 3.5)

project(boostpy-walkthrough)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# find python/boost python
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Boost COMPONENTS python REQUIRED)

add_library(core SHARED
  "core.cpp"
  "container.cpp"
#  "containeritem.cpp"
#  "containeriterator.cpp"
)

target_include_directories(core PUBLIC ${PYTHON_INCLUDE_DIR})
target_link_libraries(core ${Boost_LIBRARIES} ${PYTHON_LIBRARIES})
set_target_properties(core PROPERTIES PREFIX "")
