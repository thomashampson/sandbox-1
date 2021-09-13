cmake_minimum_required(VERSION 3.18)

# Define the project name.
project(const_ref_self)

# External libraries
find_package(Python REQUIRED COMPONENTS Interpreter Development)
find_package(Boost REQUIRED COMPONENTS python${Python_VERSION_MAJOR})

# Targets
add_library(const_ref_self SHARED environ.cpp)
set_target_properties(const_ref_self PROPERTIES PREFIX "")
target_link_libraries(const_ref_self PRIVATE Boost::boost Boost::python${Python_VERSION_MAJOR} Python::Module)