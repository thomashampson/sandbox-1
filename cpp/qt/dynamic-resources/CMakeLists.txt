cmake_minimum_required(VERSION 3.7.0)

project(dynamic_resources)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(dynamic_resources
  main.cpp
)

target_link_libraries(dynamic_resources Qt5::Widgets)
